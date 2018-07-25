
#include <HBTK/GmshParser.h>

#include <catch2/catch.hpp>

#include <map>
#include <string>
#include <set>



TEST_CASE("GmshParser")
{
	SECTION("GMSH test file 1 - ASCII")
	{
		HBTK::Gmsh::GmshParser parser;

		int node_count = 0;
		int element_count = 0;
		int edge_element_count = 0;
		std::map<int, std::string> phys_names;
		std::map<int, std::set<int>> phys_grps;

		auto node_fn = [&node_count](int tag, double x, double y, double z)->bool
		{
			node_count++;
			return true;
		};

		auto elem_fn1 = [&element_count](int tag, int type, std::vector<int> grps, std::vector<int> nds)->bool
		{
			element_count++;
			return true;
		};


		auto elem_fn2 = [&edge_element_count](int tag, int type, std::vector<int> grps, std::vector<int> nds)->bool
		{
			if (type == 1) {
				edge_element_count++;
			}
			return true;
		};

		auto elem_fn3 = [&phys_grps](int tag, int type, std::vector<int> grps, std::vector<int> nds)->bool
		{
			for (auto grp = grps.begin(); grp != grps.end(); grp++)
			{
				phys_grps[*grp].emplace(tag);
			}
			return true;
		};

		auto phys_name_func = [&phys_names](int tag, int dim, std::string name)->bool
		{
			phys_names[tag] = name;
			return true;
		};

		parser.add_phys_name_function(phys_name_func);
		parser.add_node_function(node_fn);
		parser.add_elem_function(elem_fn1);
		parser.add_elem_function(elem_fn2);
		parser.add_elem_function(elem_fn3);
		parser.parse(TESTHBTK_RESOURCE_GMSH_TEST_FILE_ASCII);

		REQUIRE(node_count == 703);
		REQUIRE(element_count == 860);
		REQUIRE(edge_element_count == 224);
		REQUIRE(phys_names[1] == std::string("Volume"));
		REQUIRE(636 == (int)phys_grps[1].size());
		REQUIRE(112 == (int)phys_grps[2].size());

	}


	SECTION("GMSH test file 1 - binary")
	{
		HBTK::Gmsh::GmshParser parser;

		int node_count = 0;
		int element_count = 0;
		int edge_element_count = 0;
		int tri_count = 0;
		bool z_zero_check = true;
		std::map<int, std::string> phys_names;
		std::map<int, std::set<int>> phys_grps;

		auto node_fn = [&node_count, &z_zero_check](int tag, double x, double y, double z)->bool
		{
			node_count++;
			z_zero_check = 0.0 == z;
			return true;
		};

		auto elem_fn1 = [&element_count](int tag, int type, std::vector<int> grps, std::vector<int> nds)->bool
		{
			element_count++;
			return true;
		};


		auto elem_fn2 = [&edge_element_count, &tri_count](int tag, int type, std::vector<int> grps, std::vector<int> nds)->bool
		{
			if (type == 1) {
				edge_element_count++;
			}
			else if (type == 2) {
				tri_count++;
			}
			return true;
		};

		auto elem_fn3 = [&phys_grps](int tag, int type, std::vector<int> grps, std::vector<int> nds)->bool
		{
			for (auto grp = grps.begin(); grp != grps.end(); grp++)
			{
				phys_grps[*grp].emplace(tag);
			}
			return true;
		};

		auto phys_name_func = [&phys_names](int tag, int dim, std::string name)->bool
		{
			phys_names[tag] = name;
			return true;
		};

		parser.add_phys_name_function(phys_name_func);
		parser.add_node_function(node_fn);
		parser.add_elem_function(elem_fn1);
		parser.add_elem_function(elem_fn2);
		parser.add_elem_function(elem_fn3);
		parser.parse(TESTHBTK_RESOURCE_GMSH_TEST_FILE_BINARY);
			
		REQUIRE(node_count == 703);
		REQUIRE(element_count == 860);
		REQUIRE(224 == edge_element_count);
		REQUIRE(phys_names[1] == std::string("Volume"));
		REQUIRE(636 == (int)phys_grps[1].size());
		REQUIRE(112 == (int)phys_grps[2].size());
		REQUIRE(z_zero_check);
	}
}
