#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Quad1D/GaussLegendre.h"
#include "../Quad1D/Tolerances.h"

#include <vector>
#include <array>
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestQuad1D
{		
	TEST_CLASS(Test_GaussLegendre)
	{
	public:
		
		TEST_METHOD(Gauss_legendre_vect_2)
		{
			std::vector<double> points, weights;
			points.resize(2);
			weights.resize(2);
			Quad1D::gauss_legendre<double>(2, points, weights);

			Assert::AreEqual(1.0, weights[0], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights = 1 for two points.", LINE_INFO());
			Assert::AreEqual(1.0, weights[1], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights = 1 for two points.", LINE_INFO());
			Assert::IsTrue(points[0] == -points[1], L"GUASS LEGENDRE DYNAMIC VECTOR: symetric weights", LINE_INFO());
		}

		TEST_METHOD(Gauss_legendre_vect_7)
		{
			std::vector<double> points, weights;
			points.resize(7);
			weights.resize(7);
			Quad1D::gauss_legendre<double, std::vector<double>>(7, points, weights);

			Assert::AreEqual(0.417959183673469, weights[3], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(0.381830050505119, weights[2], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(0.279705391489277, weights[1], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(0.129484966168870, weights[0], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(weights[2], weights[4], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(weights[1], weights[5], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(weights[0], weights[6], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(0.0, points[3], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(0.405845151377397, points[2], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(0.741531185599394, points[1], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(0.949107912342759, points[0], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(points[0], -points[6], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(points[1], -points[5], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(points[2], -points[4], Quad1D::tolerance<double>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
		}

		TEST_METHOD(Gauss_legendre_vect_float7)
		{
			std::vector<float> points, weights;
			points.resize(7);
			weights.resize(7);
			Quad1D::gauss_legendre<float, std::vector<float>>(7, points, weights);

			Assert::AreEqual((float) 0.417959183673469,  weights[3], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual((float) 0.381830050505119, weights[2], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual((float) 0.279705391489277, weights[1], (float)1.3*Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual((float) 0.129484966168870, weights[0], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual((float) weights[2], weights[4], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(weights[1], weights[5], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual(weights[0], weights[6], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected weights", LINE_INFO());
			Assert::AreEqual((float) 0.0, points[3], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual((float) 0.405845151377397, points[2], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual((float) 0.741531185599394, points[1], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual((float) 0.949107912342759, points[0], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(points[0], -points[6], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(points[1], -points[5], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
			Assert::AreEqual(points[2], -points[4], Quad1D::tolerance<float>(), L"GUASS LEGENDRE DYNAMIC VECTOR: expected points", LINE_INFO());
		}

		TEST_METHOD(Gauss_legendre_array_100)
		{
			// Should compute at compile time. Manual text by setting breakpoint in Gausslengendre
			std::array<double, 100> p, w;
			Quad1D::gauss_legendre<100, double>(p, w);
		}
	};
}