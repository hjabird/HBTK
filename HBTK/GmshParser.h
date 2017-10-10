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

// This namespace is liable to be problematic.
#ifdef WIN32
namespace fs = std::experimental::filesystem::v1;
#else
namespace fs = std::filesystem;
#endif


namespace Parsers {

	class GmshParser {

	public:
		// Remember to see full Doxygen documentation!

		// For these, the user supplies a list of function to execute on each node
		// to parse. Functions are executed according to the order in the vector, conditionally
		// if the previous function returned true.
		// Add a function to execute for phys names on parsing. 
		void add_phys_name_function(std::function<bool(int, int, std::string)> func);
		// Add a function to execute for nodes on parsing.
		void add_node_function(std::function<bool(int, double, double, double)> func);
		// Add a function to execute for elements on parsing.
		void add_elem_function(std::function<bool(int, int, std::vector<int>, std::vector<int>)> func);

		// Parse based on file system path.
		void parse(fs::path file_path);
		// Parse based on input file stream.
		void parse(std::ifstream & input_stream);
		void parse(std::ifstream & input_stream, std::ofstream & error_stream);	

	private:

		enum file_section {
			no_section,
			file_info,
			nodes,
			elements,
			physical_names,
			unsupported,
			invalid
		};

		// Vectors containing the functions the user wants to execute.
		std::vector<std::function<bool(int, int, std::string)>> phys_name_funcs;
		std::vector<std::function<bool(int, double, double, double)>> node_funcs;
		std::vector<std::function<bool(int, int, std::vector<int>, std::vector<int>)>> elem_funcs;

		// Parse a line starting with "$".
		file_section parse_file_section(std::string, file_section);
		// Pares a line in the nodes section.
		void parse_node_line(std::string line);
		// Parse a line in the elements section.
		void parse_elem_line(std::string);
		// Parse a line in physical names section.
		void parse_phys_name_line(std::string);
		// Separate a string into substrings by whitespace.
		std::vector<std::string> tokenise(std::string);

		// Print the name of file_section given to output file stream.
		void print_section_name(file_section, std::ofstream &);
	};
}

