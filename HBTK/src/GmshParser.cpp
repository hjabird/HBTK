#include "stdafx.h"
#include "GmshParser.h"
/*////////////////////////////////////////////////////////////////////////////
GmshParser.cpp

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

#include <cassert>
#include <cctype>
#include <algorithm>
#include <array>

/// \param func Function to be executed on finding physical name.
///
/// \brief Define a function to be executed each time a physical name
/// line is parsed in GMSH .msh file.
///
/// The GMSH file's physical name field has the following attributes:
///
/// tag: Integer - unique id for the physical name to be associated with.
///
/// dimensions: Integer - dimensions of the physical group (ie 1 is edge, 2 is surf...)
///
/// name: String - the name itself.
///
/// There fields are parsed and forwarded to a user function given here. It must be 
/// possible to cast the function as std::function<bool(int tag, int dimensions, std::string name)>
/// THe function should return a boolean. If the function returns false, the remaining 
/// functions in the functions to be invoked are not invoked.
///
/// For example
/// \code
/// #include "HBTK/GmshParser.h"
/// #include <map>
/// #include <string>
///
/// Gmsh::GmshParser my_parser;
/// std::map<int, std::string> phys_names // A map for names to be placed into.
///
/// //We need a function that does what we want with the correct signiture. Lambdas are a quick 
/// //way to do this as a demo.
/// auto phys_name_func = [&phys_names](int tag, int dimensions, std::string name)->bool
///	{
///		phys_names[tag] = name;
///		if(name == "Dont execute the second phys_name function")
///		{
///			return false;
///		} else {
///			return true;
///		}
///	};
///
/// // And a section function:
/// auto a_second_func = [](int tag, int dimensions, std::string name)->bool
/// { cout << "I found a physical name: " << name << ".\n"; return true; };
///
/// // Now add to our GMSH parser.
/// my_parser.add_phys_name_function(phys_name_func);
/// my_parser.add_phys_name_function(a_second_func);
///
/// // We can now run the parser:
/// my_parser.parse(<MY_MSH_FILE>);
/// \endcode 
void HBTK::Gmsh::GmshParser::add_phys_name_function(std::function<bool(int, int, std::string)> func)
{
	phys_name_funcs.emplace_back(func);
}

/// \param func Function to be executed on parsing a node.
///
/// \brief Define a function to be executed every time a node is parsed.
///
/// The GMSH file's physical name field has the following attributes:
///
/// tag: Integer - unique id for the node to be associated with. Not always consecutive!
///
/// Coordinates: Doubles * 3 - 3D cartesian coordinate of point
///
/// There fields are parsed and forwarded to a user function given here. It must be 
/// possible to cast the function as std::function<bool(int tag, double x, double y, double z)>
/// THe function should return a boolean. If the function returns false, the remaining 
/// functions in the functions to be invoked are not invoked.
///
/// For example
/// \code
/// #include "HBTK/GmshParser.h"
/// #include <map>
/// #include <array>
///
/// Gmsh::GmshParser my_parser;
/// std::map<int, std::array<double, 3>> nodes_in_volume; \\ location for our nodes of interest.
/// std::map<int, std::array<double, 3>> nodes_outside_volume; \\ some other nodes.
///
/// //We need a function that does what we want with the correct signiture. Lambdas are a quick 
/// //way to do this as a demo.
/// auto node_func_in_vol = [&nodes_in_volume](int tag, double x, double y, double z)->bool
///	{
///		if ( x + y + z < 10){
///			nodes_in_volume[tag] = {x,y,z};
///			return false;
///		} else { return true; }
///	};
///
/// // And a section function:
/// auto other_nodes_func = [&nodes_outside_volume](int tag, int dimensions, std::string name)->bool
/// { 
///		nodes_outside_volume[tag] = {x, y, z};
///		return true;
/// };
///
/// // Now add to our GMSH parser.
/// my_parser.add_node_function(node_func_in_vol);
/// my_parser.add_node_function(other_nodes_func);
///
/// // We can now run the parser:
/// my_parser.parse(<MY_MSH_FILE>);
/// \endcode 
void HBTK::Gmsh::GmshParser::add_node_function(std::function<bool(int, double, double, double)> func)
{
	node_funcs.emplace_back(func);
}


/// \param func Function to be executed on parsing an element.
///
/// \brief Define a function to be executed every time a element is parsed.
///
/// The GMSH file's physical name field has the following attributes:
///
/// tag: Integer - unique id for the node to be associated with. Not always consecutive!
///
/// Type: Integer - maps a list of nodes to nodes of a GMSH element type
///
/// Physical group tags: set of physical group integer tags
///
/// Nodes: Integer node tags - there are ordered, and correspond the the element Type and
/// the node tags given earlier.
///
/// There fields are parsed and forwarded to a user function given here. It must be 
/// possible to cast the function as std::function<bool(int, int, std::vector<int>, std::vector<int>)>,
/// where the ordering is tag, type, phys_groups, nodes.
/// THe function should return a boolean. If the function returns false, the remaining 
/// functions in the functions to be invoked are not invoked.
///
/// For example
/// \code
/// #include "HBTK/GmshParser.h"
/// #include <map>
/// #include <list>
/// #include <vector>
/// #include <tuple>
///
/// Gmsh::GmshParser my_parser;
/// std::map<int, std::tuple<int, int, std::vector<int>>> elements;
/// std::map<int, std::vector<int>> phy_elem_grp;
///
/// //We need a function that does what we want with the correct signiture. Lambdas are a quick 
/// //way to do this as a demo.
/// auto elem_grp_func = [&phy_elem_grp](int tag, int type, std::vector<int> phy_grps, std::vector<int> nodes)->bool{
///		for(auto grp = phy_grps.begin(); grp != phy_grps.end(); grp++){
///			phy_elem_grp[*grp].emplace_back(tag);
///		}
///		// We might want to ignore ungrouped elements for example:
///		if ( (int) phy_grps.size() == 0 ) { return false; }
///		else { return true; }
///	}
///
/// // And a function store our filtered elements:
/// auto elem_stor_func = [&elements](int tag, int type, std::vector<int> phy_grps, std::vector<int> nodes)->bool{
///		elements[tag] = std::tuple(tag, type, nodes);
///		return false;
///	}
///
/// // Now add to our GMSH parser.
/// my_parser.add_elem_function(elem_grp_func);
/// my_parser.add_elem_function(elem_stor_func);
///
/// // We can now run the parser:
/// my_parser.parse(<MY_MSH_FILE>);
/// \endcode 
void HBTK::Gmsh::GmshParser::add_elem_function(std::function<bool(int, int, std::vector<int>, std::vector<int>)> func)
{
	elem_funcs.emplace_back(func);
}

/// \param file_path the absolute path to file to be parsed.
/// 
/// \brief Set the parser going on file defined by file_path
///
/// The easiest way of choosing a file to be parsed. The file 
/// path given is opened and parsed according to the functions the 
/// user has already given. Any error messages will go to stderr
///
/// Eg:
/// \code
/// #include "HBTK/GmshParser.h"
///
/// Gmsh::GmshParser my_parser;
///
/// // Add functions to execute on parsing here
/// // ...
/// my_parser.add_node_function(my_node_func);
/// my_parser.add_elem_function(my_elem_func);
/// //..
///
/// // We can now run the parser:
/// my_parser.parse(<MY_MSH_FILE>);
/// // Where perhaps <MY_MESH_FILE> = C:\path\to\a\file.msh
/// \endcode



void HBTK::Gmsh::GmshParser::main_parser(std::ifstream & input_stream, std::ostream & error_stream)
{
	if (!input_stream) { throw -1; }
	if (!error_stream) { throw -1; }

	// Line counters
	int line_count = 0, section_start_line = 0;
	int expect_lines_to_next_section = 0;

	// String handles
	std::string this_line;

	bool still_parsing = true;
	struct binary_parse_info b_info = { false, -1, -1, -1, -1 };
	struct file_format_info f_info = { -1, false, (size_t)-1, false };
	file_section current_section = no_section;

	while (still_parsing) 
	{
		// LOOP FORMAT:
		//	-> Are we parsing binary right now? Yes. Do that, continue.
		//	We're parsing ASCII - we can get the line & increment counter.
		//	-> If starts with $, parse section header, set section, continue.
		//	-> Are we expecting a number to tell use the number of objects? is so, do that.
		//	-> We're parsing a regular section! Switch on what section we are
		//		on and run appropriate functions.

		if (b_info.parsing_binary) {
			switch (current_section) {
			case file_info:
				parse_file_binary_endian(input_stream, b_info, f_info);
				continue;
			case nodes:
				parse_node_line_binary(input_stream, b_info);
				continue;
			case elements:
				if (b_info.count_var > 0) {
					parse_elem_binary(input_stream, b_info); 
					expect_lines_to_next_section--;
					if (expect_lines_to_next_section < 1) { b_info.parsing_binary = false; }
				}
				else {
					parse_elem_binary_spec(input_stream, b_info);
				}
				continue;
			default:
				assert(false);
				break;
			}
		}

		do {
			still_parsing = (bool)std::getline(input_stream, this_line);
			if (!still_parsing) { break; }
			line_count++;
		} while (this_line == "");
		if (!still_parsing) { break; }

		// Working on a line starting with $ - IE section header.
		if (this_line[0] == '$') {
			// Get new section...
			try {
				current_section = parse_file_section(this_line, current_section);
			}
			catch (...) { current_section = invalid; }
			if (current_section == invalid) {
				error_stream << "ERROR:\tInvalid section header encountered at line " << line_count << ".\n";
				error_stream << "ERROR: Line is as follows:\n";
				error_stream << "ERROR: " << this_line << "\n";
				throw line_count;
			}
			section_start_line = line_count;
			continue;
		}
		// End of working on section header.

		// Get expected number of objects.
		if (expecting_object_count(current_section, line_count - section_start_line)) {
			expect_lines_to_next_section = std::stoi(this_line);
			if (current_section == nodes && f_info.binary ) {
				b_info.parsing_binary = true;
				b_info.count_var = expect_lines_to_next_section;
			}
			else if (current_section == elements && f_info.binary){
				b_info.parsing_binary = true;
				b_info.count_var = 0;
			}
			continue;
		}
		// end expected number of objects.

		// Parsing ASCII
		try {
			switch (current_section) {
			case file_info:
				parse_file_info(this_line, b_info, f_info);
				break;
			case nodes:
				parse_node_line(this_line);
				expect_lines_to_next_section -= 1;
				break;
			case elements:
				parse_elem_line(this_line);
				expect_lines_to_next_section -= 1;
				break;
			case physical_names:
				parse_phys_name_line(this_line);
				expect_lines_to_next_section -= 1;
				break;
			default:
				auto substrings = tokenise(this_line);
				if (substrings.size() != 0 && substrings[0] != "") {
					throw line_count;
					// We have nonsection data, outside a section.
				}
				// Otherwise we're on a blank line between sections.
			}
		}
		catch (...) {
			error_stream << "ERROR:\tInvalid line in ";
			print_section_name(current_section, error_stream);
			error_stream << " at line " << line_count << ".\n";
			error_stream << "ERROR:\tThe line is as follows:\n";
			error_stream << "ERROR:\t" << this_line << "\n";
			error_stream << "ERROR:\tLast header seen at line " << section_start_line << ".\n\n";
		}
		// End ASCII current section.
	}
}


HBTK::Gmsh::GmshParser::file_section HBTK::Gmsh::GmshParser::parse_file_section(std::string input_string, HBTK::Gmsh::GmshParser::file_section current_section)
{
	(void)current_section; // Make this look used - we might want to improve our error messages at some point.
	// Expects "$<section-name>" or "$End<section-name>"
	file_section section = invalid;
	auto strings = tokenise(input_string);
	if (strings.size() > 1) { throw -2; }

	if (strings[0].substr(0, 4) == "$End") {
		section = no_section;
	}
	else 
	{
		if (strings[0] == "$Nodes") { section = nodes; }
		else if (strings[0] == "$Elements") { section = elements; }
		else if (strings[0] == "$MeshFormat") { section = file_info; }
		else if (strings[0] == "$PhysicalNames") { section = physical_names; }
		else if (strings[0] == "$NodeData"
			|| strings[0] == "$ElementData"
			|| strings[0] == "$InterpolationScheme"
			|| strings[0] == "$ElementNodeData"
			|| strings[0] == "$Periodic")
		{
			section = unsupported;
		}
	}
	return section;
}


void HBTK::Gmsh::GmshParser::parse_node_line(std::string line)
{
	auto strings = tokenise(line);
	if (strings.size() != 4) {
		throw -1;
	};
	int tag;
	double x, y, z;

	tag = std::stoi(strings[0]);
	x = std::stod(strings[1]);
	y = std::stod(strings[2]);
	z = std::stod(strings[3]);

	for (auto func = node_funcs.begin(); func != node_funcs.end(); func++) {
		if (!(*func)(tag, x, y, z)) { break; };
	}
	return;
}


void HBTK::Gmsh::GmshParser::parse_node_line_binary(std::ifstream & input_stream, binary_parse_info & b_info)
{
#pragma pack(1)
	struct node_data {
		int tag;
		double x, y, z;
	} node_data;

	unpack_binary_to_struct(input_stream, node_data);
	
	for (auto func = node_funcs.begin(); func != node_funcs.end(); func++) {
		if (!(*func)(node_data.tag, node_data.x, node_data.y, node_data.z)) { break; };
	}
	b_info.count_var--;
	if (b_info.count_var < 1) { 
		b_info.parsing_binary = false; 
	}
	return;
}


void HBTK::Gmsh::GmshParser::parse_elem_line(std::string input_string)
{
	auto strings = tokenise(input_string);
	std::vector<int> values;
	int id, type, n_tags;

	for (auto string = strings.begin(); string != strings.end(); string++) {
		values.emplace_back(std::stoi(*string));
	}

	id = values[0];
	type = values[1];
	n_tags = values[2];
	std::vector<int> tags(values.begin() + 3, values.begin() + 3 + n_tags);
	std::vector<int> nodes(values.begin() + 3 + n_tags, values.end());

	for (auto func = elem_funcs.begin(); func != elem_funcs.end(); func++) {
		if (!(*func)(id, type, tags, nodes)) { break; };
	}
	return;
}


void HBTK::Gmsh::GmshParser::parse_elem_binary_spec(std::ifstream & input_stream, struct binary_parse_info & b_info)
{
	// Expects 3 ints: ele_type, num_elem_to_follow, num_tags
	assert(b_info.parsing_binary);
	assert(input_stream.good());

	#pragma pack(1)
	struct info_set {
		int ele_type, num_to_follow, num_phy_tags;
	} bs;

	unpack_binary_to_struct(input_stream, bs);

	b_info.ele_type = bs.ele_type;
	b_info.ele_tag_count = bs.num_phy_tags;
	b_info.ele_nodes = element_type_node_count(b_info.ele_type);
	b_info.count_var = bs.num_to_follow;
}


void HBTK::Gmsh::GmshParser::parse_elem_binary(std::ifstream & input_stream, struct binary_parse_info & b_info)
{
	// Expect tag(int) n_tags*physTag(int) n_nodes*node_tag(int)
	assert(b_info.parsing_binary);
	assert(b_info.ele_nodes > 0);
	assert(b_info.ele_tag_count > 0);
	assert(input_stream.good());

	int len = (1 + b_info.ele_tag_count + b_info.ele_nodes) * sizeof(int);
	char *buffer = new char[len];
	input_stream.read(buffer, (size_t)len);

	int id = reinterpret_cast<int *>(buffer)[0];
	std::vector<int> phy_tags(reinterpret_cast<int *>(buffer)+ 1, 
		reinterpret_cast<int *>(buffer)+ 1 + b_info.ele_tag_count);
	std::vector<int> nodes(reinterpret_cast<int *>(buffer) + 1 + b_info.ele_tag_count,
		reinterpret_cast<int *>(buffer) + 1 + b_info.ele_tag_count + b_info.ele_nodes);

	for (auto func = elem_funcs.begin(); func != elem_funcs.end(); func++) {
		if (!(*func)(id, b_info.ele_type, phy_tags, nodes)) { break; };
	}

	delete [] buffer;
	b_info.count_var--;
	return;
}


void HBTK::Gmsh::GmshParser::parse_phys_name_line(std::string inpt_string)
{
	// Expects <dimensions> <tag-id-thing> "<name>"
	auto strings = tokenise(inpt_string);

	int dimension, phys_num;
	std::string name;

	dimension = std::stoi(strings[0]);
	phys_num = std::stoi(strings[1]);
	name = strings[2];
	for (auto i = strings.begin() + 3; i != strings.end(); i++) {
		name += *i;
	}
	name = name.substr(1, name.length() - 2);	//Remove quote marks.

	for (auto func = phys_name_funcs.begin(); func != phys_name_funcs.end(); func++) {
		if (!(*func)(phys_num, dimension, name)) { break; };
	}
	return;
}


void HBTK::Gmsh::GmshParser::parse_file_info(std::string this_line, binary_parse_info & b_info, file_format_info & f_info)
{
	auto strings = tokenise(this_line);
	f_info.version = std::stod(strings[0]);
	f_info.binary = (bool)std::stoi(strings[1]);
	f_info.data_size = (size_t)std::stoi(strings[2]);
	if (f_info.binary) { b_info.parsing_binary = true; }
	return;
}

void HBTK::Gmsh::GmshParser::parse_file_binary_endian(std::ifstream & input_stream, binary_parse_info & b_info, file_format_info & f_info)
{
	int test_integer;
	unpack_binary_to_struct(input_stream, test_integer);
	f_info.matching_endian = test_integer == 1;
	b_info.parsing_binary = false;
}

int HBTK::Gmsh::GmshParser::element_type_node_count(int type)
{
	int nc;

	switch (type) {
		case 1: { nc = 2; break; }
		case 2: { nc = 3; break; }
		case 3: { nc = 4; break; }
		case 4: { nc = 4; break; }
		case 5: { nc = 8; break; }
		case 6: { nc = 6; break; }
		case 7: { nc = 5; break; }
		case 8: { nc = 3; break; }
		case 9: { nc = 6; break; }
		case 10: { nc = 9; break; }
		case 11: { nc = 10; break; }
		case 12: { nc = 27; break; }
		case 13: { nc = 18; break; }
		case 14: { nc = 14; break; }
		case 15: { nc = 1; break; }
		case 16: { nc = 8; break; }
		case 17: { nc = 20; break; }
		case 18: { nc = 15; break; }
		case 19: { nc = 13; break; }
		case 20: { nc = 9; break; }
		case 21: { nc = 10; break; }
		case 22: { nc = 12; break; }
		case 23: { nc = 15; break; }
		case 24: { nc = 15; break; }
		case 25: { nc = 21; break; }
		case 26: { nc = 4; break; }
		case 27: { nc = 5; break; }
		case 28: { nc = 6; break; }
		case 29: { nc = 20; break; }
		case 30: { nc = 35; break; }
		case 31: { nc = 56; break; }
		case 92: { nc = 64; break; }
		case 93: { nc = 125; break; }
		default: { nc = -1; break; }
	}
	
	return nc;
}


bool HBTK::Gmsh::GmshParser::expecting_object_count(file_section section, int line_difference)
{
	if (line_difference > 1) {
		return false;
	}
	bool are_we;
	switch (section) {
		case file_info: { are_we = false; break; }
		case nodes: { are_we = true; break; }
		case elements: { are_we = true; break; }
		case physical_names: { are_we = true; break; }
		default: { are_we = false; break; }
	}

	return are_we;
}


void HBTK::Gmsh::GmshParser::print_section_name(file_section sect, std::ostream & output)
{
	switch (sect) {
	case file_info: output << "MeshFormat"; 
		break;
	case nodes: output << "Nodes"; 
		break;
	case elements: output << "Elements";
		break;
	case physical_names: output << "PhysicalNames";
		break;
	case unsupported: output << "Unsupported file section (sorry)";
		break;
	case invalid: output << "[INVALID]";
		break;
	case no_section: output << "[No currently in section]";
		break;
	default: assert(false);
	}
}

