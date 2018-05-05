#include "VtkParser.h"

#include <cassert>

void HBTK::Vtk::VtkParser::main_parser(std::ifstream & input_stream, std::ostream & error_stream)
{

	
}

void HBTK::Vtk::VtkParser::on_tag_open(std::string tag_name, key_val_pairs key_vals)
{	
	// Essentially, this is a giant method to set up an Xml parser that does what we want.
	// More fun that you can shake a stick at.
}

void HBTK::Vtk::VtkParser::on_tag_close(std::string tag_name)
{
	vtk_tags tag = string_to_tag(tag_name);
	// Its Xml parsers job to make sure the start / end tags match but:
	assert(m_tag_stack.top() == tag);
	m_tag_stack.pop();
}


void HBTK::Vtk::VtkParser::on_vtkfile_tag(key_val_pairs key_vals)
{
	m_tag_stack.push(vtk_tags::VTKFileTag);
	for (auto & key_val : key_vals) {
		if (key_val.first == "type") {
			set_vtk_file_type(key_val.second);
		}
		else if (key_val.first == "version") {
			set_vtk_file_version(key_val.second);
		}
		else if (key_val.first == "byte_order") {
			; // Meh.
		}
		else {
			throw;
		}
	}
}


void HBTK::Vtk::VtkParser::set_vtk_file_type(std::string str)
{
	if (m_file_type != UnknownFile) throw;
	if (str == "UnstructuredGrid") {
		m_file_type = UnstructuredGridFile;
	}
	else if (str == "StructuredGrid") {
		m_file_type = StructuredGridFile;
	}
	else {
		m_file_type = UnknownFile;
		throw;
	}
	return;
}

void HBTK::Vtk::VtkParser::set_vtk_file_version(std::string str)
{
	m_version = std::stod(str.c_str());
	return;
}
