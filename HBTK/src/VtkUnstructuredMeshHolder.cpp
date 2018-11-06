#include "VtkUnstructuredMeshHolder.h"

#include "CartesianPoint.h"
#include "Checks.h"
#include "VtkInfo.h"

#include <unordered_map>

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
/*
std::vector<int> HBTK::Vtk::VtkUnstructuredMeshHolder::merge_repeated_points()
{
	std::vector<int> new_positions(points.size());
	std::unordered_map<HBTK::CartesianPoint3D, int> encountered;
	int count = 0;
	for (int i = 0; i < (int)points.size(); i++) {
		if (encountered.count(points[i])) {
			new_positions[i] = encountered[points[i]];
		}
		else {
			encountered[points[i]] = count;
			new_positions[i] = count;
			count += 1;
		}
	}
	encountered.clear();
	
	std::vector<HBTK::CartesianPoint3D> new_points(count);
	for (int i = 0; i < (int)new_positions.size(); i++) {
		new_points[new_positions[i]] = points[i];
	}
	points = new_points;
	new_points.clear();

	for (auto & cell : cells) {
		for (int & node_id : cell.node_ids) {
			node_id = new_positions[node_id];
		}
	}

	return new_positions;
}
*/
