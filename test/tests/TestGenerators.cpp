
#include <HBTK/Generators.h>
#include <HBTK/Tolerances.h>

#include <catch2/catch.hpp>


TEST_CASE("Linspace - linear spacing of points")
{
	auto a = HBTK::linspace(0, 1); // 100 points generated by default
	REQUIRE(100 == (int)a.size());
	REQUIRE(0. == a[0]);
	REQUIRE(1. == a[99]);
	REQUIRE(1. / 99 == Approx(a[16] - a[15]));
}

TEST_CASE("Logspace")
{
	auto a = HBTK::logspace(0, 2); // 100 points generated by default
	REQUIRE(100 == (int)a.size());
	REQUIRE(1. == a[0]);
	REQUIRE(100. == a[99]);
}

TEST_CASE("Geomspace")
{
	auto a = HBTK::geomspace(1, 1024, 105, 2);  
	REQUIRE(105 == (int)a.size());
	REQUIRE(1. == a[0]);
	REQUIRE(1024. == a[104]);
}
