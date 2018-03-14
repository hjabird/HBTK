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
			HBTK::linear_remap(px, wx, -1.0, 1.0, 0.0, 2.0);
			Assert::AreEqual(1.0, px, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(1.0, wx, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
			HBTK::linear_remap(px, wx, 0.0, 2.0, -2.0, 2.0);
			Assert::AreEqual(0.0, px, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(2.0, wx, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());

			px = -1.0;
			wx = 1.0;
			HBTK::linear_remap(px, wx, -1.0, 1.0, 0.0, 2.0);
			Assert::AreEqual(0.0, px, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(1.0, wx, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
			HBTK::linear_remap(px, wx, 0.0, 2.0, -2.0, 2.0);
			Assert::AreEqual(-2.0, px, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
			Assert::AreEqual(2.0, wx, HBTK::tolerance<double>(), L"Linear Remap", LINE_INFO());
		}

		TEST_METHOD(Telles_Quadratic)
		{
			double px, wx;
			px = -1;
			wx = 1;
			HBTK::telles_quadratic_remap(px, wx, 1.);
			Assert::AreEqual(-1.0, px, HBTK::tolerance<double>(), L"Telles2", LINE_INFO());
			Assert::AreEqual(2.0, wx, HBTK::tolerance<double>(), L"Telles2", LINE_INFO());
			px = 1;
			wx = 1;
			HBTK::telles_quadratic_remap(px, wx, 1.);
			Assert::AreEqual(1.0, px, HBTK::tolerance<double>(), L"Telles2", LINE_INFO());
			Assert::AreEqual(0.0, wx, HBTK::tolerance<double>(), L"Telles2", LINE_INFO());
			px = 0;
			wx = 1;
			HBTK::telles_quadratic_remap(px, wx, 1.);
			Assert::AreEqual(0.5, px, L"Telles2", LINE_INFO());
			Assert::AreEqual(1.0, wx, L"Telles2", LINE_INFO());
			px = 0;
			wx = 1;
			HBTK::telles_quadratic_remap(px, wx, -1.);
			Assert::AreEqual(-0.5, px, L"Telles2", LINE_INFO());
			Assert::AreEqual(1.0, wx, L"Telles2", LINE_INFO());
		}

		TEST_METHOD(Telles_Cubic)
		{
			double px, wx;
			px = -1;
			wx = 1;
			HBTK::telles_cubic_remap(px, wx, 1.0);
			Assert::AreEqual(-1.0, px, HBTK::tolerance<double>(), L"Telles3", LINE_INFO());
			Assert::AreEqual(3.0, wx, HBTK::tolerance<double>(), L"Telles3", LINE_INFO());
			px = 1;
			wx = 1;
			HBTK::telles_cubic_remap(px, wx, 1.0);
			Assert::AreEqual(1.0, px, HBTK::tolerance<double>(), L"Telles3", LINE_INFO());
			Assert::AreEqual(0.0, wx, HBTK::tolerance<double>(), L"Telles3", LINE_INFO());
			px = 0;
			wx = 1;
			HBTK::telles_cubic_remap(px, wx, 1.0);
			Assert::AreEqual(0.75, px, L"Telles3", LINE_INFO());
			Assert::AreEqual(0.75, wx, L"Telles3", LINE_INFO());
			px = 0;
			wx = 1;
			HBTK::telles_cubic_remap(px, wx, -1.0);
			Assert::AreEqual(-0.75, px, L"Telles3", LINE_INFO());
			Assert::AreEqual(0.75, wx, L"Telles3", LINE_INFO());
		}

		TEST_METHOD(Sato_remap)
		{
			double px, wx;
			px = -1;
			wx = 1;
			HBTK::sato_remap<3>(px, wx, 1.0);
			Assert::AreEqual(-1.0, px, HBTK::tolerance<double>(), L"Sato", LINE_INFO());
			Assert::AreEqual(3.0, wx, HBTK::tolerance<double>(), L"Sato", LINE_INFO());
			px = 1;
			wx = 1;
			HBTK::sato_remap<3>(px, wx, 1.0);
			Assert::AreEqual(1.0, px, HBTK::tolerance<double>(), L"Sato", LINE_INFO());
			Assert::AreEqual(0.0, wx, HBTK::tolerance<double>(), L"Sato", LINE_INFO());
			px = 0;
			wx = 1;
			HBTK::sato_remap<4>(px, wx, 1.0);
			Assert::AreEqual(0.875, px, L"Sato", LINE_INFO());
			Assert::AreEqual(0.5, wx, L"Sato", LINE_INFO());
			px = 0;
			wx = 1;
			HBTK::sato_remap<4>(px, wx, -1.0);
			Assert::AreEqual(-0.875, px, L"Sato", LINE_INFO());
			Assert::AreEqual(0.5, wx, L"Sato", LINE_INFO());
		}

		TEST_METHOD(Exponential_remap)
		{
			double px, wx;
			px = -1;
			wx = 1;
			HBTK::exponential_remap(px, wx, -3.);
			Assert::AreEqual(-3., px, L"EXPONENTIAL REMAP: satisfies lower limit 1.", LINE_INFO());
			px = -1;
			HBTK::exponential_remap(px, wx, 5.);
			Assert::AreEqual(5., px, L"EXPONENTIAL REMAP: satisfies lower limit 2.", LINE_INFO());
			px = 1;
			HBTK::exponential_remap(px, wx, 2.);
			Assert::AreEqual((double)INFINITY, px, L"EXPONENTIAL REMAP: satisfies upper limit.", LINE_INFO());
			px = -1;
			wx = 1;
			HBTK::exponential_remap(px, wx, 0.);
			Assert::AreEqual(0., px, L"EXPONENTIAL REMAP: satisfies lower limit.", LINE_INFO());
			Assert::AreEqual(0.5, wx, L"EXPONENTIAL REMAP: weight at lower limit.", LINE_INFO());
			px = 1;
			wx = 1;
			HBTK::exponential_remap(px, wx, 0.);
			Assert::AreEqual((double)INFINITY, px, L"EXPONENTIAL REMAP: satisfies lower limit.", LINE_INFO());
			Assert::AreEqual((double)INFINITY, wx, L"EXPONENTIAL REMAP: weight at lower limit.", LINE_INFO());
		}

		TEST_METHOD(doblare_remap)
		{
			double px, wx;
			px = -1;
			wx = 1;
			HBTK::doblare_remap(px, wx, 0.5);
			Assert::AreEqual(-1.0, px, HBTK::tolerance<double>(), L"Doblare - -1 -> -1", LINE_INFO());
			Assert::AreEqual(5., wx, HBTK::tolerance<double>(), L"Doblare weight 1", LINE_INFO());
			px = 1;
			wx = 1;
			HBTK::doblare_remap(px, wx, 0.5);
			Assert::AreEqual(1.0, px, HBTK::tolerance<double>(), L"Doblare", LINE_INFO());
			Assert::AreEqual(1., wx, HBTK::tolerance<double>(), L"Doblare", LINE_INFO());
		}
	};
}