#include "stdafx.h"
#include "GmshWriter.h"
/*////////////////////////////////////////////////////////////////////////////
GmshWriter.h

Writes a gmsh .msh file.

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

#include <fstream>


int Gmsh::GmshWriter::add_physical_group(int id, int dimensions, std::string name)
{
	if (m_physical_groups.find(id) == m_physical_groups.end()) {
		m_physical_groups.emplace(id, physical_group{ dimensions, name });
		return 0;
	}
	else {
		return -1;
	}
}


int Gmsh::GmshWriter::add_node(int id, double x, double y, double z)
{
	if (m_nodes.find(id) == m_nodes.end()) {
		m_nodes.emplace(id, node_coordinate{ x, y, z });
		return 0;
	}
	else {
		return -1;
	}
}


int Gmsh::GmshWriter::add_element(int ele_type, const std::vector<int> & node_ids)
{
	return add_element(ele_type, node_ids, std::vector<int>());
}


int Gmsh::GmshWriter::add_element(int ele_type, const std::vector<int> & node_ids, const std::vector<int> & phys_groups)
{
	int id = m_elements.size();
	m_elements.emplace(id, element{ ele_type,
		std::make_unique<std::vector<int>>(node_ids),
		std::make_unique<std::vector<int>>(phys_groups) });
	return 0;
}

bool Gmsh::GmshWriter::write(std::string path) {
	std::ofstream output_stream(path);
	return write(output_stream);
}


bool Gmsh::GmshWriter::write(std::ofstream & output_stream)
{
	if (!output_stream) { return false; }

	// Write header
	output_stream << "$MeshFormat\n2.2 0 0\n$EndMeshFormat\n";
	// Write physical names
	if (m_physical_groups.size()) {
		output_stream << "$PhysicalNames\n";
		for (auto const & phy_grp: m_physical_groups) {
			output_stream << phy_grp.first << " "; // key - physical group id.
			output_stream << phy_grp.second.dimensions << " ";
			output_stream << "\"" << phy_grp.second.name << "\"\n";
		}
		output_stream << "$EndPhysicalNames\n";
	}
	// Write nodes
	if (m_nodes.size()) {
		output_stream << "$Nodes\n";
		for (auto const & node: m_nodes) {
			output_stream << node.first << " "; // key - node number
			output_stream << node.second.x << " " << node.second.y << " "
				<< node.second.z << "\n";
		}
		output_stream << "$EndNodes\n";
	}
	// Write elements
	if (m_elements.size()) {
		output_stream << "$Elements\n";
		for (auto const & elem : m_elements) {
			output_stream << elem.first << " "; // key - element number
			output_stream << elem.second.element_type << " ";
			output_stream << (int)elem.second.phys_groups->size() << " "; // Number of physical groups
			for (int const & grp_id : *(elem.second.phys_groups)) {
				output_stream << grp_id << " ";
			}
			for (int const & node_id : *(elem.second.nodes)) {
				output_stream << node_id << " ";
			}
			output_stream << "\n";
		}
		output_stream << "$EndElements\n";
	}

	output_stream.close();
	return true;
}
