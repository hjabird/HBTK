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

#include "StructuredValueBlockND.h"

namespace HBTK {
	class StructuredMeshBlock3D
	{
	public:
		StructuredMeshBlock3D();
		~StructuredMeshBlock3D();

		// Set the number of nodes in i, j and k directions.
		void set_extent(std::array<int, 3> indexes);
		
		// Extent as tuple
		std::array<int, 3> extent();

		// Set a coordinate for a node on the grid.
		void set_coord(std::array<int, 3> indexes, std::array<double, 3> coord);
		// Get a coordinate for a node on the grid.
		std::array<double, 3> coord(std::array<int, 3> indexes);

		// Swaps internal array coordinates.
		// Eg swap_..._ij turns 200x100x50 -> 100x200x50 
		// whilst keeping the grid coordinates identical.
		void swap_internal_coordinates_ij();
		void swap_internal_coordinates_ik();
		void swap_internal_coordinates_jk();

	private:
		// Three Structured mesh value blocks. I'm sure it could be optimised...
		std::array<StructuredValueBlockND<3, double>, 3> m_coordinates;
	};
}

