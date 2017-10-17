#include "stdafx.h"
#include "CppUnitTest.h"

#include "../HBTK/GmshParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHBTK
{
	TEST_CLASS(Test_GmshParser)
	{
	public:
		TEST_METHOD(GMSH_elem_count)
		{
			Parsers::GmshParser parser;

			int node_count = 0;
			int element_count = 0;
			int edge_element_count = 0;

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

			parser.add_node_function(node_fn);
			parser.add_elem_function(elem_fn1);
			parser.add_elem_function(elem_fn2);

			parser.parse("GMSH_test_file_1.msh");

			Assert::AreEqual(node_count, 119);
			Assert::AreEqual(element_count, 44);
			Assert::AreEqual(edge_element_count, 20);
		}
	};
}