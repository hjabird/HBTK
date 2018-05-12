
#include <array>

#include <catch.hpp>

#include <HBTK/GaussLegendre.h>
#include <HBTK/Integrators.h>
#include <HBTK/Tolerances.h>


TEST_CASE("Static integrator") {
	SECTION("static integrate gauss legendre with cubic polynomial")
	{
		const int num_points = 6;
		std::array<double, num_points> points, weights;
		HBTK::gauss_legendre<num_points, double>(points, weights);

		auto my_fun = [](double x)->double
		{
			return x * x*x + x * x + 3;
		};

		double result;
		result = HBTK::static_integrate(my_fun, points, weights, num_points);
		REQUIRE(20.0 / 3.0 == Approx(result));
	}
}

TEST_CASE("Adaptive trapezoidal integrator"){
	SECTION("Integrate a x^2 in [0, 1]")
	{
		auto my_fun = [](double x)->double
		{
			return x * x;
		};
		auto result = HBTK::adaptive_trapezoidal_integrate(my_fun, 1e-10, 0.0, 1.0);
		REQUIRE(1.0 / 3.0 == Approx(result)); // May need to adjust this...
	}

	SECTION("Integrate sin(x) in [0, 2]") {
		auto my_f2 = [](double x)->double
		{	
			return sin(x);
		};
		auto result2 = HBTK::adaptive_trapezoidal_integrate(my_f2, 1e-8, 0.0, 2.0);
		REQUIRE(1.416146837 == Approx(result2)); // May need to adjust this...
	}
}

TEST_CASE("Adaptive simpsons integrator")
{
	SECTION("Integrate x^3 in [0, 1]")
	{
		auto my_f = [](double x)->double
		{
			return x * x * x; 
		};
		auto result = HBTK::adaptive_simpsons_integrate(my_f, 1e-10, 0.0, 1.0);
		REQUIRE(1.0 / 4.0 == Approx(result));
	}
	SECTION("Integrate sin(x) in [0, 2]")
	{
		auto my_f2 = [](double x)->double
		{
			return sin(x); 
		};
		auto result2 = HBTK::adaptive_simpsons_integrate(my_f2, 1e-12, 0.0, 2.0);
		REQUIRE(1.416146837 == Approx(result2));
	}
		
};

TEST_CASE("Adaptive Gauss-Lobatto")
{
	SECTION("Integrate x^3 in [0, 1]")
	{
		auto my_f = [](double x)->double
		{
			return x * x * x;
		};
		auto result = HBTK::adaptive_gauss_lobatto_integrate(my_f, 1e-10, 0.0, 1.0);
		REQUIRE(1.0 / 4.0 == Approx(result));
	}
	SECTION("Integrate sin(x) in [0, 2]")
	{
		auto my_f2 = [](double x)->double
		{
			return sin(x);
		};
		auto result2 = HBTK::adaptive_gauss_lobatto_integrate(my_f2, 1e-8, 0.0, 2.0);
		REQUIRE(1.416146837 == Approx(result2));
	}

};
