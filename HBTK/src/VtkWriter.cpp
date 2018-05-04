#include "VtkWriter.h"

#include <string>
#include <utility>
#include <vector>

HBTK::Vtk::VtkWriter::VtkWriter()
	: written_xml_header(false)
{
}

void HBTK::Vtk::VtkWriter::write(std::ostream & stream, const VtkUnstructuredDataset & data)
{
	if (!written_xml_header) xml_header(stream);
	vtk_unstructured_file_header(stream);
	vtk_unstructed_grid_header(stream);
	vtk_unstructured_piece(stream, (int)data.mesh.points.size(), (int)data.mesh.cells.size());
	vtk_unstructured_mesh(stream, data.mesh); // No close statement.
	vtk_unstructured_point_data(stream, data);
	vtk_unstructured_cell_data(stream, data);

	m_xml_writer.close_tag(stream); // piece
	m_xml_writer.close_tag(stream); // grid
	m_xml_writer.close_tag(stream); // file header
	return;
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
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		{ std::make_pair("type", "Float64"),
		  std::make_pair("Name", name),
		  std::make_pair("NumberOfComponents", "1"),
		  std::make_pair("Format", "ascii") }
	);
	for (auto & sca : scalars) {
		ostream << sca << "\n";
	}
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<int>& ints)
{
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		{ std::make_pair("type", "Int64"),
		std::make_pair("Name", name),
		std::make_pair("NumberOfComponents", "1"),
		std::make_pair("Format", "ascii") }
	);
	for (auto & i : ints) {
		ostream << i << "\n";
	}
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<HBTK::CartesianVector3D>& vects)
{
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		{ std::make_pair("type", "Float64"),
		std::make_pair("Name", name),
		std::make_pair("NumberOfComponents", "3"),
		std::make_pair("Format", "ascii") }
	);
	for (auto & vect : vects) {
		ostream << vect.x() << " " << vect.y() << " " << vect.z() << "\n";
	}
	m_xml_writer.close_tag(ostream);
}

void HBTK::Vtk::VtkWriter::vtk_data_array(std::ostream & ostream, std::string name, const std::vector<HBTK::CartesianPoint3D>& pnts)
{
	m_xml_writer.open_tag(
		ostream,
		"DataArray",
		{ std::make_pair("type", "Float64"),
		std::make_pair("Name", name),
		std::make_pair("NumberOfComponents", "3"),
		std::make_pair("Format", "ascii") }
	);
	for (auto & pnt : pnts) {
		ostream << pnt.x() << " " << pnt.y() << " " << pnt.z() << "\n";
	}
	m_xml_writer.close_tag(ostream);
}
