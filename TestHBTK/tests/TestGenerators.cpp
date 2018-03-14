#include "stdafx.h"
#include "CppUnitTest.h"

#include "../HBTK/Generators.h"
#include "../HBTK/Tolerances.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHBTK
{
	TEST_CLASS(Test_GmshParser)
	{
	public:
		TEST_METHOD(Test_linspace)
		{
			auto a = HBTK::linspace(0, 1);
			Assert::AreEqual(100, (int)a.size(), L"Linspace: check default length is 100.", LINE_INFO());
			Assert::AreEqual(0., a[0], L"Linspace: check starts at start.", LINE_INFO());
			Assert::AreEqual(1., a[99], L"Linspace: check ends at expected value,", LINE_INFO());
			Assert::AreEqual(1. / 99, a[16] - a[15], HBTK::tolerance<double>(), L"Check the difference between to elements is as expected", LINE_INFO());
		}

		TEST_METHOD(Test_logspace)
		{
			auto a = HBTK::logspace(0, 2);
			Assert::AreEqual(100, (int)a.size(), L"Logspace: check default length is 100.", LINE_INFO());
			Assert::AreEqual(1., a[0], L"Logspace: check starts at 10^0 == 1.", LINE_INFO());
			Assert::AreEqual(100., a[99], L"Logspace: check ends at expected value,", LINE_INFO());
		}

		TEST_METHOD(Test_geomspace)
		{
			auto a = HBTK::geomspace(1, 1024, 105, 2);
			Assert::AreEqual(105, (int)a.size(), L"Logspace: check default length is 100.", LINE_INFO());
			Assert::AreEqual(1., a[0], L"Logspace: check starts at start == 1", LINE_INFO());
			Assert::AreEqual(1024., a[104], L"Logspace: check ends at expected value,", LINE_INFO());
		}
	};
}