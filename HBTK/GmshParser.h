#pragma once
/*////////////////////////////////////////////////////////////////////////////
GmshParser.h

Parse a GMSH .msh file

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

#include <functional>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include "BasicParser.h"

// This namespace is liable to be problematic.
#ifdef _MSC_VER
namespace fs = std::experimental::filesystem::v1;
#else
namespace fs = std::filesystem;
#endif


namespace Gmsh {

	class GmshParser :
		public Parsers::BasicParser<Gmsh::GmshParser>
	{

	public:
		// Remember to see full Doxygen documentation!

		// For these, the user supplies a list of function to execute on each node
		// to parse. Functions are executed according to the order in the vector, conditionally
		// if the previous function returned true.
		// Add a function to execute for phys names on parsing. 
		// [Tag, dimensions, string]
		void add_phys_name_function(std::function<bool(int, int, std::string)> func);
		// Add a function to execute for nodes on parsing.
		// [tag, x, y, z]
		void add_node_function(std::function<bool(int, double, double, double)> func);
		// Add a function to execute for elements on parsing.
		// [tag, type, phys_group_tags, node_tags]
		void add_elem_function(std::function<bool(int, int, std::vector<int>, std::vector<int>)> func);
		
		// To set the parser going, one of the following may be used (inherited from BasicParser):
		// void parse(fs::path file_path);
		// void parse(std::ifstream & input_stream);
		// void parse(std::ifstream & input_stream, std::ofstream & error_stream);	
		// Where file_path is the path to the .msh file, or ifstream is the file
		// stream already opened. The error output stream can be set using ofstream,
		// by using the ifstream, ofstream overload. Otherwise stderr will be used.
		
		
	private:
		friend class Parsers::BasicParser<GmshParser>;
		// Generally, looking at http://gmsh.info/doc/texinfo/gmsh.html is useful!

		// Call main parser
		void main_parser(std::ifstream & input_stream, std::ofstream & error_stream);

		enum file_section {
			no_section,
			file_info,
			nodes,
			elements,
			physical_names,
			unsupported,
			invalid
		};

		// State is needed in binary parsing.
		struct binary_parse_info {
			bool parsing_binary;
			int ele_type;
			int ele_tag_count;
			int ele_nodes;
			int count_var;
		};

		// Information about the file format.
		struct file_format_info {
			double version;
			bool binary;
			size_t data_size;
			bool matching_endian;
		};

		// Vectors containing the functions the user wants to execute.
		std::vector<std::function<bool(int, int, std::string)>> phys_name_funcs;
		std::vector<std::function<bool(int, double, double, double)>> node_funcs;
		std::vector<std::function<bool(int, int, std::vector<int>, std::vector<int>)>> elem_funcs;

		// Parse a line starting with "$".
		file_section parse_file_section(std::string, file_section);
		// Pares a line in the nodes section.
		void parse_node_line(std::string line);
		void parse_node_line_binary(std::ifstream & input_stream, struct binary_parse_info & b_info);
		// Parse a line in the elements section.
		void parse_elem_line(std::string);
		void parse_elem_binary_spec(std::ifstream & input_stream, struct binary_parse_info & b_info);
		void parse_elem_binary(std::ifstream & input_stream, struct binary_parse_info & b_info);
		// Parse a line in physical names section.
		void parse_phys_name_line(std::string);
		// Parse the file format information section
		void parse_file_info(std::string this_line, binary_parse_info & b_info, file_format_info & f_info);
		void parse_file_binary_endian(std::ifstream & input_stream, struct binary_parse_info & b_info, 
			file_format_info & f_info);

		// Get number of nodes for element type.
		int element_type_node_count(int type);
		// Get whether we're expecting to parse a object count line.
		bool expecting_object_count(file_section, int);

		// Print the name of file_section given to output file stream.
		void print_section_name(file_section, std::ofstream &);
	};
}

