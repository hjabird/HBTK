#pragma once

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