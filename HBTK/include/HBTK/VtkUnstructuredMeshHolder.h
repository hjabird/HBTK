#pragma once

#include "VtkDataArray.h"

namespace HBTK {
	namespace Vtk {
		class VtkUnstructuredMeshHolder {
		public:
			VtkUnstructuredMeshHolder();

			VtkDataArray<HBTK::CartesianVector3D> points;
			VtkDataArray<int> cell_types;
			VtkDataArray<int> cell_nodes;
			VtkDataArray<int> cell_offsets;
		};
	}
}