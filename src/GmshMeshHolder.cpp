#include "GmshMeshHolder.h"
/*////////////////////////////////////////////////////////////////////////////
GmshMeshHolder.h

An object that represent the mesh that a Gmsh .msh file can hold.

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

#include <cassert>

#include "GmshInfo.h"

HBTK::Gmsh::GmshMeshHolder::GmshMeshHolder()
{
}

HBTK::Gmsh::GmshMeshHolder::~GmshMeshHolder()
{
}

/// \brief number of nodes in container.
int HBTK::Gmsh::GmshMeshHolder::number_of_nodes()
{
	return (int) m_nodes.size();
}

/// \brief returns a vector containing all the node tags that have been
/// registered.
std::vector<int> HBTK::Gmsh::GmshMeshHolder::get_all_node_tags()
{ 
	std::vector<int> tags;
	tags.reserve(number_of_nodes());
	for (auto & node : m_nodes) tags.push_back(node.first);
	return tags;
}

/// \brief returns the coordinate of a node given by node_tag.
HBTK::CartesianPoint3D & HBTK::Gmsh::GmshMeshHolder::node(int node_tag)
{
	assert(node_tag_exists(node_tag));
	return m_nodes[node_tag];
}

/// \brief Returns true if a node with given node_tag has been set.
bool HBTK::Gmsh::GmshMeshHolder::node_tag_exists(int node_tag)
{
	return (m_nodes.count(node_tag) == 0 ? false : true);
}

/// \brief Add a new node with given node_tag and coordinate to container. 
/// asserts if given node_tag is already registered.
void HBTK::Gmsh::GmshMeshHolder::add_node(int node_tag, CartesianPoint3D coordinate)
{
	assert(!node_tag_exists(node_tag));
	m_nodes[node_tag] = coordinate;
}

/// \brief Remove node and coordinate with given node_tag from container.
/// asserts if node_tag does not exist.
void HBTK::Gmsh::GmshMeshHolder::remove_node(int node_tag)
{
	assert(node_tag_exists(node_tag));
	m_nodes.erase(node_tag);
}

/// \brief Returns the number of elements in container.
int HBTK::Gmsh::GmshMeshHolder::number_of_elements()
{
	return m_elements.size();
}

/// \brief Returns a vector containing all the node tags that have been 
/// registered in the container.
std::vector<int> HBTK::Gmsh::GmshMeshHolder::get_all_element_tags()
{
	std::vector<int> tags;
	tags.reserve(number_of_elements());
	for (auto & element : m_elements) tags.push_back(element.first);
	return tags;
}

/// \brief Get the gmsh element id (the number corresponding to element
/// topology) for a given element_tag
int HBTK::Gmsh::GmshMeshHolder::element_id(int element_tag)
{
	assert(element_tag_exists(element_tag));
	return m_elements[element_tag].element_id;
}

/// \brief Get the vector of node_tags associated with an element_tag
std::vector<int> HBTK::Gmsh::GmshMeshHolder::element_node_tags(int element_tag)
{
	assert(element_tag_exists(element_tag));
	return m_elements[element_tag].node_tags;
}

/// \brief  Get a vector of coordinates associated with the nodes of an
/// element denoted by an element_tag.
std::vector<HBTK::CartesianPoint3D> HBTK::Gmsh::GmshMeshHolder::element_nodes(int element_tag)
{
	assert(element_tag_exists(element_tag));
	std::vector<int> node_tags = m_elements[element_tag].node_tags;
	std::vector<CartesianPoint3D> nodes(node_tags.size());
	for (int i = 0; i < (int)node_tags.size(); i++) {
		nodes[i] = node(node_tags[i]);
	}
	return nodes;
}

/// \brief Get a vector of group_tags corresponding to the groups 
/// containing element donated by element_tag.
std::vector<int> HBTK::Gmsh::GmshMeshHolder::element_groups(int element_tag)
{
	assert(element_tag_exists(element_tag));
	std::vector<int> groups;
	for (auto & group : m_groups) {
		if (group.second.element_tags.count(element_tag) == 1) groups.push_back(group.first);
	}
	return groups;
}

/// \brief Returns true if an element donated by element_tag exists.
bool HBTK::Gmsh::GmshMeshHolder::element_tag_exists(int element_tag)
{
	return m_elements.count(element_tag);
}

/// \param element_tag an integer that uniquely identifies an element.
/// \param element_id an integer that describes the element type / topology.
/// \param node_tags a vector of node_tags that define the shape of the element.
/// \param group_tags a vector of group_tags corresponding to the groups an element
/// is in.
///
/// \brief Add an element to the container.
void HBTK::Gmsh::GmshMeshHolder::add_element(int element_tag, int element_id, 
	std::vector<int> node_tags, std::vector<int> group_tags)
{
	assert(!element_tag_exists(element_tag));
	for(auto group_tag: group_tags) add_element_to_group(group_tag, element_tag);
	struct element ele;
	ele.element_id = element_id;
	ele.node_tags = node_tags;
	m_elements[element_tag] = ele;
	return;
}

/// \brief Remove element donated by element_tag.
void HBTK::Gmsh::GmshMeshHolder::remove_element(int element_tag)
{
	assert(element_tag_exists(element_tag));
	m_elements.erase(element_tag);
	for (auto & group : m_groups) {
		group.second.element_tags.erase(element_tag);
	}
	return;
}

/// \brief Number of physical groups registered.
int HBTK::Gmsh::GmshMeshHolder::number_of_groups()
{
	return m_groups.size();
}

/// \brief returns a vector of group_tags donating physical groups.
std::vector<int> HBTK::Gmsh::GmshMeshHolder::get_all_group_tags()
{
	std::vector<int> tags;
	tags.reserve(number_of_groups());
	for (auto & group : m_groups) tags.push_back(group.first);
	return tags;
}

/// \brief returns the name of the group donated by group_tag
std::string HBTK::Gmsh::GmshMeshHolder::group_name(int group_tag)
{
	assert(group_tag_exists(group_tag));
	return m_groups[group_tag].name;
}

/// \brief returns group_tag of a group with name name.
int HBTK::Gmsh::GmshMeshHolder::group_id(std::string name)
{
	assert(group_name_exists(name));
	return m_group_names_lookup[name];
}

/// \brief Returns the number of physical dimensions of the 
/// group donated by group_tag.
int HBTK::Gmsh::GmshMeshHolder::group_dimensions(int group_tag)
{
	assert(group_tag_exists(group_tag));
	return m_groups[group_tag].dimensions;
}

/// \brief Returns the set of elements in a group donated by group_tag.
std::unordered_set<int>& HBTK::Gmsh::GmshMeshHolder::group_elements(int group_tag)
{
	assert(group_tag_exists(group_tag));
	return m_groups[group_tag].element_tags;
}

/// \brief Returns true if element donated by element tag is in group donated by
/// group_tag.
bool HBTK::Gmsh::GmshMeshHolder::element_in_group(int group_tag, int element_tag)
{
	assert(group_tag_exists(group_tag));
	return m_groups[group_tag].element_tags.count(element_tag);
}

/// \brief Add element donated by element_tag to group donated by group_tag.
/// asserts if group_tag does not exist.
void HBTK::Gmsh::GmshMeshHolder::add_element_to_group(int group_tag, int element_tag)
{
	assert(group_tag_exists(group_tag));
	m_groups[group_tag].element_tags.emplace(element_tag);
}

/// \brief Remove element donated by element_tag from group donated by 
/// group_tag. asserts if group does not exist.
void HBTK::Gmsh::GmshMeshHolder::remove_element_from_group(int group_tag, int element_tag)
{
	assert(group_tag_exists(group_tag));
	m_groups[group_tag].element_tags.erase(element_tag);
}

/// \brief Returns true if the given group_tag has been registered.
bool HBTK::Gmsh::GmshMeshHolder::group_tag_exists(int group_tag)
{
	return m_groups.count(group_tag);
}

/// \brief Returns true if a group with given name has been registed.
bool HBTK::Gmsh::GmshMeshHolder::group_name_exists(std::string name)
{
	return m_group_names_lookup.count(name);
}

/// \param group_tag a tag to associate with the group.
/// \param group_name a name for the group
/// \param group_dimensions the physical number of dimensions of the group.
///
/// \brief add a group to the container.
void HBTK::Gmsh::GmshMeshHolder::add_group(int group_tag, 
	std::string group_name, int group_dimensions)
{
	assert(!group_tag_exists(group_tag));
	assert(!group_name_exists(group_name));
	struct group grp;
	grp.name = group_name;
	grp.dimensions = group_dimensions;
	m_groups[group_tag] = grp;
	m_group_names_lookup[group_name] = group_tag;
}

/// \brief remove group indicated by group_tag from container.
void HBTK::Gmsh::GmshMeshHolder::remove_group(int group_tag)
{
	assert(group_tag_exists(group_tag));
	m_group_names_lookup.erase(m_groups[group_tag].name);
	m_groups.erase(group_tag);
}

/// \brief Returns a vector of element_tags indicating the elements where
/// the element_id (the element type / topology) does not match the number of
/// nodes assigned to it.
std::vector<int> HBTK::Gmsh::GmshMeshHolder::check_element_correct_node_count()
{
	std::vector<int> problem_elements;
	for (auto & element : m_elements) {
		int ele_tag = element.first;
		int correct_count = Gmsh::element_node_count(element.second.element_id);
		if ((int)element.second.node_tags.size() != correct_count) {
			problem_elements.push_back(ele_tag);
		}
	}
	return problem_elements;
}

/// \brief Returns a vector of element_tags indicating the elements 
/// which refer to node_tags that do not exist.
std::vector<int> HBTK::Gmsh::GmshMeshHolder::check_element_nodes_exist()
{
	std::vector<int> problem_elements;
	for (auto & element : m_elements) {
		int ele_tag = element.first;
		bool good = true;
		for (int node_tag : element.second.node_tags) {
			if (!node_tag_exists(node_tag)) {
				good = false;
			}
		}
		if (good == false) {
			problem_elements.push_back(ele_tag);
		}
	}
	return problem_elements;
}

/// \brief returns a GmshParser that has been initialised to read to
/// this GmshMeshHolder object.
HBTK::Gmsh::GmshParser HBTK::Gmsh::GmshMeshHolder::get_parser()
{
	GmshParser parser;
	parser.add_node_function(
		[&](int tag, double x, double y, double z)->bool {
		add_node(tag, CartesianPoint3D({ x, y, z }));
		return true; });
	parser.add_elem_function(
		[&](int tag, int id, std::vector<int> phy_grp, std::vector<int> nodes)->bool {
		add_element(tag, id, nodes, phy_grp);
		return true; });
	parser.add_phys_name_function(
		[&](int group_tag, int group_dimensions, std::string group_name)->bool {
			add_group(group_tag, group_name, group_dimensions);
			return true; });
	return parser;
}

/// \brief Returns a GmshWriter that has been initialised to 
/// write out the data of this GmshMeshHolder.
HBTK::Gmsh::GmshWriter HBTK::Gmsh::GmshMeshHolder::get_writer()
{
	GmshWriter writer;
	for (auto & phy_grp : m_groups) {
		writer.add_physical_group(phy_grp.first, phy_grp.second.dimensions,
			phy_grp.second.name);
	}
	for (auto & node : m_nodes) {
		writer.add_node(node.first, node.second.x(), node.second.y(), node.second.z());
	}
	for (auto & element : m_elements) {
		writer.add_element(element.second.element_id, element.second.node_tags);
	}
	return writer;
}
