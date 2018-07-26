#include <HBTK/CubicSplineND.h>
#include <HBTK/CubicSpline1D.h>

#include <array>
#include <vector>

#include <catch2/catch.hpp>

TEST_CASE("Cubic spline ND") {

	SECTION("Natural BC constructor & evaluation constant") {
		std::vector<double> points({ 0, 1, 2 });
		std::vector<double> values({ 2, 2, 2 });
		HBTK::CubicSpline1D spline1d(points, values);
		HBTK::CubicSplineND<2> spline({ spline1d, spline1d });

		REQUIRE(spline(0) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(1) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(2) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(1.5) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(-1) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(5) == std::array<double, 2>{2., 2.});
	}

	SECTION("Natural BC constructor & evaluation linear") {
		std::vector<double> points1({ 0, 1, 2 });
		std::vector<double> values1({ 0, 1, 2 });
		std::vector<double> points2({ 0, 1, 2 });
		std::vector<double> values2({ 2, 2, 2 });
		HBTK::CubicSpline1D spline1(points1, values1);
		HBTK::CubicSpline1D spline2(points2, values2);
		HBTK::CubicSplineND<2> spline({ spline2, spline1 });

		REQUIRE(spline(0) == std::array<double, 2>{2., 0.});
		REQUIRE(spline(1) == std::array<double, 2>{2., 1.});
		REQUIRE(spline(2) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(1.5) == std::array<double, 2>{2., 1.5});
		REQUIRE(spline(-1) == std::array<double, 2>{2., -1.});
		REQUIRE(spline(5) == std::array<double, 2>{2., 5.});
	}

	SECTION("Point based construction") {
		std::array<std::vector<double>, 2> points = { { {{ 2., 2., 2. }}, { {0., 1., 2.}} } };
		HBTK::CubicSplineND<2> spline(points);

		REQUIRE(spline(-1) == std::array<double, 2>{2., 0.});
		REQUIRE(spline(0) == std::array<double, 2>{2., 1.});
		REQUIRE(spline(1) == std::array<double, 2>{2., 2.});
		REQUIRE(spline(0.5) == std::array<double, 2>{2., 1.5});
		REQUIRE(spline(-2) == std::array<double, 2>{2., -1.});
		REQUIRE(spline(4) == std::array<double, 2>{2., 5.});
	}
}
