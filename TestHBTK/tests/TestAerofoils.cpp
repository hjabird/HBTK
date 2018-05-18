#include <HBTK/AerofoilGeometry.h>
#include <HBTK/AerofoilGenerators.h>
#include <HBTK/CubicSpline1D.h>
#include <HBTK/Generators.h>

#include <vector>

#include <catch.hpp>

TEST_CASE("NACA 0012") {

	SECTION("NACA 0012: generate, 0 camber, +ve thickness, repoint") {
		HBTK::AerofoilGeometry foil = HBTK::AerofoilGenerators::naca_four_digit("0012");

		HBTK::CubicSpline1D camber = foil.get_camber_spline();
		bool zero_camber = true;
		std::vector<double> points_on_foil = HBTK::linspace(0, 1, 40);
		for (auto & p : points_on_foil) {
			if (camber(p) != 0.0) zero_camber = false;
		}
		REQUIRE(zero_camber);

		bool positive_thickness = true;
		HBTK::CubicSpline1D thickness = foil.get_thickness_spline();
		for (auto & p : points_on_foil) {
			if (thickness(p) < 0.0) positive_thickness = false;
		}
		REQUIRE(positive_thickness);
		
		bool matching_thick(true), matching_camber(true);
		foil.repoint([](double x) {return x; }, 400);

		HBTK::CubicSpline1D camber_2=  foil.get_camber_spline();
		zero_camber = true;
		for (auto & p : points_on_foil) {
			if (camber_2(p) != 0.0) zero_camber = false;
			if (camber(p) != Approx(camber_2(p))) matching_camber = false;
		}
		REQUIRE(zero_camber);
		REQUIRE(matching_camber);

		positive_thickness = true;
		HBTK::CubicSpline1D thickness_2 = foil.get_thickness_spline();
		for (auto & p : points_on_foil) {
			if (thickness_2(p) < 0.0) positive_thickness = false;
			if (thickness(p) != Approx(thickness_2(p))) matching_thick = false;
		}
		REQUIRE(positive_thickness);
		REQUIRE(matching_thick);
	}

	SECTION("NACA 0012: correct thickness distribution") {
		HBTK::AerofoilGeometry foil = HBTK::AerofoilGenerators::naca_four_digit("0012");
		HBTK::CubicSpline1D thickness = foil.get_thickness_spline();
		// Using data from airfoiltools.com NACA0012 (n0012-il)
		REQUIRE(2 * 0.001260 == Approx(thickness(1.0)));
		REQUIRE(2 * 0.013914 == Approx(thickness(0.904509)).margin(1e-6));
		REQUIRE(2 * 0.036670 == Approx(thickness(0.699682)).margin(1e-6));
		REQUIRE(2 * 0.052162 == Approx(thickness(0.512082)).margin(1e-6));
		REQUIRE(2 * 0.057403 == Approx(thickness(0.415822)).margin(1e-6));
		REQUIRE(2 * 0.059903 == Approx(thickness(0.322698)).margin(1e-6));
		REQUIRE(2 * 0.048457 == Approx(thickness(0.110163)).margin(1e-6));
		REQUIRE(2 * 0.024071 == Approx(thickness(0.020877)).margin(1e-6));

	}
}