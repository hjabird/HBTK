#include "VtkUnstructuredMeshHolder.h"

#include "Checks.h"
#include "VtkInfo.h"

HBTK::Vtk::VtkUnstructuredMeshHolder::VtkUnstructuredMeshHolder()
{
}

std::vector<int> HBTK::Vtk::VtkUnstructuredMeshHolder::check_consistant_node_counts()
{
	std::vector<int> problem_cells;

	for (int i = 0; i < (int)cells.size(); i++) {
		if (element_node_count(cells[i].cell_type) != (int)cells[i].node_ids.size()) {
			problem_cells.push_back(i);
		}
	}
	return problem_cells;
}

std::vector<int> HBTK::Vtk::VtkUnstructuredMeshHolder::check_valid_cell_nodes_ids()
{
	std::vector<int> problem_cells;
	int max_pnt = (int)points.size();

	for (int i = 0; i < (int)cells.size(); i++) {
		for (const int pid : cells[i].node_ids) {
			if (check_in_range(pid, 0, max_pnt)) {
				problem_cells.push_back(i);
				continue;
			}
		}
	}
	return problem_cells;
}
