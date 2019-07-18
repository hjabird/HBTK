#include "VtkXmlArrayReader.h"
/*////////////////////////////////////////////////////////////////////////////
VtkXmlArrayReader.cpp

Read arrays from VTK Xml files.

Copyright 2018 HJA Bird

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <stdexcept>

int HBTK::Vtk::VtkXmlArrayReader::new_array_tag(
	int expected_length, 
	Xml::XmlParser::key_val_pairs xml_tag_args,
	Xml::XmlParser & parser)
{
	std::string name;
	dtype type_num = SCALAR;
	stype type_comp = FLOAT64;
	bool type_known(false), name_known(false), stype_known(false);
	bool appended(false), ascii(false), binary(false);
	int offset(-1);

	if(expected_length < 0) { throw std::invalid_argument("Bad expected array length: " + std::to_string(expected_length)); }
	for (auto & p : xml_tag_args) {
		if (p.first == "Name" || p.first == "name") {
			name = p.second;
			name_known = true;
		}
		else if (p.first == "type" || p.first == "Type") {
			type_comp = type_string_to_stype(p.second);
			stype_known = true;
		}
		else if (p.first == "NumberOfComponents") {
			if (p.second == "1") type_num = SCALAR;
			else if (p.second == "3") type_num = VECTOR;
			else throw std::invalid_argument("Bad NumberOfComponents: " + p.second);
			type_known = true;
		}
		else if (p.first == "format") {
			if (p.second == "appended") {
				appended = true;
			} else if (p.second == "binary") {
				binary = true;
			}
			else if (p.second == "ascii") {
				ascii = true;
			}
			else throw std::invalid_argument("Bad format: " + p.second);
		}
		else if (p.first == "offset"){
			p.second = atoi(p.second.c_str());
		}
	}
	
	// Now check that we have something workable:
	if(!(appended || ascii || binary)) throw std::invalid_argument("Format (appended, binary, ascii) unknown.");
	if ((appended && ascii) || (binary && ascii) || (appended && binary)) {
		throw std::invalid_argument("Multiple formats specified.");
	}
	if(appended && (offset == -1)){ throw std::invalid_argument("Offset not specified."); }
	if(!type_known){ throw std::invalid_argument("NumberOfComponents unknown."); }
	if(!stype_known) { throw std::invalid_argument("Type (ie. Int32, Float64 etc) unknown."); }
	int i_tag = (int)m_data_types.size();
	if (!name_known) { name = std::to_string(i_tag); name_known = true; }

	int id = (int)m_data_names.size();
	m_data_names.push_back(name);
	m_data_types.push_back(type_num);
	m_storage_types.push_back(type_comp);
	m_num_values.push_back(expected_length);


	if (appended) {
		m_offsets[id] = offset;
	} else if (ascii) 
	{
		read_ascii_data(id, parser);
	}
	else if (binary)
	{
		// read_base64_data(id);
	}
	return id;
}

HBTK::Vtk::VtkXmlArrayReader::dtype HBTK::Vtk::VtkXmlArrayReader::retrieve_data_type(int array_tag)
{
	assert(array_tag >= 0);
	assert(array_tag < (int)m_data_names.size());
	return m_data_types[array_tag];
}

void HBTK::Vtk::VtkXmlArrayReader::retrieve_scalar_data(int tag, std::string & name_target, std::vector<double>& data_target)
{
	assert(tag >= 0);
	assert(tag < (int)m_data_names.size());
	if (m_scalar_data.count(tag) == 0) {
		throw std::invalid_argument(m_data_names[tag] + " is not of scalar type.");
	}
	data_target = m_scalar_data[tag];
	name_target = m_data_names[tag];
	return;
}

void HBTK::Vtk::VtkXmlArrayReader::retrieve_int_data(int tag, std::string & name_target, std::vector<int>& data_target)
{
	assert(tag >= 0);
	assert(tag < (int)m_data_names.size());
	if (m_int_data.count(tag) == 0) {
		throw std::invalid_argument(m_data_names[tag] + " is not of int type.");
	}
	data_target = m_int_data[tag];
	name_target = m_data_names[tag];
	return;
}

void HBTK::Vtk::VtkXmlArrayReader::retrieve_vector_data(int tag, std::string & name_target, std::vector<HBTK::CartesianVector3D>& data_target)
{
	assert(tag >= 0);
	assert(tag < (int)m_data_names.size());
	if (m_vector_data.count(tag) == 0) {
		throw std::invalid_argument(m_data_names[tag] + " is not of vector type.");
	}
	data_target = m_vector_data[tag];
	name_target = m_data_names[tag];
	return;
}

HBTK::Vtk::VtkXmlArrayReader::stype HBTK::Vtk::VtkXmlArrayReader::type_string_to_stype(std::string desc)
{
	const std::unordered_map<std::string, stype> mapping({
		{"Int8", INT8},
		{ "Int16", INT16 },
		{ "Int32", INT32 },
		{ "Int64", INT64 },
		{ "UInt8", UINT8 },
		{ "UInt16", UINT16 },
		{ "UInt32", UINT32 },
		{ "UInt64", UINT64 },
		{ "Float32", FLOAT32 },
		{ "Float64", FLOAT64 }
		});
	stype t;
	if (mapping.count(desc) == 0) {
		throw std::invalid_argument("Bad type description string. Given " + desc);
	}
	else {
		t = mapping.at(desc);
	}
	return t;
}

void HBTK::Vtk::VtkXmlArrayReader::read_ascii_data(int id, Xml::XmlParser& xml_parser)
{
	std::istream & istream = xml_parser.xml_input_stream();
	int n_val = m_num_values[id];
	dtype dt = m_data_types[id];
	stype st = m_storage_types[id];
	if (dt == SCALAR) {
		std::vector<double> data(n_val);
		for (int i = 0; i < n_val; i++) {
			try {
				istream >> data[i];
			}
			catch (...) {
				std::invalid_argument("Encountered problem reading input stream.");
			}
		}
		m_scalar_data[id] = data;
	}
	else if (dt == INTEGER) {
		std::vector<int> data(n_val);
		for (int i = 0; i < n_val; i++) {
			try {
				istream >> data[i];
			}
			catch (...) {
				std::invalid_argument("Encountered problem reading input stream.");
			}
		}
		m_int_data[id] = data;
	}
	else if (dt == VECTOR) {
		std::vector<CartesianVector3D> data(n_val * 3);
		for (int i = 0; i < n_val; i++) {
			double x, y, z;
			try {
				istream >> x;
				istream >> y;
				istream >> z;
				data[i] = CartesianVector3D({ x, y, z });
			}
			catch (...) {
				std::invalid_argument("Encountered problem reading input stream.");
			}
		}
		m_vector_data[id] = data;
	}
	return;
}
