#pragma once
/*////////////////////////////////////////////////////////////////////////////
StructuredMeshBlock2D.h

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

#include <array>
#include <vector>

namespace HBTK {
	class StructuredMeshBlock2D
	{
	public:
		StructuredMeshBlock2D();
		~StructuredMeshBlock2D();

		// Set the number of nodes in i, j and k directions.
		void set_extent(int i, int j);
		// Set the coordinate of a node on the grid.
		void set_coord(int i, int j, double x, double y);

		// Get extent as tuple;
		std::tuple<int, int> extent();
		// Get a coordinate for a node on the grid (given as RHS val).
		std::tuple<double, double>&
			coord(int i, int j);

	private:
		int i_extent, j_extent;
		std::vector<double> m_x_coords;
		std::vector<double> m_y_coords;

		bool check_valid_idx(int i, int j);
		int generate_linear_index(int i, int j);
	};
}


