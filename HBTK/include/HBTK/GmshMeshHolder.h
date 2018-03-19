#pragma once
/*////////////////////////////////////////////////////////////////////////////
GmshMeshHolder.cpp

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

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CartesianPoint.h"
#include "GmshParser.h"
#include "GmshWriter.h"

namespace HBTK {
	namespace Gmsh {
		class GmshMeshHolder {
		public:
			GmshMeshHolder();
			~GmshMeshHolder();

			int number_of_nodes();
			std::vector<int> get_all_node_tags();
			CartesianPoint3D & node(int node_tag);
			bool node_tag_exists(int node_tag);
			void add_node(int node_tag, CartesianPoint3D coordinate);
			void remove_node(int node_tag);

			int number_of_elements();
			std::vector<int> get_all_element_tags();
			int element_id(int element_tag);
			std::vector<int> element_node_tags(int element_tag);
			std::vector<CartesianPoint3D> element_nodes(int element_tag);
			std::vector<int> element_groups(int element_tag);
			bool element_tag_exists(int element_tag);
			void add_element(int element_tag, int element_id, 
				std::vector<int> node_tags, std::vector<int> group_tags);
			void remove_element(int element_tag);
			
			int number_of_groups();
			std::vector<int> get_all_group_tags();
			std::string group_name(int group_tag);
			int group_id(std::string name);
			int group_dimensions(int group_tag);
			std::unordered_set<int> & group_elements(int group_tag);
			bool element_in_group(int group_tag, int element_tag);
			void add_element_to_group(int group_tag, int element_tag);
			void remove_element_from_group(int group_tag, int element_tag);
			bool group_tag_exists(int group_tag);
			bool group_name_exists(std::string name);
			void add_group(int group_tag, std::string group_name, int group_dimensions);
			void remove_group(int group_tag);

			std::vector<int> check_element_correct_node_count();
			std::vector<int> check_element_nodes_exist();

			GmshParser get_parser();
			GmshWriter get_writer();

			struct element {
				int element_id;
				std::vector<int> node_tags;
			};

			struct group {
				std::string name;
				int dimensions;
				std::unordered_set<int> element_tags;
			};

		private:
			// Nodes: key is node_tag, value is coordinate.
			std::unordered_map<int, CartesianPoint3D> m_nodes;

			// Elements: Key is element_tag, returns a pair of element type (int) 
			// and the node_tags that give the nodes of that element.
			std::unordered_map<int, struct element> m_elements;

			// Physical groups: look up by group id. Returns group name 
			// and set of element tags of elements in that group.
			std::unordered_map<int, struct group> m_groups;
			// And lookup group tag by group name
			std::unordered_map<std::string, int> m_group_names_lookup;

		};
	}

}