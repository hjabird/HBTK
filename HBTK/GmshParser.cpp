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


void Parsers::GmshParser::add_phys_name_function(std::function<bool(int, int, std::string)> func)
{
	phys_name_funcs.emplace_back(func);
}


void Parsers::GmshParser::add_node_function(std::function<bool(int, double, double, double)> func)
{
	node_funcs.emplace_back(func);
}


void Parsers::GmshParser::add_elem_function(std::function<bool(int, int, std::vector<int>, std::vector<int>)> func)
{
	elem_funcs.emplace_back(func);
}


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
	assert(input_stream.is_open());
	assert(error_stream.is_open());

	// Line counters
	int line_count = 0, section_start_line = 0;
	int expect_lines_to_next_section = 0;

	// String handles
	std::string this_line;

	bool still_parsing = true;
	bool parsing_binary = false;
	file_section current_section = no_section;

	// Regexs:
	std::regex section_end("");
	std::regex node_ln(":digit:");

	while (still_parsing) 
	{
		if (parsing_binary) {
			throw; // Not implemented yet!
			continue;
		}

		else if (std::getline(input_stream, this_line)) {
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
			if (substrings.size() != 0) {
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
		if (!(*func)(dimension, phys_num, name)) { break; };
	}
	return;
}


std::vector<std::string> Parsers::GmshParser::tokenise(std::string input_string)
{

	std::regex no_whitespace("\\s+");
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

