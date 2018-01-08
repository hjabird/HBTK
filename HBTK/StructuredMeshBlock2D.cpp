#include "stdafx.h"
#include "StructuredMeshBlock2D.h"
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock2D.cpp

A class to represent a 2D structured mesh.

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
	StructuredMeshBlock2D::StructuredMeshBlock2D()
		: i_extent(-1),
		j_extent(-1)
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
		m_x_coords.resize(i);
		m_y_coords.resize(j);
	}

	void StructuredMeshBlock2D::set_coord(int i, int j, double x, double y)
	{
		coord(i, j) = std::make_tuple(x, y);
		return;
	}


	std::tuple<int, int> StructuredMeshBlock2D::extent()
	{
		int i = m_x_coords.size();
		int j = m_y_coords.size();
		return std::make_tuple(i, j);
	}

	std::tuple<double, double>& StructuredMeshBlock2D::coord(int i, int j)
	{
		assert(check_valid_idx(i, j));
		int lin_idx = generate_linear_index(i, j);
		return std::make_tuple(m_x_coords[lin_idx], m_y_coords[lin_idx]);
	}


	bool StructuredMeshBlock2D::check_valid_idx(int i, int j)
	{
		if ((i >= 0) && (j >= 0) &&
			(i < i_extent) && (j < j_extent)) {
			return true;
		}
		else {
			return false;
		}
	}


	int StructuredMeshBlock2D::generate_linear_index(int i, int j)
	{
		int lin_idx = i + j * i_extent;
		return lin_idx;
	}
}


