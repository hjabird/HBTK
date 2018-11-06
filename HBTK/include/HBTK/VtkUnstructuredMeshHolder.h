#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkUnstructuresMeshHolder.h

Represents a dataless VTK unstructred mesh object.

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

#include <vector>

#include "CartesianPoint.h"

namespace HBTK {
	namespace Vtk {
		class VtkUnstructuredMeshHolder {
		public:
			VtkUnstructuredMeshHolder();

			// Vector containing the coordinates of each point in the mesh
			std::vector<HBTK::CartesianPoint3D> points;

			// The data structure representing the cells. Cell type is 
			// according to the VTK datasheet and is repetead in 
			// VTKInfo.cpp ( I should create enums ).
			struct cell_data {
				// Cell type
				int cell_type;
				// Constituant nodes in VTK file format order
				std::vector<int> node_ids;
			};
			std::vector<cell_data> cells;

			std::vector<int> check_consistant_node_counts();
			std::vector<int> check_valid_cell_nodes_ids();

			// Remove points that are included in points multiple times.
			// std::vector<int> merge_repeated_points();
		};
	}
}