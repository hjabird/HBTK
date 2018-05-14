#include <HBTK/CartesianPoint.h>
#include <HBTK/CartesianVector.h>
#include <HBTK/CartesianFiniteLine.h>
#include <HBTK/CartesianLine.h>
#include <HBTK/Constants.h>

#include <catch.hpp>

TEST_CASE("Cartesian finite line 3D") {

	SECTION("2 point constructor") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		);
		REQUIRE(line.start().x() == 1);
		REQUIRE(line.end().x() == 3);
		REQUIRE(line.start().y() == 2);
		REQUIRE(line.end().y() == 5);
		REQUIRE(line.start().z() == 4);
		REQUIRE(line.end().z() == 9);
	}

	SECTION("start and direction constructor") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianVector3D({ 2, 3, 5 })
		);
		REQUIRE(line.start().x() == 1);
		REQUIRE(line.end().x() == 3);
		REQUIRE(line.start().y() == 2);
		REQUIRE(line.end().y() == 5);
		REQUIRE(line.start().z() == 4);
		REQUIRE(line.end().z() == 9);
	}

	SECTION("direction and end constructor") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianVector3D({ 2, 3, 5 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		);
		REQUIRE(line.start().x() == 1);
		REQUIRE(line.end().x() == 3);
		REQUIRE(line.start().y() == 2);
		REQUIRE(line.end().y() == 5);
		REQUIRE(line.start().z() == 4);
		REQUIRE(line.end().z() == 9);
	}

	SECTION("Evaluation of a point on the line") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		), line2;
		line2 = line;
		REQUIRE(line(0) == HBTK::CartesianPoint3D({ 1, 2, 4 }));
		REQUIRE(line(1) == HBTK::CartesianPoint3D({ 3, 5, 9 }));
		REQUIRE(line(0.25) == HBTK::CartesianPoint3D({ 1.5, 2.75, 5.25 }));
		REQUIRE(line.evaluate(0) == HBTK::CartesianPoint3D({ 1, 2, 4 }));
		REQUIRE(line.evaluate(1) == HBTK::CartesianPoint3D({ 3, 5, 9 }));
		REQUIRE(line.evaluate(0.25) == HBTK::CartesianPoint3D({ 1.5, 2.75, 5.25 }));
		REQUIRE(line2 == line);
	}

	SECTION("magnitude (length)") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		);
		REQUIRE(line.magnitude() == Approx(sqrt(38.)));
	}

	SECTION("Convertion to vector") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		), line2;
		line2 = line;
		HBTK::CartesianVector3D vec({ 2, 3, 5 });
		REQUIRE(vec == line.vector());
		REQUIRE(line2 == line);
	}

	SECTION("Computation of midpoint") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		), line2;
		line2 = line;
		HBTK::CartesianPoint3D pnt({ 2, 3.5, 6.5 });
		REQUIRE(pnt == line.midpoint());
		REQUIRE(line2 == line);
	}
	
	SECTION("Cast to 3D (infinite) line") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 1, 2, 4 }),
			HBTK::CartesianPoint3D({ 3, 5, 9 })
		), line2;
		line2 = line;
		HBTK::CartesianLine3D inf_line = (HBTK::CartesianLine3D)line;
		REQUIRE(line.vector() == inf_line.direction());
		REQUIRE(line.start() == inf_line.origin());
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a point in space where end points don't matter.") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianPoint3D pnt({ 1, 0, 2});
		double d = line.distance(pnt);
		REQUIRE(d == 1);
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a point in space affected by the finiteness of the line") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianPoint3D pnt({ 1, 0, -1 });
		double d = line.distance(pnt);
		REQUIRE(d == Approx(sqrt(2)));
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a line in space unaffected by the finiteness of the line and collinear") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;		
		HBTK::CartesianFiniteLine3D line3(
			HBTK::CartesianPoint3D({ 1, 0, 0 }),
			HBTK::CartesianPoint3D({ 1, 0, 5 })
		);
		line2 = line;
		double d = line.distance(line3);
		REQUIRE(d == Approx(1.));
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a line in space unaffected by the finiteness of the line, non-collinear") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		HBTK::CartesianFiniteLine3D line3(
			HBTK::CartesianPoint3D({ 1, -2, 2 }),
			HBTK::CartesianPoint3D({ 1, 2, 2 })
		);
		line2 = line;
		double d = line.distance(line3);
		REQUIRE(d == Approx(1.));
		REQUIRE(line2 == line);
	}

	SECTION("Distance to a line in space affected by the finiteness of the line, non-collinear") {
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		HBTK::CartesianFiniteLine3D line3(
			HBTK::CartesianPoint3D({ 1, 2, 2 }),
			HBTK::CartesianPoint3D({ 1, 4, 2 })
		);
		line2 = line;
		double d = line.distance(line3);
		REQUIRE(d == Approx(sqrt(5.)));
		REQUIRE(line2 == line);
	}

	SECTION("Compute intersection with point") {
		HBTK::CartesianFiniteLine3D line(
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
		HBTK::CartesianFiniteLine3D line(
			HBTK::CartesianPoint3D({ 0, 0, 0 }),
			HBTK::CartesianPoint3D({ 0, 0, 5 })
		), line2;
		HBTK::CartesianFiniteLine3D line3(
			HBTK::CartesianPoint3D({ 0, -2, 2 }),
			HBTK::CartesianPoint3D({ 0, 4, 2 })
		);
		line2 = line;
		double inter = line.intersection(line3);
		REQUIRE(inter == Approx(0.4));
		HBTK::CartesianFiniteLine3D line4(
			HBTK::CartesianPoint3D({ 1, 2, 2 }),
			HBTK::CartesianPoint3D({ 1, 4, 2 })
		);
		inter = line.intersection(line4);
		REQUIRE(std::isnan(inter));
		REQUIRE(line2 == line);
	}
}

TEST_CASE("Cartesian finite line 2D") {

	SECTION("2 point constructor") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		);
		REQUIRE(line.start().x() == 1);
		REQUIRE(line.end().x() == 3);
		REQUIRE(line.start().y() == 2);
		REQUIRE(line.end().y() == 5);
	}

	SECTION("start and direction constructor") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianVector2D({ 2, 3 })
		);
		REQUIRE(line.start().x() == 1);
		REQUIRE(line.end().x() == 3);
		REQUIRE(line.start().y() == 2);
		REQUIRE(line.end().y() == 5);
	}

	SECTION("direction and end constructor") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianVector2D({ 2, 3 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		);
		REQUIRE(line.start().x() == 1);
		REQUIRE(line.end().x() == 3);
		REQUIRE(line.start().y() == 2);
		REQUIRE(line.end().y() == 5);
	}

	SECTION("Evaluation of a point on the line") {
		HBTK::CartesianFiniteLine2D line(
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

	SECTION("magnitude (length)") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 4, 6 })
		);
		REQUIRE(line.magnitude() == 5.);
	}

	SECTION("Convertion to vector") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianVector2D vec({ 2, 3 });
		REQUIRE(vec == line.vector());
		REQUIRE(line2 == line);
	}

	SECTION("Computation of midpoint") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianPoint2D pnt({ 2, 3.5 });
		REQUIRE(pnt == line.midpoint());
		REQUIRE(line2 == line);
	}

	SECTION("Cast to 2D (infinite) line") {
		HBTK::CartesianFiniteLine2D line(
			HBTK::CartesianPoint2D({ 1, 2 }),
			HBTK::CartesianPoint2D({ 3, 5 })
		), line2;
		line2 = line;
		HBTK::CartesianLine2D inf_line = (HBTK::CartesianLine2D)line;
		REQUIRE(line.vector() == inf_line.direction());
		REQUIRE(line.start() == inf_line.origin());
		REQUIRE(line2 == line);
	}
}
