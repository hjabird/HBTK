#include "stdafx.h"
#include "StructuredMeshBlock3D.h"
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock3D.cpp

A class to represent a 3D structured mesh.

Copyright 2017 HJA Bird

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

namespace HBTK {
	StructuredMeshBlock3D::StructuredMeshBlock3D()
		: m_extents({-1, -1, -1})
	{
	}


	StructuredMeshBlock3D::~StructuredMeshBlock3D()
	{
	}


	void StructuredMeshBlock3D::set_extent(int i, int j, int k)
	{
		assert(i >= 0);
		assert(j >= 0);
		assert(k >= 0);
		int size = i * j * k;
		m_extents = { i, j, k };
		for (auto &coord_vector : m_coords) { coord_vector.resize(size); }
	}

	void StructuredMeshBlock3D::set_coord(int i, int j, int k, double x, double y, double z)
	{
		coord(i, j, k) = std::make_tuple(x, y, z);
		return;
	}


	std::tuple<int, int, int> StructuredMeshBlock3D::extent()
	{
		int i = m_extents[0];
		int j = m_extents[1];
		int k = m_extents[2];
		return std::make_tuple(i, j, k);
	}

	std::tuple<double&, double&, double&> StructuredMeshBlock3D::coord(int i, int j, int k)
	{
		assert(check_valid_idx(i, j, k));
		int lin_idx = generate_linear_index(i, j, k);
		return std::forward_as_tuple(m_coords[0][lin_idx], m_coords[1][lin_idx], m_coords[2][lin_idx]);
	}

	void StructuredMeshBlock3D::swap_internal_coordinates_ij()
	{
		swap_block_coordinates(0, 1);
		return;
	}

	void StructuredMeshBlock3D::swap_internal_coordinates_ik()
	{
		swap_block_coordinates(0, 2);
		return;
	}

	void StructuredMeshBlock3D::swap_internal_coordinates_jk()
	{
		swap_block_coordinates(1, 2);
		return;
	}


	void StructuredMeshBlock3D::swap_block_coordinates(int first_idx, int second_idx)
	{
		assert(first_idx != second_idx);
		assert(first_idx < 3);
		assert(first_idx >= 0);
		assert(second_idx < 3);
		assert(second_idx >= 0);

		std::array<std::vector<double>, 3> new_coords;
		int size = m_extents[0] * m_extents[1] * m_extents[2];
		for (auto & coord_vect : new_coords) { coord_vect.resize(size); }
		std::array<int, 3> new_extents = m_extents;
		new_extents[first_idx] = m_extents[second_idx];
		new_extents[second_idx] = m_extents[first_idx];

		int lin_idx_new;
		std::array<int, 3> idx;
		double x, y, z;
		for (idx[0] = 0; idx[0] < m_extents[0]; idx[0]++) {
			for (idx[1] = 0; idx[1] < m_extents[1]; idx[1]++) {
				for (idx[2] = 0; idx[2] < m_extents[2]; idx[2]++) {
					std::array<int, 3> idx_new;
					// To satify the right hand rule, the unswitched axis changes dir.
					for (int l = 0; l < 3; l++) { idx_new[l] = m_extents[l] - idx[l] - 1; }
					idx_new[first_idx] = idx[second_idx];
					idx_new[second_idx] = idx[first_idx];
					lin_idx_new = generate_linear_index(
						idx_new[0], idx_new[1], idx_new[2],
						new_extents[0], new_extents[1], new_extents[2]);
					std::tie(x, y, z) = coord(idx[0], idx[1], idx[2]);
					new_coords[0][lin_idx_new] = x;
					new_coords[1][lin_idx_new] = y;
					new_coords[2][lin_idx_new] = z;
				}
			}
		}
		m_coords = new_coords;
		m_extents = new_extents;
		return;
	}

	bool StructuredMeshBlock3D::check_valid_idx(int i, int j, int k)
	{
		if ((i >= 0) && (j >= 0) && (k >= 0) &&
			(i < m_extents[0]) && (j < m_extents[1]) && (k < m_extents[2])) {
			return true;
		}
		else {
			return false;
		}
	}


	int StructuredMeshBlock3D::generate_linear_index(int i, int j, int k)
	{
		return generate_linear_index(i, j, k, m_extents[0], m_extents[1], m_extents[2]);
	}


	constexpr int StructuredMeshBlock3D::generate_linear_index(int i, int j, int k, int i_ext, int j_ext, int k_ext)
	{
		int lin_idx = i + j * i_ext + k * i_ext * j_ext;
		return lin_idx;
	}
}
