#include "VtkWriter.h"
/*////////////////////////////////////////////////////////////////////////////
VtkWriter.h

Write new, xml VTK data files. Does not have all the bells and whistles of
the complete file type, but who cares?

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

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>

HBTK::Vtk::VtkWriter::VtkWriter()
	: m_written_xml_header(false),
	m_file_type(None),
	ascii(false),
	appended(true)
{
}

void HBTK::Vtk::VtkWriter::open_file(std::ostream & stream, vtk_file_type file_type)
{
	if (!m_written_xml_header) xml_header(stream);
	switch (file_type) {
	case UnstructuredGrid:
		vtk_unstructured_file_header(stream);
		m_file_type = file_type;
		break;
	default:
		throw std::runtime_error(
			"HBTK::Vtk::VtkWriter::open_file: "
			"Given invalid file type (probably None). " + std::to_string(__LINE__)
			+ " : " __FILE__
		);
		break;
	}
}

void HBTK::Vtk::VtkWriter::write_piece(std::ostream & stream, const VtkUnstructuredDataset & data)
{
	assert(m_file_type != None); // Have you used open_file()?
	if (m_file_type != UnstructuredGrid) {
		throw std::runtime_error(
			"HBTK::Vtk::VtkWriter::write_piece(..., VtkUnstructuredGrid): "
			"VtkFileType is not unstructured grid! " + std::to_string(__LINE__)
			+ " : " __FILE__
		);
	}
	vtk_unstructured_piece(stream, (int)data.mesh.points.size(), (int)data.mesh.cells.size());
	vtk_unstructured_mesh(stream, data.mesh); // No close statement.
	vtk_unstructured_point_data(stream, data);
	vtk_unstructured_cell_data(stream, data);

	m_xml_writer.close_tag(stream); // piece
	return;
}

void HBTK::Vtk::VtkWriter::close_file(std::ostream & stream)
{
	if ((int) m_appended_data.size()) {
		if (ascii) {
			m_xml_writer.open_tag(stream, "AppendedData",
				{ std::make_pair("encoding", "raw") });
		}
		else {
			m_xml_writer.open_tag(stream, "AppendedData",
				{ std::make_pair("encoding", "ascii") });
		}
		stream << '_';
		for (auto & s : m_appended_data) {
			for (auto & c : s) {
				stream << c;
			}
		}
		m_xml_writer.close_tag(stream);
		m_xml_writer.close_tag(stream); // grid type.
		m_xml_writer.close_tag(stream); // VTK file
	}
}

void HBTK::Vtk::VtkWriter::xml_header(std::ostream & ostream)
{
	m_xml_writer.header(ostream, "1.0", "UTF-8");
}

void HBTK::Vtk::VtkWriter::vtk_unstructured_file_header(std::ostream & ostream)
{
	m_xml_writer.open_tag(ostream, "VTKFile",
		{ std::make_pair("type", "UnstructuredGrid"),
		std::make_pair("version", "0.1"),
		std::make_pair("byte_order", "LittleEndian")});
}

void HBTK::Vtk::VtkWriter::vtk_unstructed_grid_header(std::ostream & ostream)
{
	m_xml_writer.open_tag(ostream, "UnstructuredGrid", {});
}

void HBTK::Vtk::VtkWriter::vtk_unstructured_piece(std::ostream & ostream, int num_points, int num_cells)
{
	m_xml_writer.open_tag(ostream, "Piece", {
		std::make_pair("NumberOfPoints", std::to_string(num_points)),
		std::make_pair("NumberOfCells", std::to_string(num_cells))
		});
}

void HBTK::Vtk::VtkWriter::vtk_unstructured_mesh(std::ostream & ostream, const VtkUnstructuredMeshHolder & mesh)
{
	m_xml_writer.open_tag(ostream, "Points", {});
	vtk_data_array(ostream, "Points", mesh.points);
	m_xml_writer.close_tag(ostream);
	vtk_unstructured_cells(ostream, mesh);
}

void HBTK::Vtk::VtkWriter::vtk_unstructured_cells(std::ostream & ostream, const VtkUnstructuredMeshHolder & mesh)
{
	m_xml_writer.open_tag(ostream, "Cells", {});

	std::vector<int> scratch(mesh.cells.size());
	for (int i = 0; i < (int)mesh.cells.size(); i++) scratch[i] = mesh.cells[i].cell_type;
	vtk_data_array(ostream, "types", scratch);

	int offset_counter = 0;
	for (int i = 0; i < (int)mesh.cells.size(); i++) {
		scratch[i] = offset_counter;
		offset_counter += (int)mesh.cells[i].node_ids.size();
	}
	vtk_data_array(ostream, "offsets", scratch);

	scratch.empty();
	for (auto & cell : mesh.cells)scratch.insert(scratch.begin(), cell.node_ids.begin(), cell.node_ids.end());
	vtk_data_array(ostream, "connectivity", scratch);

	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_unstructured_point_data(std::ostream & ostream, const VtkUnstructuredDataset & data)
{
	m_xml_writer.open_tag(ostream, "PointData", {});
	for (auto & subset : data.integer_point_data) vtk_data_array(ostream, subset.first, subset.second);
	for (auto & subset : data.scalar_point_data) vtk_data_array(ostream, subset.first, subset.second);
	for (auto & subset : data.vector_point_data) vtk_data_array(ostream, subset.first, subset.second);
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_unstructured_cell_data(std::ostream & ostream, const VtkUnstructuredDataset & data)
{
	m_xml_writer.open_tag(ostream, "CellData", {});
	for (auto & subset : data.integer_cell_data) vtk_data_array(ostream, subset.first, subset.second);
	for (auto & subset : data.scalar_cell_data) vtk_data_array(ostream, subset.first, subset.second);
	for (auto & subset : data.vector_cell_data) vtk_data_array(ostream, subset.first, subset.second);
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<double>& scalars)
{
	std::vector<std::pair<std::string, std::string>> xml_params =
	{ std::make_pair("type", "Float64"),
		  std::make_pair("Name", name),
		  std::make_pair("NumberOfComponents", "1") };
	auto format_params = vtk_data_array_format_options();
	xml_params.insert(xml_params.end(), format_params.begin(), format_params.end());
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		xml_params);

	auto data = vtk_data_array_generate_buffer(scalars);
	if (!appended) {
		for (auto & ch : data) { ostream << ch; }
	}
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<int>& ints)
{
	std::vector<std::pair<std::string, std::string>> xml_params =
	{ std::make_pair("type", "Int64"),
		std::make_pair("Name", name),
		std::make_pair("NumberOfComponents", "1") };
	auto format_params = vtk_data_array_format_options();
	xml_params.insert(xml_params.end(), format_params.begin(), format_params.end());
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		xml_params);

	auto data = vtk_data_array_generate_buffer(ints);
	if (!appended) {
		for (auto & ch : data) { ostream << ch; }
	}
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<HBTK::CartesianVector3D>& vects)
{
	std::vector<std::pair<std::string, std::string>> xml_params =
	{ std::make_pair("type", "Float64"),
		std::make_pair("Name", name),
		std::make_pair("NumberOfComponents", "3") };
	auto format_params = vtk_data_array_format_options();
	xml_params.insert(xml_params.end(), format_params.begin(), format_params.end());
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		xml_params);

	auto data = vtk_data_array_generate_buffer(vects);
	if (!appended) {
		for (auto & ch : data) { ostream << ch; }
	}
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<HBTK::CartesianPoint3D>& pnts)
{
	std::vector<std::pair<std::string, std::string>> xml_params =
	{ std::make_pair("type", "Float64"),
		std::make_pair("Name", name),
		std::make_pair("NumberOfComponents", "3") };
	auto format_params = vtk_data_array_format_options();
	xml_params.insert(xml_params.end(), format_params.begin(), format_params.end());
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		xml_params);

	auto data = vtk_data_array_generate_buffer(pnts);
	if (!appended) {
		for (auto & ch : data) { ostream << ch; }
	}
	m_xml_writer.close_tag(ostream);
}

std::vector<unsigned char> HBTK::Vtk::VtkWriter::vtk_data_array_generate_buffer(const std::vector<double>& scalars)
{
	std::vector<unsigned char> buffer;
	if (ascii) {
		for (auto & sca : scalars) {
			std::string str = std::to_string(sca);
			for (char & c : str) {
				buffer.push_back(c);
			}
			buffer.push_back('\n');
		}
	}
	else {
		buffer.resize(sizeof(double) * scalars.size());
		for (int i = 0; i < (int)scalars.size(); i++) {
			const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&scalars[i]);
			// Watch me carfully!
			std::copy_n(bytes, (int) sizeof(double), &buffer[i * sizeof(double)]);
		}
	}
	if (appended) {
		m_appended_data.push_back(buffer);
	}
	return buffer;
}

std::vector<unsigned char> HBTK::Vtk::VtkWriter::vtk_data_array_generate_buffer(const std::vector<int>& integers)
{
	std::vector<unsigned char> buffer;
	if (ascii) {
		for (auto & sca : integers) {
			std::string str = std::to_string(sca);
			for (char & c : str) {
				buffer.push_back(c);
			}
			buffer.push_back('\n');
		}
	}
	else {
		buffer.resize(sizeof(int64_t) * integers.size());
		for (int i = 0; i < (int64_t)integers.size(); i++) {
			int64_t tmp = integers[i];
			const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&tmp);
			// Watch me carfully!
			std::copy_n(bytes, (int) sizeof(int64_t), &buffer[i * sizeof(double)]);
		}
	}
	if (appended) {
		m_appended_data.emplace_back(buffer);
	}
	return buffer;
}

std::vector<unsigned char> HBTK::Vtk::VtkWriter::vtk_data_array_generate_buffer(const std::vector<HBTK::CartesianVector3D> & vectors)
{
	std::vector<unsigned char> buffer;
	if (ascii) {
		for (auto & vect : vectors) {
			for (const double & doub : vect.as_array()) {
				std::string str = std::to_string(doub);
				for (char & c : str) {
					buffer.push_back(c);
				}
				buffer.push_back(' ');
			}
			buffer.push_back('\n');
		}
	}
	else {
		buffer.resize(sizeof(double) * vectors.size());
		for (int i = 0; i < (double)vectors.size(); i++) {
			const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&vectors[i]);
			// Watch me carfully!
			std::copy_n(bytes, (int) sizeof(double), &buffer[i * sizeof(double)]);
		}
	}
	if (appended) {
		m_appended_data.emplace_back(buffer);
	}
	return buffer;
}

std::vector<unsigned char> HBTK::Vtk::VtkWriter::vtk_data_array_generate_buffer(const std::vector<HBTK::CartesianPoint3D> & pnts)
{
	std::vector<unsigned char> buffer;
	if (ascii) {
		for (auto & pnt : pnts) {
			for (const double & doub : pnt.as_array()) {
				std::string str = std::to_string(doub);
				for (char & c : str) {
					buffer.push_back(c);
				}
				buffer.push_back(' ');
			}
			buffer.push_back('\n');
		}
	}
	else {
		buffer.resize(sizeof(double) * pnts.size());
		for (int i = 0; i < (double)pnts.size(); i++) {
			const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&pnts[i]);
			// Watch me carfully!
			std::copy_n(bytes, (int) sizeof(double), &buffer[i * sizeof(double)]);
		}
	}
	if (appended) {
		m_appended_data.emplace_back(buffer);
	}
	return buffer;
}

std::vector<std::pair<std::string, std::string>> HBTK::Vtk::VtkWriter::vtk_data_array_format_options() const
{
	if (appended) {
		return { std::make_pair("Format", "appended"),
			std::make_pair("Offset", std::to_string(appended_data_bytelength())) };
	}
	else {
		if (ascii) {
			return { std::make_pair("Format", "ascii") };
		}
		else {
			return { std::make_pair("Format", "binary") };
		}
	}
}

int HBTK::Vtk::VtkWriter::appended_data_bytelength() const
{
	int acc = 0;
	for (auto & arr : m_appended_data) {
		acc += (int)m_appended_data.size();
	}
	return acc;
}
