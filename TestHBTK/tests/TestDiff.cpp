
#include <HBTK/NumericalDifferentiation.h>

#include <catch.hpp>

TEST_CASE("First derivative numerical")
{
	SECTION("Linear function") {
		auto linear_func = [](double x)->double { 
			return 3 * x; 
		};

		REQUIRE(3. == Approx(HBTK::central_difference_O1A2(linear_func, 0.))); //1e-7
		REQUIRE(3. == Approx(HBTK::central_difference_O1A4(linear_func, 0.)));
		REQUIRE(3. == Approx(HBTK::central_difference_O1A6(linear_func, 0.)));
		REQUIRE(3. == Approx(HBTK::central_difference_O1A2(linear_func, 10.))); //1e-6
		REQUIRE(3. == Approx(HBTK::central_difference_O1A4(linear_func, 10.)));
		REQUIRE(3. == Approx(HBTK::central_difference_O1A6(linear_func, 10.)));
	}

	SECTION("Quadratic function") {
		auto quad_func = [](double x)->double {
			return 3 * x + 2. * x * x + 1.;
		};
		REQUIRE(3. == Approx(HBTK::central_difference_O1A2(quad_func, 0.)));//-6
		REQUIRE(3. == Approx(HBTK::central_difference_O1A4(quad_func, 0.)));
		REQUIRE(3. == Approx(HBTK::central_difference_O1A6(quad_func, 0.)));
		REQUIRE(43. == Approx(HBTK::central_difference_O1A2(quad_func, 10.)));//-5
		REQUIRE(43. == Approx(HBTK::central_difference_O1A4(quad_func, 10.)));
		REQUIRE(43. == Approx(HBTK::central_difference_O1A6(quad_func, 10.)));
	}
}
		
TEST_CASE("Second derivative numerical.")
{
	SECTION("Linear function") {
		auto linear_func = [](double x)->double { 
			return 3 * x; 
		};
		REQUIRE(0. == Approx(HBTK::central_difference_O2A2(linear_func, 0.)).margin(1e-7)); //-7
		REQUIRE(0. == Approx(HBTK::central_difference_O2A4(linear_func, 0.)).margin(1e-7));
		REQUIRE(0. == Approx(HBTK::central_difference_O2A6(linear_func, 0.)).margin(1e-7));
		REQUIRE(0. == Approx(HBTK::central_difference_O2A2(linear_func, 10.)).margin(1e-6));//-6
		REQUIRE(0. == Approx(HBTK::central_difference_O2A4(linear_func, 10.)).margin(1e-6));
		REQUIRE(0. == Approx(HBTK::central_difference_O2A6(linear_func, 10.)).margin(1e-6));
	}
	
	SECTION("Quadratic function") {
		auto quad_func = [](double x)->double {
			return 3. * x + 2. * x * x + 1.; 
		};
		REQUIRE(4. == Approx(HBTK::central_difference_O2A2(quad_func, 0.)));//-6
		REQUIRE(4. == Approx(HBTK::central_difference_O2A4(quad_func, 0.)));
		REQUIRE(4. == Approx(HBTK::central_difference_O2A6(quad_func, 0.)));
		REQUIRE(4. == Approx(HBTK::central_difference_O2A2(quad_func, 10.)));//-5
		REQUIRE(4. == Approx(HBTK::central_difference_O2A4(quad_func, 10.)));
		REQUIRE(4. == Approx(HBTK::central_difference_O2A6(quad_func, 10.)));
	}

	SECTION("Cubic function") {
		auto cubic_func = [](double x)->double { 
			return 3. * x + 2. * x * x + 1. + x * x * x; 
		};
		REQUIRE(4. == Approx(HBTK::central_difference_O2A2(cubic_func, 0.))); //-6
		REQUIRE(4. == Approx(HBTK::central_difference_O2A4(cubic_func, 0.)));
		REQUIRE(4. == Approx(HBTK::central_difference_O2A6(cubic_func, 0.)));
		REQUIRE(64. == Approx(HBTK::central_difference_O2A2(cubic_func, 10.))); //-5
		REQUIRE(64. == Approx(HBTK::central_difference_O2A4(cubic_func, 10.)));
		REQUIRE(64. == Approx(HBTK::central_difference_O2A6(cubic_func, 10.)));
	}		
};
