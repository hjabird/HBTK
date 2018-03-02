#pragma once
/*////////////////////////////////////////////////////////////////////////////
ElementShapeFunctions.h

Shape functions for elements described in ElementNodes.h and
ElementGeometry.h. INCOMPLETE.

Copyright 2018 HJA Bird

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/////////////////////////////////////////////////////////////////////////////

#include <array>

namespace HBTK {
	
	/*
	A set of shape functions goes with an element from ElementNodes.h.
	For an element of i nodes and j dimensions the SFs are written as:

	class <Function type>ShapeFunctions:
		constexpr double shape_function_0(double x, ..)
		...
		constexpr double shape_function_i(double x, ..)

		// And derivatives:
		constexpr double shape_function_0_d0(double x, ..)
		...
		constexpr double shape_function_i_d0(double x, ..)

		...

		constexpr double shape_function_0_dj(double x, ..)
		...
		constexpr double shape_function_i_dj(double x, ..)
	*/



	namespace Elements {
		// No shape functions needed for point.

		// Shape functions in 1d.
		class LinearShapeFunctions;
		class QuadraticShapeFunctions;

		// Shape functions for quads
		class BilinearShapeFunctions;
	}

	namespace Elements {
		class LinearShapeFunctions {
		public:
			constexpr std::array<double, 2> shape_function(double x);
			constexpr std::array<double, 2> shape_function_d0(double x);

			constexpr double shape_function_0(double x);
			constexpr double shape_function_1(double x);

			constexpr double shape_function_0_d0(double x);
			constexpr double shape_function_1_d0(double x);
		};

		class QuadraticShapeFunctions {
		public:
			constexpr std::array<double, 3> shape_function(double x);
			constexpr std::array<double, 3> shape_function_d0(double x);

			constexpr double shape_function_0(double x);
			constexpr double shape_function_1(double x);
			constexpr double shape_function_2(double x);

			constexpr double shape_function_0_d0(double x);
			constexpr double shape_function_1_d0(double x);
			constexpr double shape_function_2_d0(double x);
		};

		class BilinearShapeFunctions {
		public:
			constexpr std::array<double, 4> shape_function(double x, double y);
			constexpr std::array<double, 4> shape_function_d0(double x, double y);
			constexpr std::array<double, 4> shape_function_d1(double x, double y);

			constexpr double shape_function_0(double x, double y);
			constexpr double shape_function_1(double x, double y);
			constexpr double shape_function_2(double x, double y);
			constexpr double shape_function_3(double x, double y);

			constexpr double shape_function_0_d0(double x, double y);
			constexpr double shape_function_1_d0(double x, double y);
			constexpr double shape_function_2_d0(double x, double y);
			constexpr double shape_function_3_d0(double x, double y);

			constexpr double shape_function_0_d1(double x, double y);
			constexpr double shape_function_1_d1(double x, double y);
			constexpr double shape_function_2_d1(double x, double y);
			constexpr double shape_function_3_d1(double x, double y);
		};
	}
}
