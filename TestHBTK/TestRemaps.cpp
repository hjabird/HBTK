#include "stdafx.h"
#include "CppUnitTest.h"

#include "../HBTK/Remaps.h"
#include "../HBTK/Tolerances.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHBTK
{
	TEST_CLASS(Test_Remaps)
	{
	public:

		TEST_METHOD(Linear_Remap)
		{
			// Debuggin can be problematic due to compiling the solution.
			double px, wx;
			px = 0.0;
			wx = 1.0;
			Quad::linear_remap(px, wx, -1.0, 1.0, 0.0, 2.0);
			Assert::AreEqual(1.0, px, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(1.0, wx, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Quad::linear_remap(px, wx, 0.0, 2.0, -2.0, 2.0);
			Assert::AreEqual(0.0, px, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(2.0, wx, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());

			px = -1.0;
			wx = 1.0;
			Quad::linear_remap(px, wx, -1.0, 1.0, 0.0, 2.0);
			Assert::AreEqual(0.0, px, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(1.0, wx, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Quad::linear_remap(px, wx, 0.0, 2.0, -2.0, 2.0);
			Assert::AreEqual(-2.0, px, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(2.0, wx, Quad::tolerance<double>(), L"Linear Remap", LINE_INFO());
		}

		TEST_METHOD(Telles_Quadratic)
		{
			double px, wx;
			px = -1;
			wx = 1;
			Quad::telles_quadratic_remap(px, wx, 1.);
			Assert::AreEqual(-1.0, px, Quad::tolerance<double>(), L"Telles2", LINE_INFO());
			Assert::AreEqual(2.0, wx, Quad::tolerance<double>(), L"Telles2", LINE_INFO());
			px = 1;
			wx = 1;
			Quad::telles_quadratic_remap(px, wx, 1.);
			Assert::AreEqual(1.0, px, Quad::tolerance<double>(), L"Telles2", LINE_INFO());
			Assert::AreEqual(0.0, wx, Quad::tolerance<double>(), L"Telles2", LINE_INFO());
			px = 0;
			wx = 1;
			Quad::telles_quadratic_remap(px, wx, 1.);
			Assert::AreEqual(0.5, px, L"Telles2", LINE_INFO());
			Assert::AreEqual(1.0, wx, L"Telles2", LINE_INFO());
			px = 0;
			wx = 1;
			Quad::telles_quadratic_remap(px, wx, -1.);
			Assert::AreEqual(-0.5, px, L"Telles2", LINE_INFO());
			Assert::AreEqual(1.0, wx, L"Telles2", LINE_INFO());
		}

		TEST_METHOD(Telles_Cubic)
		{
			double px, wx;
			px = -1;
			wx = 1;
			Quad::telles_cubic_remap(px, wx, 1.0);
			Assert::AreEqual(-1.0, px, Quad::tolerance<double>(), L"Telles3", LINE_INFO());
			Assert::AreEqual(3.0, wx, Quad::tolerance<double>(), L"Telles3", LINE_INFO());
			px = 1;
			wx = 1;
			Quad::telles_cubic_remap(px, wx, 1.0);
			Assert::AreEqual(1.0, px, Quad::tolerance<double>(), L"Telles3", LINE_INFO());
			Assert::AreEqual(0.0, wx, Quad::tolerance<double>(), L"Telles3", LINE_INFO());
			px = 0;
			wx = 1;
			Quad::telles_cubic_remap(px, wx, 1.0);
			Assert::AreEqual(0.75, px, L"Telles3", LINE_INFO());
			Assert::AreEqual(0.75, wx, L"Telles3", LINE_INFO());
			px = 0;
			wx = 1;
			Quad::telles_cubic_remap(px, wx, -1.0);
			Assert::AreEqual(-0.75, px, L"Telles3", LINE_INFO());
			Assert::AreEqual(0.75, wx, L"Telles3", LINE_INFO());
		}

		TEST_METHOD(Sato_remap)
		{
			double px, wx;
			px = -1;
			wx = 1;
			Quad::sato_remap<3>(px, wx, 1.0);
			Assert::AreEqual(-1.0, px, Quad::tolerance<double>(), L"Sato", LINE_INFO());
			Assert::AreEqual(3.0, wx, Quad::tolerance<double>(), L"Sato", LINE_INFO());
			px = 1;
			wx = 1;
			Quad::sato_remap<3>(px, wx, 1.0);
			Assert::AreEqual(1.0, px, Quad::tolerance<double>(), L"Sato", LINE_INFO());
			Assert::AreEqual(0.0, wx, Quad::tolerance<double>(), L"Sato", LINE_INFO());
			px = 0;
			wx = 1;
			Quad::sato_remap<4>(px, wx, 1.0);
			Assert::AreEqual(0.875, px, L"Sato", LINE_INFO());
			Assert::AreEqual(0.5, wx, L"Sato", LINE_INFO());
			px = 0;
			wx = 1;
			Quad::sato_remap<4>(px, wx, -1.0);
			Assert::AreEqual(-0.875, px, L"Sato", LINE_INFO());
			Assert::AreEqual(0.5, wx, L"Sato", LINE_INFO());
		}
	};
}