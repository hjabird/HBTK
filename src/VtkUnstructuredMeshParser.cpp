#include "VtkUnstructuredMeshParser.h"

#include <cassert>

HBTK::Vtk::VtkParser::VtkParser()
	: m_version(0.1),
	m_fmap_stack(),
	input_stream(NULL)
{
	m_fmap_stack.push
	(function_map({ {"VTKFile", 
		[&](const key_val_pairs & p, std::istream & s) {vtk_file_tag_handler(p,s); } } }));
}

void HBTK::Vtk::VtkParser::main_parser(std::ifstream & input_stream, std::ostream & error_stream)
{

	
}

void HBTK::Vtk::VtkParser::on_tag_open(std::string tag_name, key_val_pairs key_vals)
{	
	// Evaluates whatever is on top of the function map stack pretty much.
	std::function<void(const key_val_pairs &, std::istream & stream)> func;
	try {
		func = m_fmap_stack.top().at(tag_name);
		func(key_vals, *input_stream);
	}
	catch (...) {
		throw;
	}
}

void HBTK::Vtk::VtkParser::on_tag_close(std::string tag_name)
{
	m_fmap_stack.pop();
}

void HBTK::Vtk::VtkParser::vtk_file_tag_handler(
	const key_val_pairs & params, std::istream & stream)
{
	for (const auto & pair : params) {
		if (pair.first == "type") {
			if (pair.second != "UnstructuredGrid") {
				throw;
			}
		}
		else if(pair.first == "version") {
			; // Sort out later.
		}
		else if (pair.first == "byte_order") {
			; // Sort out later.
		}
		else if (pair.first == "compressor") {
			throw;
		}
		else {
			throw;
		}
	}

	m_fmap_stack.push(function_map({
		{ "Cells", [&](const key_val_pairs & p, std::istream & s) {unstructured_cells_tag_handler(p,s); } },
		{ "Points", [&](const key_val_pairs & p, std::istream & s) {unstructured_points_tag_handler(p,s); } },
		{ "CellData", [&](const key_val_pairs & p, std::istream & s) {unstructured_cell_data_tag_handler(p,s); } },
		{ "Points", [&](const key_val_pairs & p, std::istream & s) {unstructured_point_data_tag_handler(p,s); } } }));
	return;
}

void HBTK::Vtk::VtkParser::data_array_tag_handler(const key_val_pairs & params, std::istream & stream)
{
	int expected_len, tag;
	tag = m_array_reader.new_array_tag(expected_len, params, m_xml_parser);
}

void HBTK::Vtk::VtkParser::unstructured_cells_tag_handler(const key_val_pairs & params, std::istream & stream)
{
}

void HBTK::Vtk::VtkParser::unstructured_points_tag_handler(const key_val_pairs & params, std::istream & stream)
{
}

void HBTK::Vtk::VtkParser::unstructured_cell_data_tag_handler(const key_val_pairs & params, std::istream & stream)
{
}

void HBTK::Vtk::VtkParser::unstructured_point_data_tag_handler(const key_val_pairs & params, std::istream & stream)
{
}


