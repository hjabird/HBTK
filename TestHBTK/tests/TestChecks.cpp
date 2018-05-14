#include <HBTK/Checks.h>
#include <HBTK/Constants.h>

#include <array>
#include <complex>
#include <vector>

#include <catch.hpp>

TEST_CASE("Check finite") {

	SECTION("double") {
		REQUIRE(HBTK::check_finite(0.0));
		REQUIRE(HBTK::check_finite(-100.));
		REQUIRE_FALSE(HBTK::check_finite(HUGE_VAL));
		REQUIRE_FALSE(HBTK::check_finite((double)NAN));
		REQUIRE_FALSE(HBTK::check_finite((double)INFINITY));
	}

	SECTION("float") {
		REQUIRE(HBTK::check_finite((float)0.0));
		REQUIRE(HBTK::check_finite((float)-100.));
		REQUIRE_FALSE(HBTK::check_finite(HUGE_VALF));
		REQUIRE_FALSE(HBTK::check_finite(NAN));
		REQUIRE_FALSE(HBTK::check_finite(INFINITY));
	}

	SECTION("complex") {
		REQUIRE(HBTK::check_finite((std::complex<double>)0.0));
		REQUIRE(HBTK::check_finite((std::complex<double>) -100.));
		REQUIRE_FALSE(HBTK::check_finite((std::complex<double>)HUGE_VAL));
		REQUIRE_FALSE(HBTK::check_finite((std::complex<double>)NAN));
		REQUIRE_FALSE(HBTK::check_finite((std::complex<double>)INFINITY));
		REQUIRE(HBTK::check_finite(HBTK::Constants::i()));
		REQUIRE_FALSE(HBTK::check_finite(HBTK::Constants::i() * HUGE_VAL));
		REQUIRE_FALSE(HBTK::check_finite(HBTK::Constants::i() * (double)NAN));
		REQUIRE_FALSE(HBTK::check_finite(HBTK::Constants::i() * (double)INFINITY));
	}

	SECTION("vector") {
		std::vector<double> vec({ 0, 1, 2, 3, 4 });
		REQUIRE(HBTK::check_finite(vec));
		vec[2] = HUGE_VAL;
		REQUIRE_FALSE(HBTK::check_finite(vec));
		vec[2] = (double)NAN;
		REQUIRE_FALSE(HBTK::check_finite(vec));
		vec[2] = (double)INFINITY;
		REQUIRE_FALSE(HBTK::check_finite(vec));
	}

	SECTION("array") {
		std::array<double, 5> vec;
		vec = { 0, 1, 2, 3, 4 };
		REQUIRE(HBTK::check_finite(vec));
		vec[2] = HUGE_VAL;
		REQUIRE_FALSE(HBTK::check_finite(vec));
		vec[2] = (double)NAN;
		REQUIRE_FALSE(HBTK::check_finite(vec));
		vec[2] = (double)INFINITY;
		REQUIRE_FALSE(HBTK::check_finite(vec));
	}
}

TEST_CASE("Check in range") {

	SECTION("double") {
		REQUIRE(HBTK::check_in_range(0.0, -1., 1.));
		REQUIRE(HBTK::check_in_range(0.0, -1., 0.));
		REQUIRE(HBTK::check_in_range(0.0, 0., 1.));
		REQUIRE_FALSE(HBTK::check_in_range(-0.1, 0., 1.));
		REQUIRE_FALSE(HBTK::check_in_range((double)NAN, 0., 1.));
		REQUIRE_FALSE(HBTK::check_in_range((double)INFINITY, 0., 1.));
		REQUIRE_FALSE(HBTK::check_in_range((double)HUGE_VAL, 0., 1.));
	}

	SECTION("vector") {
		std::vector<double> vec({ 0, 1, 2, 3, 4 });
		REQUIRE(HBTK::check_in_range(vec, -1., 10.));
		REQUIRE(HBTK::check_in_range(vec, -1., 4.));
		REQUIRE(HBTK::check_in_range(vec, 0., 10.));
		REQUIRE_FALSE(HBTK::check_in_range(vec, 0., 1.));
	}

	SECTION("array") {
		std::array<double, 5> vec;
		vec = { 0, 1, 2, 3, 4 };
		REQUIRE(HBTK::check_in_range(vec, -1., 10.));
		REQUIRE(HBTK::check_in_range(vec, -1., 4.));
		REQUIRE(HBTK::check_in_range(vec, 0., 10.));
		REQUIRE_FALSE(HBTK::check_in_range(vec, 0., 1.));
	}

}
