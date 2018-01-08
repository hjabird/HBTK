#include "stdafx.h"
#include "Plot3DWriter.h"

#include <cassert>

HBTK::Plot3D::Plot3DWriter::Plot3DWriter()
{
}


HBTK::Plot3D::Plot3DWriter::~Plot3DWriter()
{
}


void HBTK::Plot3D::Plot3DWriter::add_mesh_block2d(HBTK::StructuredMeshBlock2D mesh)
{
	m_meshes_2d.emplace_back(mesh);
}

void HBTK::Plot3D::Plot3DWriter::add_mesh_block3d(HBTK::StructuredMeshBlock3D mesh)
{
	m_meshes_3d.emplace_back(mesh);
}

bool HBTK::Plot3D::Plot3DWriter::write(std::string path)
{
	std::ofstream output_stream(path);
	return write(output_stream);
}


bool HBTK::Plot3D::Plot3DWriter::write(std::ofstream & output_stream)
{
	if (!output_stream) { return false; }
}


void HBTK::Plot3D::Plot3DWriter::write_block_extent(int block, std::ofstream & output_stream)
{
	assert(block >= 0);
	if (three_dimensional) {
		assert(block < (int)m_meshes_3d.size());
		output_stream << std::get<0>(m_meshes_3d[block].extent());
		output_stream << std::get<1>(m_meshes_3d[block].extent());
		output_stream << std::get<2>(m_meshes_3d[block].extent());
	}
	else {
		assert(block < (int)m_meshes_2d.size());
		output_stream << std::get<0>(m_meshes_2d[block].extent());
		output_stream << std::get<1>(m_meshes_2d[block].extent());
	}
}


void HBTK::Plot3D::Plot3DWriter::write_nodes(int block, std::ofstream & output_stream)
{
	assert(block >= 0);
	if (three_dimensional) {
		assert(block < (int)m_meshes_3d.size());
		for (int k = 0; k < std::get<2>(m_meshes_3d[block].extent()); k++) {
			for (int j = 0; j < std::get<1>(m_meshes_3d[block].extent()); j++) {
				for (int i = 0; i < std::get<0>(m_meshes_3d[block].extent()); i++) {
					output_stream << std::get<0>(m_meshes_3d[block].coord(i, j, k));
				}
			}
		}
		for (int k = 0; k < std::get<2>(m_meshes_3d[block].extent()); k++) {
			for (int j = 0; j < std::get<1>(m_meshes_3d[block].extent()); j++) {
				for (int i = 0; i < std::get<0>(m_meshes_3d[block].extent()); i++) {
					output_stream << std::get<1>(m_meshes_3d[block].coord(i, j, k));
				}
			}
		}
		for (int k = 0; k < std::get<2>(m_meshes_3d[block].extent()); k++) {
			for (int j = 0; j < std::get<1>(m_meshes_3d[block].extent()); j++) {
				for (int i = 0; i < std::get<0>(m_meshes_3d[block].extent()); i++) {
					output_stream << std::get<2>(m_meshes_3d[block].coord(i, j, k));
				}
			}
		}
	}
	else {
		assert(block < (int)m_meshes_2d.size());
		for (int j = 0; j < std::get<1>(m_meshes_2d[block].extent()); j++) {
			for (int i = 0; i < std::get<0>(m_meshes_2d[block].extent()); i++) {
				output_stream << std::get<0>(m_meshes_2d[block].coord(i, j));
			}
		}
		for (int j = 0; j < std::get<1>(m_meshes_2d[block].extent()); j++) {
			for (int i = 0; i < std::get<0>(m_meshes_2d[block].extent()); i++) {
				output_stream << std::get<1>(m_meshes_2d[block].coord(i, j));
			}
		}
	}

	return;
}
