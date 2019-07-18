#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkUnstructuredDataset.h

Information on Vtk elements

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
#include <unordered_map>

#include "CartesianVector.h"
#include "VtkUnstructuredMeshHolder.h"

namespace HBTK {
	namespace Vtk {
		class VtkUnstructuredDataset {
		public:
			
			VtkUnstructuredMeshHolder mesh;
			
			// Point data - index linked correspondence to points in mesh.
			// data name is key.
			std::unordered_map<std::string, std::vector<double>> scalar_point_data;
			std::unordered_map<std::string, std::vector<int>> integer_point_data;
			std::unordered_map<std::string, std::vector<HBTK::CartesianVector3D>> vector_point_data;

			// Cell data - index linked correspondence to cells in mesh
			// data name is key.
			std::unordered_map<std::string, std::vector<double>> scalar_cell_data;
			std::unordered_map<std::string, std::vector<int>> integer_cell_data;
			std::unordered_map<std::string, std::vector<HBTK::CartesianVector3D>> vector_cell_data;
		};
	}
}