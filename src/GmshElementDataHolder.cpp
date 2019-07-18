#include "GmshElementDataHolder.h"
/*////////////////////////////////////////////////////////////////////////////
GmshElementDataHolder.cpp

An object that represent the Element data that a Gmsh .msh file can hold.

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

HBTK::Gmsh::GmshElementDataHolder::GmshElementDataHolder()
	: m_element_data_type(scalar)
{
}

HBTK::Gmsh::GmshElementDataHolder::~GmshElementDataHolder()
{
}

/// \brief Access the string describing the dataset
std::string & HBTK::Gmsh::GmshElementDataHolder::data_description()
{
	return m_element_data_name;
}

/// \brief Access the string describing the dataset.
const std::string & HBTK::Gmsh::GmshElementDataHolder::data_description() const
{
	return m_element_data_name;
}

/// \brief Access the int representing the time_step number of the data
int & HBTK::Gmsh::GmshElementDataHolder::time_step()
{
	return m_time_step;
}

/// \brief Access the int representing the time_step number of the data
const int & HBTK::Gmsh::GmshElementDataHolder::time_step() const
{
	return m_time_step;
}

/// \brief Access the int representing the time of the data
double & HBTK::Gmsh::GmshElementDataHolder::time()
{
	return m_time;
}

/// \brief Access the int representing the time of the data
const double & HBTK::Gmsh::GmshElementDataHolder::time() const
{
	return m_time;
}

/// \brief Returns the number of elements data recorded.
int HBTK::Gmsh::GmshElementDataHolder::number_of_element_data_points()
{
	return (int)m_element_data.size();
}

/// \brief Returns true if element data for a element donated by element_tag 
/// has been set.
bool HBTK::Gmsh::GmshElementDataHolder::element_data_exists(int element_tag)
{
	return m_element_data.count(element_tag);
}

/// \brief Returns the data associated with a given element.
std::vector<double>& HBTK::Gmsh::GmshElementDataHolder::element_data(int element_tag)
{
	assert(element_data_exists(element_tag));
	return m_element_data[element_tag];
}

/// \brief Add data to element donated by element_tag to the data set. element_data
/// must be of correct length (1 for scalar data, 3 for vect, 9 for second
/// order tensor) as defined by element_data_type(). Throws std::domain_error
/// otherwise.
/// asserts if element data already exists.
void HBTK::Gmsh::GmshElementDataHolder::add_element_data(int element_tag, std::vector<double> element_data)
{
	assert(!element_data_exists(element_tag));
	if ((int)element_data.size() != data_len()) {
		throw std::domain_error(
			"HBTK::Gmsh::GmshElementDataHolder the size of the element data vector ("
			+ std::to_string((int)element_data.size()) + ") did not corespond "
			"to the data type (" + data_type_str() + ") expecting length "
			+ std::to_string(data_len()) + ". " __FILE__
			+ " : " + std::to_string(__LINE__)
		);
	}
	m_element_data[element_tag] = element_data;
}

/// \brief Remove element data associate with element_tag.
void HBTK::Gmsh::GmshElementDataHolder::remove_element_data(int element_tag)
{
	assert(element_data_exists(element_tag));
	m_element_data.erase(element_tag);
}

/// \brief Returns a vector of element_tags for which the corresponding data 
/// vector is of the incorrect size of the selected data type.
std::vector<int> HBTK::Gmsh::GmshElementDataHolder::check_correct_element_data_length()
{
	std::vector<int> problem_element_tags;
	for (auto & element : m_element_data) {
		if ((int)element.second.size() != data_len()) {
			problem_element_tags.push_back(element.first);
		}
	}
	return std::vector<int>();
}

/// \brief Returns a vector of element tags used by this dataset that
/// are not present in the mesh object.
std::vector<int> HBTK::Gmsh::GmshElementDataHolder::check_consistant(GmshMeshHolder & mesh)
{
	std::vector<int> problem_elements;
	for (auto & element : m_element_data) {
		if (!mesh.element_tag_exists(element.first)) {
			problem_elements.push_back(element.first);
		}
	}
	return problem_elements;
}

/// \brief returns the element data type.
///
/// Set to scalar (1 component), vector (3 component) or second order tensor (9
/// component).
HBTK::Gmsh::GmshElementDataHolder::data_type & HBTK::Gmsh::GmshElementDataHolder::element_data_type()
{
	return m_element_data_type;
}


int HBTK::Gmsh::GmshElementDataHolder::data_len()
{
	int len;
	switch (m_element_data_type) {
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

std::string HBTK::Gmsh::GmshElementDataHolder::data_type_str()
{
	std::string str;
	switch (m_element_data_type) {
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
