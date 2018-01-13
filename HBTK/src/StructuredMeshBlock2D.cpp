#include "stdafx.h"
#include "StructuredMeshBlock2D.h"
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock2D.cpp

A class to represent a 2D structured mesh.

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
#include <vector>

#include "Generators.h"

namespace HBTK {
	StructuredMeshBlock2D::StructuredMeshBlock2D()
		: m_i_extent(-1),
		m_j_extent(-1)
	{
	}


	StructuredMeshBlock2D::~StructuredMeshBlock2D()
	{
	}


	void StructuredMeshBlock2D::set_extent(int i, int j)
	{
		assert(i >= 0);
		assert(j >= 0);
		int size = i * j;
		m_i_extent = i;
		m_j_extent = j;
		m_x_coords.resize(size);
		m_y_coords.resize(size);
	}

	void StructuredMeshBlock2D::set_coord(int i, int j, double x, double y)
	{
		coord(i, j) = std::make_tuple(x, y);
		return;
	}


	std::tuple<int, int> StructuredMeshBlock2D::extent()
	{
		int i = m_i_extent;
		int j = m_j_extent;
		return std::make_tuple(i, j);
	}

	std::tuple<double&, double&> StructuredMeshBlock2D::coord(int i, int j)
	{
		assert(check_valid_idx(i, j));
		int lin_idx = generate_linear_index(i, j);
		return std::forward_as_tuple(m_x_coords[lin_idx], m_y_coords[lin_idx]);
	}

	HBTK::StructuredMeshBlock3D StructuredMeshBlock2D::extrude_to_3D(std::vector<double> z_values)
	{
		assert((int)z_values.size() > 1);

		std::sort(z_values.begin(), z_values.end());
		HBTK::StructuredMeshBlock3D mesh3d;
		int k_dim = (int)z_values.size();

		mesh3d.set_extent(m_i_extent, m_j_extent, k_dim);
		double x, y, z;
		for (int i = 0; i < m_i_extent; i++) {
			for (int j = 0; j < m_j_extent; j++) {
				std::tie(x, y) = coord(i, j);
				for (int k = 0; k < k_dim; k++) {
					z = z_values[k];
					mesh3d.coord(i, j, k) = std::tie(x, y, z);
				}
			}
		}
		return mesh3d;
	}


	bool StructuredMeshBlock2D::check_valid_idx(int i, int j)
	{
		if ((i >= 0) && (j >= 0) &&
			(i < m_i_extent) && (j < m_j_extent)) {
			return true;
		}
		else {
			return false;
		}
	}


	int StructuredMeshBlock2D::generate_linear_index(int i, int j)
	{
		int lin_idx = i + j * m_i_extent;
		return lin_idx;
	}
}


