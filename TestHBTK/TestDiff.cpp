#include "stdafx.h"
#include "CppUnitTest.h"

#include "../HBTK/NumericalDifferentiation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHBTK
{
	TEST_CLASS(Test_GaussLegendre)
	{
	public:

		TEST_METHOD(First_order_diff)
		{
			auto linear_func = [](double x)->double { return 3*x; };
			auto quad_func = [](double x)->double { return 3 * x + 2. * x*x + 1.; };

			Assert::AreEqual(3., Diff::central_difference_O1A2(linear_func, 0.), 1e-7, L"Linear O1A2 at 0");
			Assert::AreEqual(3., Diff::central_difference_O1A4(linear_func, 0.), 1e-7, L"Linear O1A4 at 0");
			Assert::AreEqual(3., Diff::central_difference_O1A6(linear_func, 0.), 1e-7, L"Linear O1A6 at 0");
			Assert::AreEqual(3., Diff::central_difference_O1A2(linear_func, 10.), 1e-6, L"Linear O1A2 at 10");
			Assert::AreEqual(3., Diff::central_difference_O1A4(linear_func, 10.), 1e-6, L"Linear O1A4 at 10");
			Assert::AreEqual(3., Diff::central_difference_O1A6(linear_func, 10.), 1e-6, L"Linear O1A6 at 10");


			Assert::AreEqual(3., Diff::central_difference_O1A2(quad_func, 0.), 1e-6, L"Quad O1A2 at 0");
			Assert::AreEqual(3., Diff::central_difference_O1A4(quad_func, 0.), 1e-6, L"Quad O1A4 at 0");
			Assert::AreEqual(3., Diff::central_difference_O1A6(quad_func, 0.), 1e-6, L"Quad O1A6 at 0");
			Assert::AreEqual(43., Diff::central_difference_O1A2(quad_func, 10.), 1e-5, L"Quad O1A2 at 10");
			Assert::AreEqual(43., Diff::central_difference_O1A4(quad_func, 10.), 1e-5, L"Quad O1A4 at 10");
			Assert::AreEqual(43., Diff::central_difference_O1A6(quad_func, 10.), 1e-5, L"Quad O1A6 at 10");
		}
		
		TEST_METHOD(Second_order_diff)
		{
			auto linear_func = [](double x)->double { return 3 * x; };
			auto quad_func = [](double x)->double { return 3. * x + 2. * x*x + 1.; };
			auto cubic_func = [](double x)->double { return 3. * x + 2. * x*x + 1. + x*x*x; };

			Assert::AreEqual(0., Diff::central_difference_O2A2(linear_func, 0.), 1e-7, L"Linear O2A2 at 0");
			Assert::AreEqual(0., Diff::central_difference_O2A4(linear_func, 0.), 1e-7, L"Linear O2A4 at 0");
			Assert::AreEqual(0., Diff::central_difference_O2A6(linear_func, 0.), 1e-7, L"Linear O2A6 at 0");
			Assert::AreEqual(0., Diff::central_difference_O2A2(linear_func, 10.), 1e-6, L"Linear O2A2 at 10");
			Assert::AreEqual(0., Diff::central_difference_O2A4(linear_func, 10.), 1e-6, L"Linear O2A4 at 10");
			Assert::AreEqual(0., Diff::central_difference_O2A6(linear_func, 10.), 1e-6, L"Linear O2A6 at 10");

			
			Assert::AreEqual(4., Diff::central_difference_O2A2(cubic_func, 0.), 1e-6, L"cubic O2A2 at 0");
			Assert::AreEqual(4., Diff::central_difference_O2A4(cubic_func, 0.), 1e-6, L"cubic O2A4 at 0");
			Assert::AreEqual(4., Diff::central_difference_O2A6(cubic_func, 0.), 1e-6, L"cubic O2A6 at 0");
			Assert::AreEqual(64., Diff::central_difference_O2A2(cubic_func, 10.), 1e-5, L"cubic O2A2 at 10");
			Assert::AreEqual(64., Diff::central_difference_O2A4(cubic_func, 10.), 1e-5, L"cubic O2A4 at 10");
			Assert::AreEqual(64., Diff::central_difference_O2A6(cubic_func, 10.), 1e-5, L"cubic O2A6 at 10");
			

			Assert::AreEqual(4., Diff::central_difference_O2A2(quad_func, 0.), 1e-6, L"Quad O2A2 at 0");
			Assert::AreEqual(4., Diff::central_difference_O2A4(quad_func, 0.), 1e-6, L"Quad O2A4 at 0");
			Assert::AreEqual(4., Diff::central_difference_O2A6(quad_func, 0.), 1e-6, L"Quad O2A6 at 0");
			Assert::AreEqual(4., Diff::central_difference_O2A2(quad_func, 10.), 1e-5, L"Quad O2A2 at 10");
			Assert::AreEqual(4., Diff::central_difference_O2A4(quad_func, 10.), 1e-5, L"Quad O2A4 at 10");
			Assert::AreEqual(4., Diff::central_difference_O2A6(quad_func, 10.), 1e-5, L"Quad O2A6 at 10");
		}
		
	};
}