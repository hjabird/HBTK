#include "StructuredMeshBlock2D.h"
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock2D.cpp

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
	StructuredMeshBlock2D::StructuredMeshBlock2D()
	{
	}


	StructuredMeshBlock2D::~StructuredMeshBlock2D()
	{
	}


	void StructuredMeshBlock2D::set_extent(std::array<int, 2> indexes)
	{
		for (auto &block : m_coordinates) { block.extent(indexes); }
		return;
	}

	void StructuredMeshBlock2D::set_coord(std::array<int, 2> indexes, std::array<int, 3> coordinate)
	{
		for (int i = 0; i < 3; i++) {
			m_coordinates[i].value(indexes) = coordinate[i];
		}
		return;
	}


	std::array<int, 2> StructuredMeshBlock2D::extent()
	{
		return m_coordinates[0].extent();
	}

	std::array<double, 2> StructuredMeshBlock2D::coord(std::array<int, 2> indexes)
	{
		return { m_coordinates[0].value(indexes),
			m_coordinates[1].value(indexes) };
	}

	void StructuredMeshBlock2D::swap_internal_coordinates_ij()
	{
		for (auto &block : m_coordinates) {
			block.swap(1, 2);
		}
		return;
	}
	
	HBTK::StructuredMeshBlock3D StructuredMeshBlock2D::extrude_to_3D(std::vector<double> z_values)
	{
		assert((int)z_values.size() > 1);

		std::sort(z_values.begin(), z_values.end());
		HBTK::StructuredMeshBlock3D mesh3d;
		int k_dim = (int)z_values.size();

		mesh3d.set_extent({ extent()[0],
							extent()[1],
							k_dim });
		for (int i = 0; i < extent()[0]; i++) {
			for (int j = 0; j < extent()[1]; j++) {
				auto phys_2d = coord({ i, j });
				for (int k = 0; k < k_dim; k++) {
					double z = z_values[k];
					mesh3d.set_coord({ i, j, k }, { phys_2d[0], phys_2d[1], z });
				}
			}
		}
		return mesh3d;
	}
}



	
