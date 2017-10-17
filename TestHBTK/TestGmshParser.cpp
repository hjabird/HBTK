#include "stdafx.h"
#include "CppUnitTest.h"

#include "../HBTK/GmshParser.h"

#include <map>
#include <string>
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHBTK
{
	TEST_CLASS(Test_GmshParser)
	{
	public:
		TEST_METHOD(GMSH_test_file_1)
		{
			Parsers::GmshParser parser;

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
				if (type == 8) {
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
			parser.parse("C:\\Users\\User\\source\\repos\\HBTK\\TestHBTK\\GMSH_test_file_1.msh");

			Assert::AreEqual(node_count, 119);
			Assert::AreEqual(element_count, 44);
			Assert::AreEqual(edge_element_count, 20);
			Assert::AreEqual(phys_names[1], std::string("Volume"));
			Assert::AreEqual((int)phys_grps[1].size(), 24);
			Assert::AreEqual((int)phys_grps[2].size(), 10);

		}
	};
}