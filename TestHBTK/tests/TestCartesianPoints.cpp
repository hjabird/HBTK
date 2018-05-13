#include <HBTK/CartesianPoint.h>
#include <HBTK/CartesianVector.h>
#include <HBTK/CartesianPlane.h>
#include <HBTK/Constants.h>

#include <catch.hpp>

#include <cmath>
#include <array>

TEST_CASE("Cartesian Point 2D") {
	SECTION("Test constructor and x, y basics") {
		HBTK::CartesianPoint2D pnt({ 1., 3.});
		REQUIRE(pnt.x() == 1.);
		REQUIRE(pnt.y() == 3.);
		pnt.y() = 4.;
		pnt.x() = 5.;
		REQUIRE(pnt.x() == 5.);
		REQUIRE(pnt.y() == 4.);
	}

	SECTION("Test as_array functionality") {
		HBTK::CartesianPoint2D pnt({ 1, 3 });
		REQUIRE(pnt.as_array() == std::array<double, 2>({ 1., 3. }));
		pnt.as_array() = std::array<double, 2>({ 4., 5. });
		REQUIRE(pnt.x() == 4.);
		REQUIRE(pnt.y() == 5.);
	}

	SECTION("Equals and not equals") {
		HBTK::CartesianPoint2D pnt1({ 1, 2 }), pnt2({ 3, 4 });
		REQUIRE_FALSE(pnt1 == pnt2);
		REQUIRE(pnt1 != pnt2);
		pnt2 = pnt1;
		REQUIRE(pnt1 == pnt2);
		REQUIRE_FALSE(pnt1 != pnt2);
	}

	SECTION("Subtration") {
		HBTK::CartesianPoint2D pnt1({ 1, 2 }), pnt2({ 3, 6 });
		HBTK::CartesianVector2D vec = pnt1 - pnt2;
		REQUIRE(vec.x() == -2);
		REQUIRE(vec.y() == -4);
	}

	SECTION("Vector addition") {
		HBTK::CartesianPoint2D pnt1({ 1, 2 }), pnt2;
		HBTK::CartesianVector2D vec({ 4, 6 });
		pnt2 = pnt1 + vec;
		REQUIRE(pnt2.x() == 5);
		REQUIRE(pnt2.y() == 8);
		REQUIRE(pnt1.x() == 1.);
		REQUIRE(pnt1.y() == 2.);
		pnt1 += vec;
		REQUIRE(pnt1 == pnt2);
	}

	SECTION("Vector subtraction") {
		HBTK::CartesianPoint2D pnt1({ 1, 2 }), pnt2;
		HBTK::CartesianVector2D vec({ 4, 6 });
		pnt2 = pnt1 - vec;
		REQUIRE(pnt2.x() == -3);
		REQUIRE(pnt2.y() == -4);
		REQUIRE(pnt1.x() == 1.);
		REQUIRE(pnt1.y() == 2.);
		pnt1 -= vec;
		REQUIRE(pnt1 == pnt2);
	}

	SECTION("Origin placement") {
		HBTK::CartesianPoint2D pnt1, pnt2;
		pnt2 = pnt1.origin();
		REQUIRE(pnt2.x() == 0);
		REQUIRE(pnt2.y() == 0);
	}

	SECTION("Rotation about origin") {
		HBTK::CartesianPoint2D pnt1({ 1, 0 });
		pnt1.rotate(HBTK::Constants::pi() / 4.);
		REQUIRE(pnt1.x() == Approx(1. / sqrt(2)));
		REQUIRE(pnt1.y() == Approx(1. / sqrt(2)));
		pnt1.rotate(HBTK::Constants::pi() / 4.);
		REQUIRE(pnt1.x() == Approx(0.).margin(1e-15));
		REQUIRE(pnt1.y() == Approx(1.));
	}

	SECTION("Rotation about another point") {
		HBTK::CartesianPoint2D pnt1({ 2, 1 }), pnt2({ 1, 1 });
		pnt1.rotate(HBTK::Constants::pi() / 4., pnt2);
		REQUIRE(pnt1.x() == Approx(1. / sqrt(2) + 1));
		REQUIRE(pnt1.y() == Approx(1. / sqrt(2) + 1));
		pnt1.rotate(HBTK::Constants::pi() / 4., pnt2);
		REQUIRE(pnt1.x() == Approx(1.));
		REQUIRE(pnt1.y() == Approx(2.));
	}
}


TEST_CASE("Cartesian Point 3D") {
	SECTION("Test constructor and x, y, z basics") {
		HBTK::CartesianPoint3D pnt({ 1., 3., 7. });
		REQUIRE(pnt.x() == 1.);
		REQUIRE(pnt.y() == 3.);
		REQUIRE(pnt.z() == 7.);
		pnt.y() = 4.;
		pnt.x() = 5.;
		pnt.z() = 8.;
		REQUIRE(pnt.x() == 5.);
		REQUIRE(pnt.y() == 4.);
		REQUIRE(pnt.z() == 8.);
	}

	SECTION("Test as_array functionality") {
		HBTK::CartesianPoint3D pnt({ 1, 3, 5. });
		REQUIRE(pnt.as_array() == std::array<double, 3>({ 1., 3., 5. }));
		pnt.as_array() = std::array<double, 3>({ 4., 5., 6. });
		REQUIRE(pnt.x() == 4.);
		REQUIRE(pnt.y() == 5.);
		REQUIRE(pnt.z() == 6.);
	}

	SECTION("Equals and not equals") {
		HBTK::CartesianPoint3D pnt1({ 1., 2., 5. }), pnt2({ 3., 4., 6. });
		REQUIRE_FALSE(pnt1 == pnt2);
		REQUIRE(pnt1 != pnt2);
		pnt2 = pnt1;
		REQUIRE(pnt1 == pnt2);
		REQUIRE_FALSE(pnt1 != pnt2);
	}

	SECTION("Subtration") {
		HBTK::CartesianPoint3D pnt1({ 1., 2., 3. }), pnt2({ 4., 7., 9. });
		HBTK::CartesianVector3D vec = pnt1 - pnt2;
		REQUIRE(vec.x() == -3);
		REQUIRE(vec.y() == -5);
		REQUIRE(vec.z() == -6);
	}

	SECTION("Vector addition") {
		HBTK::CartesianPoint3D pnt1({ 1., 2., 4. }), pnt2;
		HBTK::CartesianVector3D vec({ 4., 6., 10. });
		pnt2 = pnt1 + vec;
		REQUIRE(pnt2.x() == 5.);
		REQUIRE(pnt2.y() == 8.);
		REQUIRE(pnt2.z() == 14.);
		REQUIRE(pnt1.x() == 1.);
		REQUIRE(pnt1.y() == 2.);
		REQUIRE(pnt1.z() == 4.);
		pnt1 += vec;
		REQUIRE(pnt1 == pnt2);
	}

	SECTION("Vector subtraction") {
		HBTK::CartesianPoint3D pnt1({ 1., 2., 4. }), pnt2;
		HBTK::CartesianVector3D vec({ 4., 6., 10. });
		pnt2 = pnt1 - vec;
		REQUIRE(pnt2.x() == -3.);
		REQUIRE(pnt2.y() == -4.);
		REQUIRE(pnt2.z() == -6.);
		REQUIRE(pnt1.x() == 1.);
		REQUIRE(pnt1.y() == 2.);
		REQUIRE(pnt1.z() == 4.);
		pnt1 -= vec;
		REQUIRE(pnt1 == pnt2);
	}

	SECTION("Origin placement") {
		HBTK::CartesianPoint3D pnt1, pnt2;
		pnt2 = pnt1.origin();
		REQUIRE(pnt2.x() == 0);
		REQUIRE(pnt2.y() == 0);
		REQUIRE(pnt2.z() == 0);
	}

	SECTION("Distance") {
		HBTK::CartesianPoint3D pnt1({ 1., 2., 3. });
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 1, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 1, 0 }));
		double d = pnt1.distance(plane);
		REQUIRE(d == Approx(3.));
		pnt1 = HBTK::CartesianPoint3D({ 1, 2, 0 });
		d = pnt1.distance(plane);
		REQUIRE(d == 0.);
	}
}


