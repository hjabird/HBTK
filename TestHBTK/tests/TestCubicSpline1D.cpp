#include <HBTK/CubicSpline1D.h>

#include <vector>

#include <catch2/catch.hpp>

TEST_CASE("Cubic spline 1D") {

	SECTION("Natural BC constructor & evaluation constant") {
		std::vector<double> points({ 0, 1, 2 });
		std::vector<double> values({ 2, 2, 2 });
		HBTK::CubicSpline1D spline(points, values);

		REQUIRE(spline(0) == 2);
		REQUIRE(spline(1) == 2);
		REQUIRE(spline(2) == 2);
		REQUIRE(spline(1.5) == 2);
		REQUIRE(spline(-1) == 2);
		REQUIRE(spline(5) == 2);
	}

	SECTION("Natural BC constructor & evaluation linear") {
		std::vector<double> points({ 0, 1, 2 });
		std::vector<double> values({ 0, 1, 2 });
		HBTK::CubicSpline1D spline(points, values);

		REQUIRE(spline(0) == 0);
		REQUIRE(spline(1) == 1);
		REQUIRE(spline(2) == 2);
		REQUIRE(spline(1.5) == 1.5);
		REQUIRE(spline(-1) == -1);
		REQUIRE(spline(5) == 5);
	}

	SECTION("Natural BC bounds functions") {
		std::vector<double> points({ 0, 1, 2 });
		std::vector<double> values({ 0, 1, 2 });
		HBTK::CubicSpline1D spline(points, values);

		REQUIRE(spline.lower_input_bound() == 0);
		REQUIRE(spline.upper_input_bound() == 2);
	}


	SECTION("Natural BC constructor & derivative linear") {
		std::vector<double> points({ 0, 1, 2 });
		std::vector<double> values({ 0, 1, 2 });
		HBTK::CubicSpline1D spline(points, values);

		REQUIRE(spline.derivative(0) == 1);
		REQUIRE(spline.derivative(1) == 1);
		REQUIRE(spline.derivative(2) == 1);
		REQUIRE(spline.derivative(1.5) == 1);
		REQUIRE(spline.derivative(-1) == 1);
		REQUIRE(spline.derivative(5) == 1);
	}

	SECTION("Defined derivative BC constructor & evaluation") {
		std::vector<double> points({ 0, 1, 2 });
		std::vector<double> values({ 0, 1, 2 });
		HBTK::CubicSpline1D spline(points, values, 0, 2);

		REQUIRE(spline(0) == 0);
		REQUIRE(spline(1) == 1);
		REQUIRE(spline(2) == 2);
		REQUIRE_FALSE(spline(1.5) == 1.5);
		REQUIRE_FALSE(spline(-1) == -1);
		REQUIRE_FALSE(spline(5) == 5);
		REQUIRE(spline.derivative(0) == 0);
		REQUIRE(spline.derivative(2) == 2);
	}

	SECTION("Defined derivative BC constructor & evaluation") {
		std::vector<double> points({ 0, 1, 2, 3, 4, 5 });
		std::vector<double> values({ 0, 1, 2, 3, 4, 5 });
		HBTK::CubicSpline1D spline(points, values, 0);

		REQUIRE(spline(0) == 0);
		REQUIRE(spline(1) == 1);
		REQUIRE(spline(2) == 2);
		REQUIRE(spline(5) == 5);
		REQUIRE_FALSE(spline(1.5) == 1.5);
		REQUIRE_FALSE(spline(-1) == -1);
		REQUIRE(spline.derivative(0) == 0);
		REQUIRE(spline.derivative(5) == 1);
	}
}
