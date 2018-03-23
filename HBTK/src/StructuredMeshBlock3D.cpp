#include "StructuredMeshBlock3D.h"
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock3D.cpp

A class to represent a 3D structured mesh.

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

namespace HBTK {
	StructuredMeshBlock3D::StructuredMeshBlock3D()
	{
	}


	StructuredMeshBlock3D::~StructuredMeshBlock3D()
	{
	}


	void StructuredMeshBlock3D::set_extent(std::array<int, 3> indexes)
	{
		for (auto &block : m_coordinates) { block.extent(indexes); }
		return;
	}

	void StructuredMeshBlock3D::set_coord(std::array<int, 3> indexes, std::array<double, 3> coordinate)
	{
		for (int i = 0; i < 3; i++) {
			m_coordinates[i].value(indexes) = coordinate[i];
		}
		return;
	}


	std::array<int, 3> StructuredMeshBlock3D::extent()
	{
		return m_coordinates[0].extent();
	}

	std::array<double, 3> StructuredMeshBlock3D::coord(std::array<int, 3> indexes)
	{
		return { m_coordinates[0].value(indexes),
				m_coordinates[1].value(indexes),
				m_coordinates[2].value(indexes) };
	}

	void StructuredMeshBlock3D::swap_internal_coordinates_ij()
	{
		for (auto &block : m_coordinates) {
			block.swap(1, 2);
		}
		return;
	}

	void StructuredMeshBlock3D::swap_internal_coordinates_ik()
	{
		for (auto &block : m_coordinates) {
			block.swap(1, 3);
		}
		return;
	}

	void StructuredMeshBlock3D::swap_internal_coordinates_jk()
	{
		for (auto &block : m_coordinates) {
			block.swap(2, 3);
		}
		return;
	}
}
