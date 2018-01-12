#include "stdafx.h"
#include "Plot3DWriter.h"
/*////////////////////////////////////////////////////////////////////////////
Plot3DWriter.h

Write a Plot3D file.

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
#include <iomanip>

#include "FortranSequentialOutputStream.h"

HBTK::Plot3D::Plot3DWriter::Plot3DWriter()
	: write_binary(true),
	no_block_count(false),
	three_dimensional(true)
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
	std::ofstream output_stream(path, std::ios::binary);
	return write(output_stream);
}


bool HBTK::Plot3D::Plot3DWriter::write(std::ofstream & output_stream)
{
	HBTK::FortranSequentialOutputStream fortran_output;
	if (!output_stream) { return false; }
	else {
		int blocks = (three_dimensional ? (int)m_meshes_3d.size() : (int)m_meshes_2d.size());
		if (!no_block_count) {
			if (write_binary) { 
				fortran_output.record_start(output_stream);
				output_stream.write(reinterpret_cast<char*>(&blocks), sizeof(blocks));
				fortran_output.record_end(output_stream);
			}
			else { output_stream << blocks << "\n"; }
		}
		if(write_binary) fortran_output.record_start(output_stream);
		for (int n = 0; n < blocks; n++) {
			write_block_extent(n, output_stream);
		}
		if (write_binary) fortran_output.record_end(output_stream);

		for (int n = 0; n < blocks; n++) {
			if (write_binary) fortran_output.record_start(output_stream);
			write_nodes(n, output_stream);
			if (write_binary) fortran_output.record_end(output_stream);
		}
	}
	return true;
}


void HBTK::Plot3D::Plot3DWriter::write_block_extent(int block, std::ofstream & output_stream)
{
	assert(block >= 0);
	if (three_dimensional) {
		assert(block < (int)m_meshes_3d.size());
		int i, j, k;
		std::tie(i, j, k) = m_meshes_3d[block].extent();
		if (write_binary) {
			output_stream.write(reinterpret_cast<char*>(&i), sizeof(i));
			output_stream.write(reinterpret_cast<char*>(&j), sizeof(j));
			output_stream.write(reinterpret_cast<char*>(&k), sizeof(k));
		}
		else {
			output_stream << i << " ";
			output_stream << j << " ";
			output_stream << k << "\n";
		}
	}
	else {
		assert(block < (int)m_meshes_2d.size());
		int i, j;
		std::tie(i, j) = m_meshes_2d[block].extent();
		if (write_binary) {
			output_stream.write(reinterpret_cast<char*>(&i), sizeof(i));
			output_stream.write(reinterpret_cast<char*>(&j), sizeof(j));
		}
		else {
			output_stream << i << " ";
			output_stream << j << "\n";
		}
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
					double val = std::get<0>(m_meshes_3d[block].coord(i, j, k));
					if (write_binary) {
						output_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
					}
					else {
						output_stream << std::setprecision(15) << std::scientific << val << "\n";
					}
				}
			}
		}
		for (int k = 0; k < std::get<2>(m_meshes_3d[block].extent()); k++) {
			for (int j = 0; j < std::get<1>(m_meshes_3d[block].extent()); j++) {
				for (int i = 0; i < std::get<0>(m_meshes_3d[block].extent()); i++) {
					double val = std::get<1>(m_meshes_3d[block].coord(i, j, k));
					if (write_binary) {
						output_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
					}
					else {
						output_stream << std::setprecision(15) << std::scientific << val << "\n";
					}
				}
			}
		}
		for (int k = 0; k < std::get<2>(m_meshes_3d[block].extent()); k++) {
			for (int j = 0; j < std::get<1>(m_meshes_3d[block].extent()); j++) {
				for (int i = 0; i < std::get<0>(m_meshes_3d[block].extent()); i++) {
					double val = std::get<2>(m_meshes_3d[block].coord(i, j, k));
					if (write_binary) {
						output_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
					}
					else {
						output_stream << std::setprecision(15) << std::scientific << val << "\n";
					}
				}
			}
		}
	} // End If three dimensional
	else {
		assert(block < (int)m_meshes_2d.size());
		for (int j = 0; j < std::get<1>(m_meshes_2d[block].extent()); j++) {
			for (int i = 0; i < std::get<0>(m_meshes_2d[block].extent()); i++) {
				double val = std::get<0>(m_meshes_2d[block].coord(i, j));
				if (write_binary) {
					output_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
				}
				else {
					output_stream << std::setprecision(15) << std::scientific << val << "\n";
				}
			}
		}
		for (int j = 0; j < std::get<1>(m_meshes_2d[block].extent()); j++) {
			for (int i = 0; i < std::get<0>(m_meshes_2d[block].extent()); i++) {
				double val = std::get<1>(m_meshes_2d[block].coord(i, j));
				if (write_binary) {
					output_stream.write(reinterpret_cast<char*>(&val), sizeof(val));
				}
				else {
					output_stream << std::setprecision(15) << std::scientific << val << "\n";
				}
			}
		}
	}
	output_stream.flush();
	return;
}
