#include <HBTK/CartesianPoint.h>
#include <HBTK/CartesianVector.h>
#include <HBTK/CartesianFiniteLine.h>
#include <HBTK/CartesianLine.h>
#include <HBTK/Constants.h>

#include <catch.hpp>

TEST_CASE("Cartesian line 3D") {

	SECTION("2 point constructor") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 2, 3, 5 })
		);
		REQUIRE(line.origin().x() == 1);
		REQUIRE(line.origin().y() == 2);
		REQUIRE(line.origin().z() == 4);
		REQUIRE(line.direction().x() == Approx(1.));
		REQUIRE(line.direction().y() == Approx(1.));
		REQUIRE(line.direction().z() == Approx(1.));
	}

	SECTION("origin and direction constructor") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianVector3D({ 3, 5, 0 })
		);
		REQUIRE(line.origin().x() == 1);
		REQUIRE(line.origin().y() == 2);
		REQUIRE(line.origin().z() == 4);
		REQUIRE(line.direction().x() == Approx(3.));
		REQUIRE(line.direction().y() == Approx(5.));
		REQUIRE(line.direction().z() == Approx(0.0));
	}


	SECTION("Evaluation of a point on the line") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianVector3D({ 5, 0, 0 })
		), line2;
		line2 = line;
		REQUIRE(line(0) == HBTK::CartesianPoint3D({ 1, 2, 4 }));
		REQUIRE(line(1) == HBTK::CartesianPoint3D({ 6, 2, 4 }));
		REQUIRE(line(0.25) == HBTK::CartesianPoint3D({ 2.25, 2, 4 }));
		REQUIRE(line.evaluate(0) == HBTK::CartesianPoint3D({ 1, 2, 4 }));
		REQUIRE(line.evaluate(1) == HBTK::CartesianPoint3D({ 6, 2, 4 }));
		REQUIRE(line.evaluate(0.25) == HBTK::CartesianPoint3D({ 2.25, 2, 4 }));
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a point in space") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianPoint3D pnt({ 1, 0, 2 });
		double d = line.distance(pnt);
		REQUIRE(d == 1);
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a line in space, collinear") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		HBTK::CartesianLine3D line3(
			HBTK::CartesianPoint3D({ 1, 0, 0 }),
			HBTK::CartesianPoint3D({ 1, 0, 5 })
		);
		line2 = line;
		double d = line.distance(line3);
		REQUIRE(d == Approx(1.));
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a line in space, non-collinear") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		HBTK::CartesianLine3D line3(
			HBTK::CartesianPoint3D({ 1, -2, 2 }),
			HBTK::CartesianPoint3D({ 1, 2, 2 })
		);
		line2 = line;
		double d = line.distance(line3);
		REQUIRE(d == Approx(1.));
		REQUIRE(line2 == line);
	}

	SECTION("Compute intersection with point") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianPoint3D pnt({ 0, 0, 2 });
		REQUIRE(line.intersection(pnt) == Approx(0.4));
		pnt = HBTK::CartesianPoint3D({ 0, 0.0000001, 2 });
		REQUIRE(std::isnan(line.intersection(pnt)));
		REQUIRE(line2 == line);
	}

	SECTION("Compute intersection with a line") {
		HBTK::CartesianLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		HBTK::CartesianLine3D line3(
			HBTK::CartesianPoint3D({ 0, -2, 2 }),
			HBTK::CartesianPoint3D({ 0, 4, 2 })
		);
		line2 = line;
		double inter = line.intersection(line3);
		REQUIRE(inter == Approx(0.4));
		HBTK::CartesianLine3D line4(
			HBTK::CartesianPoint3D({ 1, 2, 2 }),
			HBTK::CartesianPoint3D({ 1, 4, 2 })
		);
		inter = line.intersection(line4);
		REQUIRE(std::isnan(inter));
		REQUIRE(line2 == line);
	}

	SECTION("Equalities (==, !=)") {
		HBTK::CartesianLine3D line1(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianVector3D({ 2, 3, 6 })
		);
		HBTK::CartesianLine3D line2(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianVector3D({ 4, 5, 9 })
		);
		HBTK::CartesianLine3D line3(
			HBTK::CartesianPoint3D({ 2, -1, -2 }),
			HBTK::CartesianVector3D({ 2, 3, 6 })
		);
		REQUIRE(line1 != line2);
		REQUIRE(line1 != line3);
		REQUIRE(line2 != line3);
		REQUIRE_FALSE(line1 == line2);
		REQUIRE_FALSE(line1 == line3);
		REQUIRE_FALSE(line2 == line3);
		line2 = line1;
		REQUIRE(line1 == line2);
	}
}

TEST_CASE("Cartesian line 2D") {

	SECTION("2 point constructor") {
		HBTK::CartesianLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		);
		REQUIRE(line.origin().x() == 1);
		REQUIRE(line.origin().y() == 2);
		REQUIRE(line.direction().x() == 2);
		REQUIRE(line.direction().y() == 3);
	}

	SECTION("start and direction constructor") {
		HBTK::CartesianLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianVector2D({ 2, 3 })
		);
		REQUIRE(line.origin().x() == 1);
		REQUIRE(line.origin().y() == 2);
		REQUIRE(line.direction().x() == 2);
		REQUIRE(line.direction().y() == 3);
	}

	SECTION("Evaluation of a point on the line") {
		HBTK::CartesianLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		), line2;
		line2 = line;
		REQUIRE(line(0) == HBTK::CartesianPoint2D({ 1, 2 }));
		REQUIRE(line(1) == HBTK::CartesianPoint2D({ 3, 5 }));
		REQUIRE(line(0.25) == HBTK::CartesianPoint2D({ 1.5, 2.75 }));
		REQUIRE(line.evaluate(0) == HBTK::CartesianPoint2D({ 1, 2 }));
		REQUIRE(line.evaluate(1) == HBTK::CartesianPoint2D({ 3, 5 }));
		REQUIRE(line.evaluate(0.25) == HBTK::CartesianPoint2D({ 1.5, 2.75 }));
		REQUIRE(line2 == line);
	}
	
	SECTION("Equalities (==, !=)") {
		HBTK::CartesianLine2D line1(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianVector2D({ 2, 3 })
		);
		HBTK::CartesianLine2D line2(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianVector2D({ 4, 5 })
		);
		HBTK::CartesianLine2D line3(
			HBTK::CartesianPoint2D({ 2, -1 }),
			HBTK::CartesianVector2D({ 2, 3 })
		);
		REQUIRE(line1 != line2);
		REQUIRE(line1 != line3);
		REQUIRE(line2 != line3);
		REQUIRE_FALSE(line1 == line2);
		REQUIRE_FALSE(line1 == line3);
		REQUIRE_FALSE(line2 == line3);
		line2 = line1;
		REQUIRE(line1 == line2);
	}
}
