#include "GmshNodeDataHolder.h"
/*////////////////////////////////////////////////////////////////////////////
GmshNodeDataHolder.cpp

An object that represent the node data that a Gmsh .msh file can hold.

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
#include <exception>

#include "GmshMeshHolder.h"

HBTK::Gmsh::GmshNodeDataHolder::GmshNodeDataHolder()
	: m_node_data_type(scalar)
{
}

HBTK::Gmsh::GmshNodeDataHolder::~GmshNodeDataHolder()
{
}

/// \brief Access the string describing the dataset
std::string & HBTK::Gmsh::GmshNodeDataHolder::data_description()
{
	return m_node_data_name;
}

/// \brief Access the string describing the dataset.
const std::string & HBTK::Gmsh::GmshNodeDataHolder::data_description() const
{
	return m_node_data_name;
}

/// \brief Access the int representing the time_step number of the data
int & HBTK::Gmsh::GmshNodeDataHolder::time_step()
{
	return m_time_step;
}

/// \brief Access the int representing the time_step number of the data
const int & HBTK::Gmsh::GmshNodeDataHolder::time_step() const
{
	return m_time_step;
}

/// \brief Access the int representing the time of the data
double & HBTK::Gmsh::GmshNodeDataHolder::time()
{
	return m_time;
}

/// \brief Access the int representing the time of the data
const double & HBTK::Gmsh::GmshNodeDataHolder::time() const
{
	return m_time;
}

/// \brief Returns the number of nodes data recorded.
int HBTK::Gmsh::GmshNodeDataHolder::number_of_node_data_points()
{
	return (int)m_node_data.size();
}

/// \brief Returns true if node data for a node donated by node_tag 
/// has been set.
bool HBTK::Gmsh::GmshNodeDataHolder::node_data_exists(int node_tag)
{
	return m_node_data.count(node_tag);
}

/// \brief Returns the data associated with a given node.
std::vector<double>& HBTK::Gmsh::GmshNodeDataHolder::node_data(int node_tag)
{
	assert(node_data_exists(node_tag));
	return m_node_data[node_tag];
}

/// \brief Add data to node donated by node_tag to the data set. node_data
/// must be of correct length (1 for scalar data, 3 for vect, 9 for second
/// order tensor) as defined by node_data_type(). Throws std::domain_error
/// otherwise.
/// asserts if node data already exists.
void HBTK::Gmsh::GmshNodeDataHolder::add_node_data(int node_tag, std::vector<double> node_data)
{
	assert(!node_data_exists(node_tag));
	if ((int)node_data.size() != data_len()) {
		throw std::domain_error(
			"HBTK::Gmsh::GmshNodeDataHolder the size of the node data vector ("
			+ std::to_string((int)node_data.size()) + ") did not corespond "
			"to the data type (" + data_type_str() + ") expecting length "
			+ std::to_string(data_len()) + ". " __FILE__ 
			+ " : " + std::to_string(__LINE__)
		);
	}
	m_node_data[node_tag] = node_data;
}

/// \brief Remove node data associate with node_tag.
void HBTK::Gmsh::GmshNodeDataHolder::remove_node_data(int node_tag)
{
	assert(node_data_exists(node_tag));
	m_node_data.erase(node_tag);
}

/// \brief Returns a vector of node_tags for which the corresponding data 
/// vector is of the incorrect size of the selected data type.
std::vector<int> HBTK::Gmsh::GmshNodeDataHolder::check_correct_node_data_length()
{
	std::vector<int> problem_node_tags;
	for (auto & node : m_node_data) {
		if ((int)node.second.size() != data_len()) {
			problem_node_tags.push_back(node.first);
		}
	}
	return std::vector<int>();
}

/// \brief Returns a vector of node tags used by this dataset that
/// are not present in the mesh object.
std::vector<int> HBTK::Gmsh::GmshNodeDataHolder::check_consistant(GmshMeshHolder & mesh)
{ 
	std::vector<int> problem_nodes;
	for (auto & node : m_node_data) {
		if (!mesh.node_tag_exists(node.first)) {
			problem_nodes.push_back(node.first);
		}
	}
	return problem_nodes;
}

/// \brief returns the node data type.
///
/// Set to scalar (1 component), vector (3 component) or second order tensor (9
/// component).
HBTK::Gmsh::GmshNodeDataHolder::data_type & HBTK::Gmsh::GmshNodeDataHolder::node_data_type()
{
	return m_node_data_type;
}


int HBTK::Gmsh::GmshNodeDataHolder::data_len()
{
	int len;
	switch (m_node_data_type) {
	case scalar:
		len = 1;
		break;
	case vector:
		len = 3;
		break;
	case tensor2:
		len = 9;
		break;
	default:
		assert(false);
	}
	return len;
}

std::string HBTK::Gmsh::GmshNodeDataHolder::data_type_str()
{
	std::string str;
	switch (m_node_data_type) {
	case scalar:
		str = "scalar";
		break;
	case vector:
		str = "vector";
		break;
	case tensor2:
		str = "second order tensor";
		break;
	default:
		assert(false);
	}
	return str;
}
