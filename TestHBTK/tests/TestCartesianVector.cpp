#include <HBTK/CartesianPoint.h>
#include <HBTK/CartesianVector.h>
#include <HBTK/CartesianPlane.h>
#include <HBTK/Constants.h>

#include <catch.hpp>

#include <cmath>
#include <array>

TEST_CASE("Cartesian Vector 2D") {

	SECTION("Test constructor and x, y basics") {
		HBTK::CartesianVector2D vec({ 1., 3. });
		REQUIRE(vec.x() == 1.);
		REQUIRE(vec.y() == 3.);
		vec.y() = 4.;
		vec.x() = 5.;
		REQUIRE(vec.x() == 5.);
		REQUIRE(vec.y() == 4.);
	}

	SECTION("Test as_array functionality") {
		HBTK::CartesianVector2D vec({ 1, 3 });
		REQUIRE(vec.as_array() == std::array<double, 2>({ 1., 3. }));
		vec.as_array() = std::array<double, 2>({ 4., 5. });
		REQUIRE(vec.x() == 4.);
		REQUIRE(vec.y() == 5.);
	}

	SECTION("Equals and not equals") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 4 });
		REQUIRE_FALSE(vec1 == vec2);
		REQUIRE(vec1 != vec2);
		vec1 = vec2;
		REQUIRE(vec1 == vec2);
		REQUIRE_FALSE(vec1 != vec2);
	}

	SECTION("Subtration") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 6 });
		HBTK::CartesianVector2D vec3 = vec1 - vec2;
		REQUIRE(vec3.x() == -2);
		REQUIRE(vec3.y() == -4);
		vec1 -= vec2;
		REQUIRE(vec1 == vec3);
	}

	SECTION("Addition") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 6 });
		HBTK::CartesianVector2D vec3 = vec1 + vec2;
		REQUIRE(vec3.x() == 4);
		REQUIRE(vec3.y() == 8);
		vec1 += vec2;
		REQUIRE(vec1 == vec3);
	}

	SECTION("Scalar multiplication") {
		HBTK::CartesianVector2D vec1({ 1., 3. }), vec2;
		vec2 = 2. * vec1;
		REQUIRE(vec2.x() == 2.);
		REQUIRE(vec2.y() == 6.);
		REQUIRE(vec2 == (vec1 * 2.));
		vec1 *= 2.;
		REQUIRE(vec2 == vec1);
	}

	SECTION("Scalar division") {
		HBTK::CartesianVector2D vec1({ 1., 3. }), vec2;
		vec2 = vec1 / 2;
		REQUIRE(vec2.x() == 0.5);
		REQUIRE(vec2.y() == 1.5);
		vec1 /= 2.;
		REQUIRE(vec2 == vec1);
	}

	SECTION("Negation") {
		HBTK::CartesianVector2D vec1({ 1., 3. }), vec2;
		vec2 = -vec1;
		REQUIRE(vec2.x() == -1.);
		REQUIRE(vec2.y() == -3.);
		REQUIRE(vec1.x() == 1.);
		REQUIRE(vec1.y() == 3.);
	}

	SECTION("Addition to point") {
		HBTK::CartesianVector2D vec1({ 1, 2 });
		HBTK::CartesianPoint2D pnt1({ 3, 4 }), pnt2;
		pnt2 = vec1 + pnt1;
		REQUIRE(pnt2.x() == 4);
		REQUIRE(pnt2.y() == 6);
		REQUIRE(vec1.x() == 1.);
		REQUIRE(vec1.y() == 2.);
	}

	SECTION("Normalisation") {
		HBTK::CartesianVector2D vec1({ 2, 2 }), vec2({ -1, 0 });
		vec1.normalise();
		REQUIRE(vec1.x() == Approx(1. / sqrt(2)));
		REQUIRE(vec1.y() == Approx(1. / sqrt(2)));
		vec2.normalise();
		REQUIRE(vec2.x() == -1.);
		REQUIRE(vec2.y() == 0.);
	}

	SECTION("Dot product") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 6 });
		double res = vec1.dot(vec2);
		REQUIRE(res == 15.);
		REQUIRE(res == vec2.dot(vec1));
	}

	SECTION("Cross product (rotate 90)") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2;
		vec2 = vec1.cross();
		REQUIRE(vec1.x() == 1.);
		REQUIRE(vec1.y() == 2.);
		REQUIRE(vec2.x() == 2.);
		REQUIRE(vec2.y() == -1.);
	}

	SECTION("Magnitude") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 6 }), vec3({ -1, 1 });
		REQUIRE(vec1.magnitude() == Approx(sqrt(5.)));
		REQUIRE(vec2.magnitude() == Approx(3 * sqrt(5.)));
		REQUIRE(vec3.magnitude() == Approx(sqrt(2)));
		REQUIRE(abs(vec3) == Approx(sqrt(2)));
	}

	SECTION("Cosine of angle between 2 vectors") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 6 }), vec3({ -1, 1 });
		double cos_angle = vec1.cos_angle(vec2);
		REQUIRE(cos_angle == Approx(1.));
		cos_angle = vec1.cos_angle(vec3);
		REQUIRE(cos_angle == Approx(1. / sqrt(10.)));
	}

	SECTION("Angle between 2 vectors") {
		HBTK::CartesianVector2D vec1({ 1, 2 }), vec2({ 3, 6 }), vec3({ -1, 1 });
		double angle = vec1.angle(vec2);
		REQUIRE(angle == 0.0);
		angle = vec1.angle(vec3);
		REQUIRE(angle == Approx(acos(1. / sqrt(10.))));
	}
}



TEST_CASE("Cartesian Vector 3D") {

	SECTION("Test constructor and x, y, z basics") {
		HBTK::CartesianVector3D vec({ 1., 3., 6. });
		REQUIRE(vec.x() == 1.);
		REQUIRE(vec.y() == 3.);
		REQUIRE(vec.z() == 6.);
		vec.y() = 4.;
		vec.x() = 5.;
		vec.z() = 10;
		REQUIRE(vec.x() == 5.);
		REQUIRE(vec.y() == 4.);
		REQUIRE(vec.z() == 10);
	}

	SECTION("Test as_array functionality") {
		HBTK::CartesianVector3D vec({ 1, 3, 6 });
		REQUIRE(vec.as_array() == std::array<double, 3>({ 1., 3., 6 }));
		vec.as_array() = std::array<double, 3>({ 4., 5., 7 });
		REQUIRE(vec.x() == 4.);
		REQUIRE(vec.y() == 5.);
		REQUIRE(vec.z() == 7.);
	}

	SECTION("Equals and not equals") {
		HBTK::CartesianVector3D vec1({ 1, 2, 5 }), vec2({ 3, 4, 6 });
		REQUIRE_FALSE(vec1 == vec2);
		REQUIRE(vec1 != vec2);
		vec1 = vec2;
		REQUIRE(vec1 == vec2);
		REQUIRE_FALSE(vec1 != vec2);
	}

	SECTION("Subtration") {
		HBTK::CartesianVector3D vec1({ 1, 2, 5 }), vec2({ 3, 6, 11 });
		HBTK::CartesianVector3D vec3 = vec1 - vec2;
		REQUIRE(vec3.x() == -2);
		REQUIRE(vec3.y() == -4);
		REQUIRE(vec3.z() == -6);
		vec1 -= vec2;
		REQUIRE(vec1 == vec3);
	}

	SECTION("Addition") {
		HBTK::CartesianVector3D vec1({ 1, 2, 5 }), vec2({ 3, 6, 11 });
		HBTK::CartesianVector3D vec3 = vec1 + vec2;
		REQUIRE(vec3.x() == 4);
		REQUIRE(vec3.y() == 8);
		REQUIRE(vec3.z() == 16);
		vec1 += vec2;
		REQUIRE(vec1 == vec3);
	}

	SECTION("Scalar multiplication") {
		HBTK::CartesianVector3D vec1({ 1., 3., 5. }), vec2;
		vec2 = 2. * vec1;
		REQUIRE(vec2.x() == 2.);
		REQUIRE(vec2.y() == 6.);
		REQUIRE(vec2.z() == 10.);
		REQUIRE(vec2 == (vec1 * 2.));
		vec1 *= 2.;
		REQUIRE(vec2 == vec1);
	}

	SECTION("Scalar division") {
		HBTK::CartesianVector3D vec1({ 1., 3., 5. }), vec2;
		vec2 = vec1 / 2;
		REQUIRE(vec2.x() == 0.5);
		REQUIRE(vec2.y() == 1.5);
		REQUIRE(vec2.z() == 2.5);
		vec1 /= 2.;
		REQUIRE(vec2 == vec1);
	}

	SECTION("Negation") {
		HBTK::CartesianVector3D vec1({ 1., 3., 5. }), vec2;
		vec2 = -vec1;
		REQUIRE(vec2.x() == -1.);
		REQUIRE(vec2.y() == -3.);
		REQUIRE(vec2.z() == -5.);
		REQUIRE(vec1.x() == 1.);
		REQUIRE(vec1.y() == 3.);
		REQUIRE(vec1.z() == 5.);
	}

	SECTION("Addition to point") {
		HBTK::CartesianVector3D vec1({ 1, 2, 7 });
		HBTK::CartesianPoint3D pnt1({ 3, 4, 8 }), pnt2;
		pnt2 = vec1 + pnt1;
		REQUIRE(pnt2.x() == 4);
		REQUIRE(pnt2.y() == 6);
		REQUIRE(pnt2.z() == 15);
		REQUIRE(vec1.x() == 1.);
		REQUIRE(vec1.y() == 2.);
		REQUIRE(vec1.z() == 7.);
	}

	SECTION("Normalisation") {
		HBTK::CartesianVector3D vec1({ 2, 2, 2 }), vec2({ -1, 0, 0 });
		vec1.normalise();
		REQUIRE(vec1.x() == Approx(1. / sqrt(3.)));
		REQUIRE(vec1.y() == Approx(1. / sqrt(3.)));
		REQUIRE(vec1.z() == Approx(1. / sqrt(3.)));
		vec2.normalise();
		REQUIRE(vec2.x() == -1.);
		REQUIRE(vec2.y() == 0.);
		REQUIRE(vec2.z() == 0.);
	}

	SECTION("Dot product") {
		HBTK::CartesianVector3D vec1({ 1, 2, 7 }), vec2({ 3, 6, 9 });
		double res = vec1.dot(vec2);
		REQUIRE(res == 78.);
		REQUIRE(res == vec2.dot(vec1));
	}

	SECTION("Cross product (rotate 90)") {
		HBTK::CartesianVector3D vec1({ 1, 2, 3 }), vec2({ 6, 2, -1 }), vec3;
		vec3 = vec1.cross(vec2);
		REQUIRE(vec1.x() == 1.);
		REQUIRE(vec1.y() == 2.);
		REQUIRE(vec1.z() == 3.);
		REQUIRE(vec2.x() == 6.);
		REQUIRE(vec2.y() == 2.);
		REQUIRE(vec2.z() == -1.);
		REQUIRE(vec3.x() == -8.);
		REQUIRE(vec3.y() == 19.);
		REQUIRE(vec3.z() == -10);
	}

	SECTION("Magnitude") {
		HBTK::CartesianVector3D vec1({ 1, 2, 3 }), vec2({ 3, 6, 10 }), vec3({ -1, 1, 0 });
		REQUIRE(vec1.magnitude() == Approx(sqrt(14.)));
		REQUIRE(vec2.magnitude() == Approx(sqrt(145.)));
		REQUIRE(vec3.magnitude() == Approx(sqrt(2.)));
		REQUIRE(abs(vec3) == Approx(sqrt(2.)));
	}

	SECTION("Cosine of angle between 2 vectors") {
		HBTK::CartesianVector3D vec1({ 1, 2, 0 }), vec2({ 3, 6, 0 }), vec3({ -1, 1, 0 }), 
			vec4({ 2, 3, -4 });
		double cos_angle = vec1.cos_angle(vec2);
		REQUIRE(cos_angle == Approx(1.));
		cos_angle = vec1.cos_angle(vec3);
		REQUIRE(cos_angle == Approx(1. / sqrt(10.)));
		cos_angle = vec1.cos_angle(vec4);
		REQUIRE(cos_angle == Approx(8. / sqrt(145.)));
	}

	SECTION("Angle between 2 vectors") {
		HBTK::CartesianVector3D vec1({ 1, 2, 0 }), vec2({ 3, 6, 0 }), vec3({ -1, 1, 0 }),
			vec4({ 2, 3, -4 });
		double angle = vec1.angle(vec2);
		REQUIRE(angle == 0.0);
		angle = vec1.angle(vec3);
		REQUIRE(angle == Approx(acos(1. / sqrt(10.))));
		angle = vec1.angle(vec4);
		REQUIRE(angle == Approx(acos(8. / sqrt(145.))));
	}
}