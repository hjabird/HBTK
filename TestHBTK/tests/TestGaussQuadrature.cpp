

#include <HBTK\GaussianQuadrature.h>
#include <HBTK\Tolerances.h>

#include <gtest\gtest.h>

#include <vector>
#include <array>
#include <chrono>


TEST(GaussLegendre, Vect2)
{
	std::vector<double> points, weights;
	points.resize(2);
	weights.resize(2);
	HBTK::gauss_legendre<double>(2, points, weights);

	ASSERT_NEAR(1.0, weights[0], HBTK::tolerance<double>());
	ASSERT_NEAR(1.0, weights[1], HBTK::tolerance<double>());
	ASSERT_TRUE(points[0] == -points[1]);
}

TEST(GaussLegendre, VectNoPreallocated)
{
	auto quad = HBTK::gauss_legendre(2);
	auto points = quad.get_quadrature().first;
	auto weights = quad.get_quadrature().second;

	ASSERT_NEAR(1.0, weights[0], HBTK::tolerance<double>());
	ASSERT_NEAR(1.0, weights[1], HBTK::tolerance<double>());
	ASSERT_TRUE(points[0] == -points[1]);
}

TEST(GaussLegendre, Vect7)
{
	std::vector<double> points, weights;
	points.resize(7);
	weights.resize(7);
	HBTK::gauss_legendre<double, std::vector<double>>(7, points, weights);

	ASSERT_NEAR(0.417959183673469, weights[3], HBTK::tolerance<double>());
	ASSERT_NEAR(0.381830050505119, weights[2], HBTK::tolerance<double>());
	ASSERT_NEAR(0.279705391489277, weights[1], HBTK::tolerance<double>());
	ASSERT_NEAR(0.129484966168870, weights[0], HBTK::tolerance<double>());
	ASSERT_NEAR(weights[2], weights[4], HBTK::tolerance<double>());
	ASSERT_NEAR(weights[1], weights[5], HBTK::tolerance<double>());
	ASSERT_NEAR(weights[0], weights[6], HBTK::tolerance<double>());
	ASSERT_NEAR(0.0, points[3], HBTK::tolerance<double>());
	ASSERT_NEAR(0.405845151377397, points[2], HBTK::tolerance<double>());
	ASSERT_NEAR(0.741531185599394, points[1], HBTK::tolerance<double>());
	ASSERT_NEAR(0.949107912342759, points[0], HBTK::tolerance<double>());
	ASSERT_NEAR(points[0], -points[6], HBTK::tolerance<double>());
	ASSERT_NEAR(points[1], -points[5], HBTK::tolerance<double>());
	ASSERT_NEAR(points[2], -points[4], HBTK::tolerance<double>());
}

TEST(GaussLegendre, VectFloat7)
{
	std::vector<float> points, weights;
	points.resize(7);
	weights.resize(7);
	HBTK::gauss_legendre<float, std::vector<float>>(7, points, weights);

	ASSERT_NEAR((float) 0.417959183673469,  weights[3], HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.381830050505119, weights[2], HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.279705391489277, weights[1], (float)1.3*HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.129484966168870, weights[0], HBTK::tolerance<float>());
	ASSERT_NEAR((float) weights[2], weights[4], HBTK::tolerance<float>());
	ASSERT_NEAR(weights[1], weights[5], HBTK::tolerance<float>());
	ASSERT_NEAR(weights[0], weights[6], HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.0, points[3], HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.405845151377397, points[2], HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.741531185599394, points[1], HBTK::tolerance<float>());
	ASSERT_NEAR((float) 0.949107912342759, points[0], HBTK::tolerance<float>());
	ASSERT_NEAR(points[0], -points[6], HBTK::tolerance<float>());
	ASSERT_NEAR(points[1], -points[5], HBTK::tolerance<float>());
	ASSERT_NEAR(points[2], -points[4], HBTK::tolerance<float>());
}

TEST(GaussLegendre, Array100)
{
	// Should compute at compile time. Manual text by setting breakpoint in Gausslengendre
	std::array<double, 100> p, w;
	HBTK::gauss_legendre<100, double>(p, w);
}

TEST(GaussLaguerre, NameHere)
{
	auto quad = HBTK::gauss_laguerre(3);
	auto points = quad.get_quadrature().first;
	auto weights = quad.get_quadrature().second;

	ASSERT_NEAR(0.417959183673469, weights[3], HBTK::tolerance<double>());
	ASSERT_NEAR(0.381830050505119, weights[2], HBTK::tolerance<double>());
	ASSERT_NEAR(0.279705391489277, weights[1], HBTK::tolerance<double>());
	ASSERT_NEAR(0.129484966168870, weights[0], HBTK::tolerance<double>());
	ASSERT_NEAR(weights[2], weights[4], HBTK::tolerance<double>());
	ASSERT_NEAR(weights[1], weights[5], HBTK::tolerance<double>());
	ASSERT_NEAR(weights[0], weights[6], HBTK::tolerance<double>());
	ASSERT_NEAR(0.0, points[3], HBTK::tolerance<double>());
	ASSERT_NEAR(0.405845151377397, points[2], HBTK::tolerance<double>());
	ASSERT_NEAR(0.741531185599394, points[1], HBTK::tolerance<double>());
	ASSERT_NEAR(0.949107912342759, points[0], HBTK::tolerance<double>());
	ASSERT_NEAR(points[0], -points[6], HBTK::tolerance<double>());
	ASSERT_NEAR(points[1], -points[5], HBTK::tolerance<double>());
	ASSERT_NEAR(points[2], -points[4], HBTK::tolerance<double>());
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
