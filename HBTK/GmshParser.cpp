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
#include <regex>
#include <algorithm>

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
/// Parsers::GmshParser my_parser;
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
void Parsers::GmshParser::add_phys_name_function(std::function<bool(int, int, std::string)> func)
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
/// Parsers::GmshParser my_parser;
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
void Parsers::GmshParser::add_node_function(std::function<bool(int, double, double, double)> func)
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
/// Parsers::GmshParser my_parser;
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
void Parsers::GmshParser::add_elem_function(std::function<bool(int, int, std::vector<int>, std::vector<int>)> func)
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
/// Parsers::GmshParser my_parser;
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
void Parsers::GmshParser::parse(fs::path file_path)
{
	if (file_path.empty()) { throw; }
	std::ifstream inpt_stream(file_path);
	std::ofstream out_stream(stderr);
	parse(inpt_stream, out_stream);
}

void Parsers::GmshParser::parse(std::ifstream & input_stream)
{
	std::ofstream err_stream(stderr);
	parse(input_stream, err_stream);
}

void Parsers::GmshParser::parse(std::ifstream & input_stream, std::ofstream & error_stream)
{
	if (!input_stream) { throw; }
	if (!error_stream) { throw; }
	// Line counters
	int line_count = 0, section_start_line = 0;
	int expect_lines_to_next_section = 0;

	// String handles
	std::string this_line;

	bool still_parsing = true;
	bool parsing_binary = false;
	file_section current_section = no_section;

	while (still_parsing) 
	{
		if (parsing_binary) {
			throw; // Not implemented yet!
			continue;
		}

		else if (!std::getline(input_stream, this_line)) {
			still_parsing = false;
			break;
		}
		line_count++;

		// Working on a line starting with $ - IE section header.
		if (this_line[0] == '$') {
			if (expect_lines_to_next_section != 0) {
				error_stream << "WARNING:\tUnexpected new section on line " << line_count << ".\n";
				error_stream << "WARNING:\tWas looking at section ";
				print_section_name(current_section, error_stream);
				error_stream << " which started on line " << section_start_line << "\n.";
				error_stream << "WARNING:\tWas expecting " << expect_lines_to_next_section << " more entries first.\n\n";
			}
			// Get new section...
			try {
				current_section = parse_file_section(this_line, current_section);
			}
			catch (...) {
				error_stream << "ERROR:\tInvalid section header encountered at line " << line_count << ".\n\n";
				throw;
			}
			section_start_line = line_count;
			continue;
		}

		// We're inside a section.
		switch (current_section) {
		case file_info:
			// Not impemented yet...
			break;
		case nodes:
			if (line_count - section_start_line > 1) {
				parse_node_line(this_line);
				expect_lines_to_next_section -= 1;
			}
			else { expect_lines_to_next_section = std::stoi(this_line); }
			break;
		case elements:
			if (line_count - section_start_line > 1) {
				parse_elem_line(this_line);
				expect_lines_to_next_section -= 1;
			}
			else { expect_lines_to_next_section = std::stoi(this_line); }
			break;
		case physical_names:
			if (line_count - section_start_line > 1) {
				parse_phys_name_line(this_line);
				expect_lines_to_next_section -= 1;
			}
			else { expect_lines_to_next_section = std::stoi(this_line); }
			break;
		default:
			auto substrings = tokenise(this_line);
			if (substrings.size() != 0 && substrings[0] != "") {
				error_stream << "ERROR:\tInvalid line in no section at line " << line_count << ".\n";
				error_stream << "ERROR:\tLast header seen at line " << section_start_line << ".\n\n";
				throw;
				// We have nonsection data, outside a section.
			}
			// Otherwise the line is blank between sections...
		}
	}
}


Parsers::GmshParser::file_section Parsers::GmshParser::parse_file_section(std::string input_string, Parsers::GmshParser::file_section current_section)
{
	// Expects "$<section-name>" or "$End<section-name>"
	file_section section = invalid;
	auto strings = tokenise(input_string);
	if (strings.size() > 1) { throw; }

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


void Parsers::GmshParser::parse_node_line(std::string line)
{
	auto strings = tokenise(line);
	assert(strings.size() == 4);
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


void Parsers::GmshParser::parse_elem_line(std::string input_string)
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


void Parsers::GmshParser::parse_phys_name_line(std::string inpt_string)
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


std::vector<std::string> Parsers::GmshParser::tokenise(std::string input_string)
{
	std::regex no_whitespace("[\\s,]+");
	std::vector<std::string> tokens(
		std::sregex_token_iterator(input_string.begin(), input_string.end(), no_whitespace, -1),
		std::sregex_token_iterator());
	return tokens;
}

void Parsers::GmshParser::print_section_name(file_section sect, std::ofstream & output)
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
	default: assert(false);
	}
}

