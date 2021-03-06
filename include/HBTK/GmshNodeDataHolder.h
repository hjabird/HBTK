#pragma once
/*////////////////////////////////////////////////////////////////////////////
GmshNodeDataHolder.h

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

#include <string>
#include <unordered_map>
#include <vector>

namespace HBTK {
	namespace Gmsh {
		class GmshMeshHolder;

		class GmshNodeDataHolder {
		public:
			GmshNodeDataHolder();
			~GmshNodeDataHolder();

			std::string & data_description();
			const std::string & data_description() const;

			int & time_step();
			const int & time_step() const;

			double & time();
			const double & time() const;

			int number_of_node_data_points();
			bool node_data_exists(int node_tag);
			std::vector<double> & node_data(int node_tag);
			void add_node_data(int node_tag, std::vector<double> node_data);
			void remove_node_data(int node_tag);

			std::vector<int> check_correct_node_data_length();
			std::vector<int> check_consistant(GmshMeshHolder & mesh);

			enum data_type {
				scalar,
				vector,
				tensor2
			};
			data_type & node_data_type();
			
		private:
			std::string m_node_data_name;
			double m_time;
			int m_time_step;
			data_type m_node_data_type;
			std::unordered_map<int, std::vector<double>> m_node_data;

			// Expected number of values per node due according to node data type.
			int data_len();
			// A string of node data type.
			std::string data_type_str();
		};
	}
}