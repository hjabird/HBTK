
#include <catch2/catch.hpp>

#include <HBTK/Remaps.h>
#include <HBTK/Tolerances.h>

TEST_CASE("Integral Remaps")
{
	SECTION("Linear remaps")
	{
		// Debuggin can be problematic due to compiling the solution.
		double px, wx;
		px = 0.0;
		wx = 1.0;
		HBTK::linear_remap(px, wx, -1.0, 1.0, 0.0, 2.0);
		REQUIRE(1.0 == Approx(px));
		REQUIRE(1.0 == Approx(wx));
		HBTK::linear_remap(px, wx, 0.0, 2.0, -2.0, 2.0);
		REQUIRE(0.0 == Approx(px));
		REQUIRE(2.0 == Approx(wx));

		px = -1.0;
		wx = 1.0;
		HBTK::linear_remap(px, wx, -1.0, 1.0, 0.0, 2.0);
		REQUIRE(0.0 == Approx(px));
		REQUIRE(1.0 == Approx(wx));
		HBTK::linear_remap(px, wx, 0.0, 2.0, -2.0, 2.0);
		REQUIRE(-2.0 == Approx(px));
		REQUIRE(2.0 == Approx(wx));
	}

	SECTION("Telles Quadratic remap")
	{
		double px, wx;
		px = -1;
		wx = 1;
		HBTK::telles_quadratic_remap(px, wx, 1.);
		REQUIRE(-1.0 == Approx(px));
		REQUIRE(2.0 == Approx(wx));
		px = 1;
		wx = 1;
		HBTK::telles_quadratic_remap(px, wx, 1.);
		REQUIRE(1.0 == Approx(px));
		REQUIRE(0.0 == Approx(wx));
		px = 0;
		wx = 1;
		HBTK::telles_quadratic_remap(px, wx, 1.);
		REQUIRE(0.5 == Approx(px));
		REQUIRE(1.0 == Approx(wx));
		px = 0;
		wx = 1;
		HBTK::telles_quadratic_remap(px, wx, -1.);
		REQUIRE(-0.5 == Approx(px));
		REQUIRE(1.0 == Approx(wx));
	}

	SECTION("Telles Cubic remap")
	{
		double px, wx;
		px = -1;
		wx = 1;
		HBTK::telles_cubic_remap(px, wx, 1.0);
		REQUIRE(-1.0 == Approx(px));
		REQUIRE(3.0 == Approx(wx));
		px = 1;
		wx = 1;
		HBTK::telles_cubic_remap(px, wx, 1.0);
		REQUIRE(1.0 == Approx(px));
		REQUIRE(0.0 == Approx(wx));
		px = 0;
		wx = 1;
		HBTK::telles_cubic_remap(px, wx, 1.0);
		REQUIRE(0.75 == Approx(px));
		REQUIRE(0.75 == Approx(wx));
		px = 0;
		wx = 1;
		HBTK::telles_cubic_remap(px, wx, -1.0);
		REQUIRE(-0.75 == Approx(px));
		REQUIRE(0.75 == Approx(wx));
	}

	SECTION("Sato remap")
	{
		double px, wx;
		px = -1;
		wx = 1;
		HBTK::sato_remap<3>(px, wx, 1.0);
		REQUIRE(-1.0 == Approx(px));
		REQUIRE(3.0 == Approx(wx));
		px = 1;
		wx = 1;
		HBTK::sato_remap<3>(px, wx, 1.0);
		REQUIRE(1.0 == Approx(px));
		REQUIRE(0.0 == Approx(wx));
		px = 0;
		wx = 1;
		HBTK::sato_remap<4>(px, wx, 1.0);
		REQUIRE(0.875 == Approx(px));
		REQUIRE(0.5 == Approx(wx));
		px = 0;
		wx = 1;
		HBTK::sato_remap<4>(px, wx, -1.0);
		REQUIRE(-0.875 == Approx(px));
		REQUIRE(0.5 == Approx(wx));
	}

	SECTION("Exponential remap")
	{
		double px, wx;
		px = -1;
		wx = 1;
		HBTK::exponential_remap(px, wx, -3.);
		REQUIRE(-3. == Approx(px));
		px = -1;
		HBTK::exponential_remap(px, wx, 5.);
		REQUIRE(5. == Approx(px));
		px = 1;
		HBTK::exponential_remap(px, wx, 2.);
		REQUIRE((double)INFINITY == Approx(px));
		px = -1;
		wx = 1;
		HBTK::exponential_remap(px, wx, 0.);
		REQUIRE(0. == Approx(px));
		REQUIRE(0.5 == Approx(wx));
		px = 1;
		wx = 1;
		HBTK::exponential_remap(px, wx, 0.);
		REQUIRE((double)INFINITY == Approx(px));
		REQUIRE((double)INFINITY == Approx(wx));
	}

	SECTION("Doblare remap")
	{
		double px, wx;
		px = -1;
		wx = 1;
		HBTK::doblare_remap(px, wx, 0.5);
		REQUIRE(-1.0 == Approx(px));
		REQUIRE(5. == Approx(wx));
		px = 1;
		wx = 1;
		HBTK::doblare_remap(px, wx, 0.5);
		REQUIRE(1.0 == Approx(px));
		REQUIRE(1. == Approx(wx));
	}
	};
