#pragma once
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock3D.h

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

#include <array>
#include <tuple>
#include <vector>

namespace HBTK {
	class StructuredMeshBlock3D
	{
	public:
		StructuredMeshBlock3D();
		~StructuredMeshBlock3D();

		// Set the number of nodes in i, j and k directions.
		void set_extent(int i, int j, int k);

		// Set the coordinate of a node on the grid.
		void set_coord(int i, int j, int k, double x, double y, double z);

		// Extent as tuple
		std::tuple<int, int, int> extent();
		// Get a coordinate for a node on the grid (given as RHS val).
		std::tuple<double&, double&, double&>
			coord(int i, int j, int k);

		// Swaps internal array coordinates.
		// Eg swap_..._ij turns 200x100x50 -> 100x200x50 
		// whilst keeping the grid coordinates identical.
		void swap_internal_coordinates_ij();
		void swap_internal_coordinates_ik();
		void swap_internal_coordinates_jk();

	private:
		// Array of {i_extent, j_extent, k_extent}
		std::array<int, 3> m_extents;
		// Array of {x_coords, y_coords, z_coords}
		std::array<std::vector<double>, 3> m_coords;

		void swap_block_coordinates(int first_idx, int second_idx);

		bool check_valid_idx(int i, int j, int k);
		int generate_linear_index(int i, int j, int k);
		int generate_linear_index(int i, int j, int k, int i_ext, int j_ext, int k_ext);
	};
}

