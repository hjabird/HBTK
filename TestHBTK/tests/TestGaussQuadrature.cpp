

#include <HBTK/GaussianQuadrature.h>
#include <HBTK/Tolerances.h>

#include <catch2/catch.hpp>

#include <vector>
#include <array>
#include <chrono>


TEST_CASE("Gauss Legendre quadratures generation")
{
	SECTION("Basic 1 point generation in preallocated std::vector<>") {
		std::vector<double> points, weights;
		points.resize(1);
		weights.resize(1);
		HBTK::gauss_legendre<double>(1, points, weights);
		REQUIRE(2.0 == Approx(weights[0]));
		REQUIRE(points[0] == Approx(0.0));
	}

	SECTION("Basic 2 point generation in preallocated std::vector<>") {
		std::vector<double> points, weights;
		points.resize(2);
		weights.resize(2);
		HBTK::gauss_legendre<double>(2, points, weights);
		REQUIRE(1.0 == Approx(weights[0]));
		REQUIRE(1.0 == Approx(weights[1]));
		REQUIRE(points[0] == -points[1]);
	}

	SECTION("Basic 2 point generation in returned std::vector<>") {
		std::vector<double> points, weights;
		auto quad = HBTK::gauss_legendre(2);
		points = quad.get_quadrature().first;
		weights = quad.get_quadrature().second;
		REQUIRE(1.0 == Approx(weights[0]));
		REQUIRE(1.0 == Approx(weights[1]));
		REQUIRE(points[0] == -points[1]);
	}

	SECTION("7 points generation to std::vector<double>.") {
		std::vector<double> points, weights;
		points.resize(7);
		weights.resize(7);
		HBTK::gauss_legendre<double, std::vector<double>>(7, points, weights);
		REQUIRE(0.417959183673469 == Approx(weights[3]));
		REQUIRE(0.381830050505119 == Approx(weights[2]));
		REQUIRE(0.279705391489277 == Approx(weights[1]));
		REQUIRE(0.129484966168870 == Approx(weights[0]));
		REQUIRE(weights[2] == Approx(weights[4]));
		REQUIRE(weights[1] == Approx(weights[5]));
		REQUIRE(weights[0] == Approx(weights[6]));
		REQUIRE(0.0 == Approx(points[3]));
		REQUIRE(0.405845151377397 == Approx(points[2]));
		REQUIRE(0.741531185599394 == Approx(points[1]));
		REQUIRE(0.949107912342759 == Approx(points[0]));
		REQUIRE(points[0] == Approx(-points[6]));
		REQUIRE(points[1] == Approx(-points[5]));
		REQUIRE(points[2] == Approx(-points[4]));
	}

	SECTION("7 point generation to std::vector<float>.")
	{
		std::vector<float> points, weights;
		points.resize(7);
		weights.resize(7);
		HBTK::gauss_legendre<float, std::vector<float>>(7, points, weights);

		REQUIRE((float) 0.417959183673469 == Approx(weights[3]));
		REQUIRE((float) 0.381830050505119 == Approx(weights[2]));
		REQUIRE((float) 0.279705391489277 == Approx(weights[1]));
		REQUIRE((float) 0.129484966168870 == Approx(weights[0]));
		REQUIRE((float) weights[2] == Approx(weights[4]));
		REQUIRE(weights[1] == Approx(weights[5]));
		REQUIRE(weights[0] == Approx(weights[6]));
		REQUIRE((float) 0.0 == Approx(points[3]).margin(1e-10));
		REQUIRE((float) 0.405845151377397 == Approx(points[2]));
		REQUIRE((float) 0.741531185599394 == Approx(points[1]));
		REQUIRE((float) 0.949107912342759 == Approx(points[0]));
		REQUIRE(points[0] == Approx(-points[6]));
		REQUIRE(points[1] == Approx(-points[5]));
		REQUIRE(points[2] == Approx(-points[4]));
	}

}


TEST_CASE("Gauss Laguerre quadrature generation")
{
	SECTION("3 point Gauss laguere quadrature generation.") {
		auto quad = HBTK::gauss_laguerre(3);
		auto points = quad.get_quadrature().first;
		auto weights = quad.get_quadrature().second;
		REQUIRE(0.711093 == Approx(weights[0]));
		REQUIRE(0.278518 == Approx(weights[1]));
		REQUIRE(0.0103893 == Approx(weights[2]));
		REQUIRE(0.415775 == Approx(points[0]));
		REQUIRE(2.29428 == Approx(points[1]));
		REQUIRE(6.28995 == Approx(points[2]));
	}

	SECTION("5 point Gauss laguere quadrature generation.") {
		/*	From Wolfram Math world.
			0.26356	0.521756
			1.4134	0.398667
			3.59643	0.0759424
			7.08581	0.00361176
			12.6408	0.00002337 */
		auto quad = HBTK::gauss_laguerre(5);
		auto points = quad.get_quadrature().first;
		auto weights = quad.get_quadrature().second;
		REQUIRE(0.521756 == Approx(weights[0]));
		REQUIRE(0.398667 == Approx(weights[1]));
		REQUIRE(0.0759424 == Approx(weights[2]));
		REQUIRE(0.00361176 == Approx(weights[3]));
		REQUIRE(0.00002337 == Approx(weights[4]));
		REQUIRE(0.26356 == Approx(points[0]));
		REQUIRE(1.4134 == Approx(points[1]));
		REQUIRE(3.59643 == Approx(points[2]));
		REQUIRE(7.08581 == Approx(points[3]));
		REQUIRE(12.6408 == Approx(points[4]));
	}
}

TEST_CASE("Gauss Hermite quadrature generation")
{
	SECTION("3 point Gauss hermite quadrature generation.") {
		auto quad = HBTK::gauss_hermite(3);
		auto points = quad.get_quadrature().first;
		auto weights = quad.get_quadrature().second;
		REQUIRE((2./3.) * sqrt(HBTK::Constants::pi()) == Approx(weights[0]));
		REQUIRE(sqrt(HBTK::Constants::pi()) / 6. == Approx(weights[1]));
		REQUIRE(sqrt(HBTK::Constants::pi()) / 6. == Approx(weights[2]));
		REQUIRE(0.0 == Approx(points[0]).margin(1e-15));
		REQUIRE(-0.5 * sqrt(6.) == Approx(points[1]));
		REQUIRE(0.5 * sqrt(6.) == Approx(points[2]));
	}

	SECTION("4 point Gauss hermite quadrature generation.") {
		auto quad = HBTK::gauss_hermite(4);
		auto points = quad.get_quadrature().first;
		auto weights = quad.get_quadrature().second;
		REQUIRE(sqrt(HBTK::Constants::pi()) / (4 * (3 - sqrt(6.)))
			== Approx(weights[0]));
		REQUIRE(sqrt(HBTK::Constants::pi()) / (4 * (3 - sqrt(6.)))
			== Approx(weights[1]));
		REQUIRE(sqrt(HBTK::Constants::pi()) / (4 * (3 + sqrt(6.)))
			== Approx(weights[2]));
		REQUIRE(sqrt(HBTK::Constants::pi()) / (4 * (3 + sqrt(6.)))
			== Approx(weights[3]));
		REQUIRE(-sqrt((3. - sqrt(6.)) / 2.) == Approx(points[0]));
		REQUIRE(sqrt((3. - sqrt(6.)) / 2.) == Approx(points[1]));
		REQUIRE(-sqrt((3. + sqrt(6.)) / 2.) == Approx(points[2]));
		REQUIRE(sqrt((3. + sqrt(6.)) / 2.) == Approx(points[3]));
	}
}

TEST_CASE("Gauss Chebyshev type 1 quadrature") {

	SECTION("5 point Gauss chebyshev 1 quadrature generation") {
		auto quad = HBTK::gauss_chebyshev1(5);
		auto points = quad.get_quadrature().first;
		auto weights = quad.get_quadrature().second;
		REQUIRE(HBTK::Constants::pi() / 5. == Approx(weights[0]));
		REQUIRE(HBTK::Constants::pi() / 5. == Approx(weights[1]));
		REQUIRE(HBTK::Constants::pi() / 5. == Approx(weights[2]));
		REQUIRE(HBTK::Constants::pi() / 5. == Approx(weights[3]));
		REQUIRE(HBTK::Constants::pi() / 5. == Approx(weights[4]));
		REQUIRE(-0.5 * sqrt(0.5 * (5. - sqrt(5.))) == Approx(points[0]));
		REQUIRE(-0.5 * sqrt(0.5 * (5. + sqrt(5.))) == Approx(points[1]));
		REQUIRE(0.0 == Approx(points[2]).margin(1e-15));
		REQUIRE(0.5 * sqrt(0.5 * (5. - sqrt(5.))) == Approx(points[3]));
		REQUIRE(0.5 * sqrt(0.5 * (5. + sqrt(5.))) == Approx(points[4]));
	}
}

TEST_CASE("Gauss Chebyshev type 2 quadrature") {

	SECTION("5 point Gauss chebyshev 2 quadrature generation") {
		auto quad = HBTK::gauss_chebyshev2(5);
		auto points = quad.get_quadrature().first;
		auto weights = quad.get_quadrature().second;
		REQUIRE(0.3926990816987241548078 == Approx(weights[0]));
		REQUIRE(0.5235987755982988730771 == Approx(weights[1]));
		REQUIRE(0.3926990816987241548078 == Approx(weights[2]));
		REQUIRE(0.1308996938995747182693 == Approx(weights[3]));
		REQUIRE(0.1308996938995747182693 == Approx(weights[4]));
		REQUIRE(-0.5 == Approx(points[0]));
		REQUIRE(0.0 == Approx(points[1]).margin(1e-15));
		REQUIRE(0.5  == Approx(points[2]));
		REQUIRE(0.8660254037844386467637== Approx(points[3]));
		REQUIRE(-0.8660254037844386467637 == Approx(points[4]));
	}
}

