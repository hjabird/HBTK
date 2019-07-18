#include <HBTK/CartesianPoint.h>
#include <HBTK/CartesianVector.h>
#include <HBTK/CartesianPlane.h>
#include <HBTK/Constants.h>

#include <catch2/catch.hpp>

#include <cmath>
#include <array>

TEST_CASE("Cartesian plane") {
	SECTION("3 point constructor - simple 1") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 2, 1, 1 }),
			HBTK::CartesianPoint3D({ 1, 2, 1 })
		);
		HBTK::CartesianPoint3D pnt = plane(HBTK::CartesianPoint2D({ 0,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1,1,1 }));
		pnt = plane(HBTK::CartesianPoint2D({ 1,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 2,1,1 }));
		pnt = plane(HBTK::CartesianPoint2D({ 0,1 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1, 2, 1 }));
	}


	SECTION("3 point constructor - simple 2") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 1, 3, 1 }),
			HBTK::CartesianPoint3D({ 3, 1, 1 })
		);
		HBTK::CartesianPoint3D pnt = plane(HBTK::CartesianPoint2D({ 0,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1,1,1 }));
		pnt = plane(HBTK::CartesianPoint2D({ 1,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1,2,1 }));
		pnt = plane(HBTK::CartesianPoint2D({ 0,1 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 2, 1, 1 }));
	}

	SECTION("3 point constructor - complex") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 2, 1, 2 }),
			HBTK::CartesianPoint3D({ 1, 1, 2 })
		);
		HBTK::CartesianPoint3D pnt = plane(HBTK::CartesianPoint2D({ 0,0 })); 
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1,1,1 }));
		pnt = plane(HBTK::CartesianPoint2D({ 1,0 }));
		HBTK::CartesianVector3D vec({ 1, 0, 1 });
		vec.normalise();
		HBTK::CartesianPoint3D tmp_pnt = HBTK::CartesianPoint3D({ 1, 1, 1 }) + vec;
		REQUIRE(pnt == tmp_pnt);
		pnt = plane(HBTK::CartesianPoint2D({ 0, 1 }));
		vec = HBTK::CartesianVector3D({ -1, 0, 1 });
		vec.normalise();
		tmp_pnt = HBTK::CartesianPoint3D({ 1, 1, 1 }) + vec;
		REQUIRE(pnt.x() == Approx(tmp_pnt.x()));
		REQUIRE(pnt.y() == Approx(tmp_pnt.y()));
		REQUIRE(pnt.z() == Approx(tmp_pnt.z()));
	}

	SECTION("Origin and normal constructor") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianVector3D({0, 1, 0})
		);
		HBTK::CartesianPoint3D pnt = plane(HBTK::CartesianPoint2D({ 0,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1,1,1 }));
		pnt = plane(HBTK::CartesianPoint2D({ 1,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 2, 1, 1}));
		pnt = plane(HBTK::CartesianPoint2D({ 0, 1 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1, 1, 0}));
	}

	SECTION("Origin function") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ -1, 2, 3 }),
			HBTK::CartesianPoint3D({ -2, 4, 5 })
		);
		HBTK::CartesianPoint3D pnt = plane(HBTK::CartesianPoint2D({ 0,0 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1,1,1 }));
		REQUIRE(plane.origin() == HBTK::CartesianPoint3D({ 1,1,1 }));
		plane.origin() = HBTK::CartesianPoint3D({ 0, 0, 0 });
		REQUIRE(plane.origin() == HBTK::CartesianPoint3D({ 0, 0, 0 }));
	}

	SECTION("Distance from a point in space") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 2, 1, 1 }),
			HBTK::CartesianPoint3D({ 1, 2, 1 })
		);
		double d = plane.distance(HBTK::CartesianPoint3D({ 1, 1, 2 }));
		REQUIRE(d == 1);
	}	
	
	SECTION("Projection of a point onto the plane") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 2, 1, 1 }),
			HBTK::CartesianPoint3D({ 1, 2, 1 })
		);
		HBTK::CartesianPoint2D pnt = plane.projection(HBTK::CartesianPoint3D({ 1, 1, 2 }));
		REQUIRE(pnt == HBTK::CartesianPoint2D({ 0, 0 }));
		pnt = plane.projection(HBTK::CartesianPoint3D({ 1, 2, 2 }));
		REQUIRE(pnt == HBTK::CartesianPoint2D({ 0, 1 }));
	}

	SECTION("Closest point on plane to point in space") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 2, 1, 1 }),
			HBTK::CartesianPoint3D({ 1, 2, 1 })
		);
		HBTK::CartesianPoint3D pnt = plane.closest_point(HBTK::CartesianPoint3D({ 1, 1, 2 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1, 1, 1 }));
		pnt = plane.closest_point(HBTK::CartesianPoint3D({ 1, 2, 2 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1, 2, 1 }));
	}

	SECTION("Point symmetrically positioned across plane.") {
		HBTK::CartesianPlane plane(
			HBTK::CartesianPoint3D({ 1, 1, 1 }),
			HBTK::CartesianPoint3D({ 2, 1, 1 }),
			HBTK::CartesianPoint3D({ 1, 2, 1 })
		);
		HBTK::CartesianPoint3D pnt = plane.symmetric_point(HBTK::CartesianPoint3D({ 1, 1, 2 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1, 1, 0 }));
		pnt = plane.symmetric_point(HBTK::CartesianPoint3D({ 1, 2, 2 }));
		REQUIRE(pnt == HBTK::CartesianPoint3D({ 1, 2, 0 }));
	}
}
