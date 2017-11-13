#pragma once
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

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace HBTK {
	namespace Gmsh {
		class GmshWriter
		{
		public:

			// Add a physical group.
			// Returns -1 for physical group id already exists
			int add_physical_group(int id, int dimensions, std::string name);

			// Add a node of with id number id at x, y, z
			// Returns -1 for node id already exists.
			int add_node(int id, double x, double y, double z);

			// Add an element of ele_type (see gmsh element ids) with nodes node_ids.
			// Returns +ve: the assigned element number
			// Returns -1: failed!
			// First overload: do not make part of any physical group
			int add_element(int ele_type, const std::vector<int> & node_ids);
			// Second overload: make part of physical groups given in vector phys_grps.
			int add_element(int ele_type, const std::vector<int> & node_ids, const std::vector<int> & phys_groups);

			// Write out file to path:
			bool write(std::string path);
			bool write(std::ofstream & output_stream);

		private:
			struct element {
				int element_type;
				std::unique_ptr<std::vector<int>> nodes;
				std::unique_ptr<std::vector<int>> phys_groups;
			};

			struct physical_group {
				int dimensions;
				std::string name;
			};

			struct node_coordinate {
				double x, y, z;
			};

			std::map<int, element> m_elements;
			std::map<int, physical_group> m_physical_groups;
			std::map<int, node_coordinate> m_nodes;
		};
	}
} // END namespace HBTK
