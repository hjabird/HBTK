/*////////////////////////////////////////////////////////////////////////////
GmshParser.cpp

A demonstration of the HBTK/GmshParser class.

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

#include "stdafx.h"

#include <iostream>
#include <map>
#include <chrono>
#include <cassert>

#include <HBTK/GmshParser.h>
#include <HBTK/GmshInfo.h>


void run_analysis(std::string path)
{
	std::cout << "Opening " << path << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	int count_node = 0;
	double max_x, max_y, max_z, min_x, min_y, min_z;
	double ave_x = 0, ave_y = 0, ave_z = 0;

	std::map<int, int> ele_counts;
	std::map<int, std::string> phys_grps;
	std::map<int, int> phys_grps_ects;

	auto nd_func = [&](int id, double x, double y, double z)->bool {
		count_node++;
		if (count_node > 1) {
			max_x = x > max_x ? x : max_x;
			min_x = x < min_x ? x : min_x;
			max_y = y > max_y ? y : max_y;
			min_y = y < min_y ? y : min_y;
			max_z = z > max_z ? z : max_z;
			min_z = z < min_z ? z : min_z;
		}
		else
		{
			max_x = min_x = x;
			max_y = min_y = y;
			max_z = min_z = z;
		}
		return true;
	};

	auto node_ave_func = [&](int id, double x, double y, double z)->bool {
		ave_x += x;
		ave_y += y;
		ave_z += z;
		return true;
	};

	auto ele_func = [&](int id, int type, std::vector<int> phy_grps, std::vector<int> nodes)->bool {
		ele_counts[type] += 1;
		for (auto idx = phy_grps.begin(); idx != phy_grps.end(); idx++) {
			phys_grps_ects[*idx] += 1;
		}

		return true;
	};

	auto phy_grps_func = [&phys_grps](int id, int dim, std::string name)->bool {
		phys_grps[id] = name;
		return true;
	};

	HBTK::Gmsh::GmshParser parser;
	parser.add_elem_function(ele_func);
	parser.add_node_function(nd_func);
	parser.add_node_function(node_ave_func);
	parser.add_phys_name_function(phy_grps_func);

	try {
		parser.parse(path);
	}
	catch (int exc) {
		if (exc > 0) {
			std::cout << "Parsing failed at line " << exc << ".\n";
			return;
		}
		else if (exc == -1) {
			std::cout << "Could not open file!\n";
			return;
		}
	}
	catch (...) {
		std::cout << "An unknown failure occured.\n";
		return;
	}


	ave_x = ave_x / count_node;	
	ave_y = ave_y / count_node;	
	ave_z = ave_z / count_node;

	auto finish = std::chrono::high_resolution_clock::now();

	std::cout << "Parsed file in " << std::chrono::duration<double>(finish - start).count() << " seconds.\n\n";

	std::cout << "\n\nMetadata:\n";

	std::cout << "\tPhysical groups:\n";
	for (auto idx = phys_grps.begin(); idx != phys_grps.end(); idx++) {
		std::cout << "\t\t";
		std::cout << idx->second << "\t:";
		std::cout << "Group no. " << idx->first << " (" << phys_grps_ects[idx->first] << " elements)\n";
	}

	std::cout << "\n\tNodes:\n";
	std::cout << "\t\t" << count_node << " nodes counted.\n";
	std::cout << "\t\tBounding box:\n";
	std::cout << "\t\t\t\tMin\tMax\n";
	std::cout << "\t\t\tx\t" << min_x << "\t" << max_x << "\n";
	std::cout << "\t\t\ty\t" << min_y << "\t" << max_y << "\n";
	std::cout << "\t\t\tz\t" << min_z << "\t" << max_z << "\n";
	std::cout << "\t\tAverage position:\n";
	std::cout << "\t\t\tx\t" << ave_x << "\n";
	std::cout << "\t\t\ty\t" << ave_y << "\n";
	std::cout << "\t\t\tz\t" << ave_z << "\n";
		
	std::cout << "\n\tElements:\n";
	for (auto idx = ele_counts.begin(); idx != ele_counts.end(); idx++) {
		std::cout << "\t\t" << HBTK::Gmsh::element_name(idx->first) << "\t: " << idx->second << "\n";
	}
	std::cout << "\n\nFinished.\n";

}



int main(int argc, char* argv[]) {
	std::cout << "GMSH metainfo program.\n";
	std::cout << "Demo for HBTK/GmshParser. (C) HJA Bird 2017.\n";
#ifdef _MSC_VER
	std::cout << "Compiled by MSVC " << _MSC_VER << ".\n";
#endif

	std::string path;

	if (argc > 2) {
		std::cout << "Expected a single path as the argument (no space) or -h for help.\n";
		std::cout << "Closing.\n\n";
	}
	else if (argc < 2) {
		std::cout << "No input path given. Using test file.\n";
		path = "C:\\Users\\User\\source\\repos\\HBTK\\TestHBTK\\GMSH_test_file_1_binary.msh";
		run_analysis(path);
	}
	else if (argv[1] == "-h" || argv[1] == "--help") {
		std::cout << "Help:\n";
		std::cout << "A program to demo a GMSH .msh parser capable of parsing GMSH 2.2 binary";
		std::cout << " and ASCII files (currently nodes, elems & physical names only.\n";
		std::cout << "To use the only argument is the path to a .msh file.\n\n";
	}
	else {
		path = argv[1];
		try {
			run_analysis(path);
		}
		catch(...) {
			std::cout << "\nParsing failed... Reason unknown.\n\n";
		}
	}


	return 0;
}



