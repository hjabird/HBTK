#include "stdafx.h"
#include "CppUnitTest.h"

#include <array>

#include "../HBTK/GaussLegendre.h"
#include "../HBTK/Integrators.h"
#include "../HBTK/Tolerances.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHBTK
{
	TEST_CLASS(Test_Integrators)
	{
	public:

		TEST_METHOD(Static_integrator)
		{
			const int num_points = 6;
			std::array<double, num_points> points, weights;
			Quad::gauss_legendre<num_points, double>(points, weights);

			auto my_fun = [](double x)->double
			{
				return x*x*x + x*x + 3;
			};

			double result;
			result = Quad::static_integrate(my_fun, points, weights, num_points);
			Assert::AreEqual(20.0 / 3.0, result, num_points*Quad::tolerance<double>(), L"Expected solution...", LINE_INFO());
		}

		TEST_METHOD(Static_integrator_templated_n_points)
		{
			const int num_points = 6;
			std::array<double, num_points> points, weights;
			Quad::gauss_legendre<num_points, double>(points, weights);

			auto my_fun = [](double x)->double
			{
				return x*x*x + x*x + 3;
			};

			double result;
			result = Quad::static_integrate<num_points>(my_fun, points, weights);
			Assert::AreEqual(20.0 / 3.0, result, num_points*Quad::tolerance<double>(), L"Expected solution...", LINE_INFO());
		}

		TEST_METHOD(Adaptive_trapezoidal_rule)
		{
			auto my_fun = [](double x)->double
			{
				return x*x*x*x*x*x*x*x*x;
			};
			auto result = Quad::adaptive_trapezoidal_integrate(my_fun, 1e-10, 0.0, 1.0);
			Assert::AreEqual(1.0 / 10.0, result, 1e-10);

			auto my_f2 = [](double x)->double
			{return sin(x); };
			auto result2 = Quad::adaptive_trapezoidal_integrate(my_f2, 1e-8, 0.0, 2.0);
			Assert::AreEqual(1.416146837, result2, 1e-8);
		}
		
		TEST_METHOD(Adaptive_simpsons_rule)
		{
			auto my_f = [](double x)->double
			{return x*x*x*x*x*x*x*x*x;};
			auto result = Quad::adaptive_simpsons_integrate(my_f, 1e-10, 0.0, 1.0);
			Assert::AreEqual(1.0 / 10.0, result, 1e-10);

			auto my_f2 = [](double x)->double
			{return sin(x); };
			auto result2 = Quad::adaptive_simpsons_integrate(my_f2, 1e-8, 0.0, 2.0);
			Assert::AreEqual(1.416146837, result2, 1e-8);
		}
		
	};
}