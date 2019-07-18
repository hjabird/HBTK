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
		class LinearShapeFunctions;		// With Line2
		class QuadraticShapeFunctions;	// With Line3

		// Shape functions for Triangles
		class LinearTriangle3ShapeFunctions;	// With Triangle3
		class QuadraticTriangle6ShapeFunctions;	// With Triangle6

		// Shape functions for quads
		class BilinearQuad4ShapeFunctions;		// With Quad4
		class SerendipityQuad8ShapeFunctions;	// With Quad8

		// Shape functions for tetrahedrons
		class LinearTetrahedron4ShapeFunctions;	// With Tetrahedron4
		class QuadraticTetrahedron10ShapeFunctions; // With Tetrahedron10

		// Shape functions for hexahedrons.
		class LinearHexahedron8ShapeFunctions;	// With Hexahedron8
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

		class LinearTriangle3ShapeFunctions {
		public:
			constexpr std::array<double, 3> shape_function(double x, double y);
			constexpr std::array<double, 3> shape_function_d0(double x, double y);
			constexpr std::array<double, 3> shape_function_d1(double x, double y);

			constexpr double shape_function_0(double x, double y);
			constexpr double shape_function_1(double x, double y);
			constexpr double shape_function_2(double x, double y);

			constexpr double shape_function_0_d0(double x, double y);
			constexpr double shape_function_1_d0(double x, double y);
			constexpr double shape_function_2_d0(double x, double y);

			constexpr double shape_function_0_d1(double x, double y);
			constexpr double shape_function_1_d1(double x, double y);
			constexpr double shape_function_2_d1(double x, double y);
		};

		class QuadraticTriangle6ShapeFunctions {
		public:
			constexpr std::array<double, 6> shape_function(double x, double y);
			constexpr std::array<double, 6> shape_function_d0(double x, double y);
			constexpr std::array<double, 6> shape_function_d1(double x, double y);

			constexpr double shape_function_0(double x, double y);
			constexpr double shape_function_1(double x, double y);
			constexpr double shape_function_2(double x, double y);
			constexpr double shape_function_3(double x, double y);
			constexpr double shape_function_4(double x, double y);
			constexpr double shape_function_5(double x, double y);

			constexpr double shape_function_0_d0(double x, double y);
			constexpr double shape_function_1_d0(double x, double y);
			constexpr double shape_function_2_d0(double x, double y);
			constexpr double shape_function_3_d0(double x, double y);
			constexpr double shape_function_4_d0(double x, double y);
			constexpr double shape_function_5_d0(double x, double y);

			constexpr double shape_function_0_d1(double x, double y);
			constexpr double shape_function_1_d1(double x, double y);
			constexpr double shape_function_2_d1(double x, double y);
			constexpr double shape_function_3_d1(double x, double y);
			constexpr double shape_function_4_d1(double x, double y);
			constexpr double shape_function_5_d1(double x, double y);
		};

		class BilinearQuad4ShapeFunctions {
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

		class SerendipityQuad8ShapeFunctions {
		public:
			constexpr std::array<double, 8> shape_function(double x, double y);
			constexpr std::array<double, 8> shape_function_d0(double x, double y);
			constexpr std::array<double, 8> shape_function_d1(double x, double y);

			constexpr double shape_function_0(double x, double y);
			constexpr double shape_function_1(double x, double y);
			constexpr double shape_function_2(double x, double y);
			constexpr double shape_function_3(double x, double y);
			constexpr double shape_function_4(double x, double y);
			constexpr double shape_function_5(double x, double y);
			constexpr double shape_function_6(double x, double y);
			constexpr double shape_function_7(double x, double y);

			constexpr double shape_function_0_d0(double x, double y);
			constexpr double shape_function_1_d0(double x, double y);
			constexpr double shape_function_2_d0(double x, double y);
			constexpr double shape_function_3_d0(double x, double y);
			constexpr double shape_function_4_d0(double x, double y);
			constexpr double shape_function_5_d0(double x, double y);
			constexpr double shape_function_6_d0(double x, double y);
			constexpr double shape_function_7_d0(double x, double y);

			constexpr double shape_function_0_d1(double x, double y);
			constexpr double shape_function_1_d1(double x, double y);
			constexpr double shape_function_2_d1(double x, double y);
			constexpr double shape_function_3_d1(double x, double y);
			constexpr double shape_function_4_d1(double x, double y);
			constexpr double shape_function_5_d1(double x, double y);
			constexpr double shape_function_6_d1(double x, double y);
			constexpr double shape_function_7_d1(double x, double y);
		};

		class LinearTetrahedron4ShapeFunctions {
		public:
			constexpr std::array<double, 4> shape_function(double x, double y, double z);
			constexpr std::array<double, 4> shape_function_d0(double x, double y, double z);
			constexpr std::array<double, 4> shape_function_d1(double x, double y, double z);
			constexpr std::array<double, 4> shape_function_d2(double x, double y, double z);

			constexpr double shape_function_0(double x, double y, double z);
			constexpr double shape_function_1(double x, double y, double z);
			constexpr double shape_function_2(double x, double y, double z);
			constexpr double shape_function_3(double x, double y, double z);

			constexpr double shape_function_0_d0(double x, double y, double z);
			constexpr double shape_function_1_d0(double x, double y, double z);
			constexpr double shape_function_2_d0(double x, double y, double z);
			constexpr double shape_function_3_d0(double x, double y, double z);

			constexpr double shape_function_0_d1(double x, double y, double z);
			constexpr double shape_function_1_d1(double x, double y, double z);
			constexpr double shape_function_2_d1(double x, double y, double z);
			constexpr double shape_function_3_d1(double x, double y, double z);

			constexpr double shape_function_0_d2(double x, double y, double z);
			constexpr double shape_function_1_d2(double x, double y, double z);
			constexpr double shape_function_2_d2(double x, double y, double z);
			constexpr double shape_function_3_d2(double x, double y, double z);
		};

		class QuadraticTetrahedron10ShapeFunctions {
		public:
			constexpr std::array<double, 10> shape_function(double x, double y, double z);
			constexpr std::array<double, 10> shape_function_d0(double x, double y, double z);
			constexpr std::array<double, 10> shape_function_d1(double x, double y, double z);
			constexpr std::array<double, 10> shape_function_d2(double x, double y, double z);

			constexpr double shape_function_0(double x, double y, double z);
			constexpr double shape_function_1(double x, double y, double z);
			constexpr double shape_function_2(double x, double y, double z);
			constexpr double shape_function_3(double x, double y, double z);
			constexpr double shape_function_4(double x, double y, double z);
			constexpr double shape_function_5(double x, double y, double z);
			constexpr double shape_function_6(double x, double y, double z);
			constexpr double shape_function_7(double x, double y, double z);
			constexpr double shape_function_8(double x, double y, double z);
			constexpr double shape_function_9(double x, double y, double z);

			constexpr double shape_function_0_d0(double x, double y, double z);
			constexpr double shape_function_1_d0(double x, double y, double z);
			constexpr double shape_function_2_d0(double x, double y, double z);
			constexpr double shape_function_3_d0(double x, double y, double z);
			constexpr double shape_function_4_d0(double x, double y, double z);
			constexpr double shape_function_5_d0(double x, double y, double z);
			constexpr double shape_function_6_d0(double x, double y, double z);
			constexpr double shape_function_7_d0(double x, double y, double z);
			constexpr double shape_function_8_d0(double x, double y, double z);
			constexpr double shape_function_9_d0(double x, double y, double z);

			constexpr double shape_function_0_d1(double x, double y, double z);
			constexpr double shape_function_1_d1(double x, double y, double z);
			constexpr double shape_function_2_d1(double x, double y, double z);
			constexpr double shape_function_3_d1(double x, double y, double z);
			constexpr double shape_function_4_d1(double x, double y, double z);
			constexpr double shape_function_5_d1(double x, double y, double z);
			constexpr double shape_function_6_d1(double x, double y, double z);
			constexpr double shape_function_7_d1(double x, double y, double z);
			constexpr double shape_function_8_d1(double x, double y, double z);
			constexpr double shape_function_9_d1(double x, double y, double z);

			constexpr double shape_function_0_d2(double x, double y, double z);
			constexpr double shape_function_1_d2(double x, double y, double z);
			constexpr double shape_function_2_d2(double x, double y, double z);
			constexpr double shape_function_3_d2(double x, double y, double z);
			constexpr double shape_function_4_d2(double x, double y, double z);
			constexpr double shape_function_5_d2(double x, double y, double z);
			constexpr double shape_function_6_d2(double x, double y, double z);
			constexpr double shape_function_7_d2(double x, double y, double z);
			constexpr double shape_function_8_d2(double x, double y, double z);
			constexpr double shape_function_9_d2(double x, double y, double z);
		};

		class LinearHexahedron8ShapeFunctions {
		public:
			constexpr std::array<double, 8> shape_function(double x, double y, double z);
			constexpr std::array<double, 8> shape_function_d0(double x, double y, double z);
			constexpr std::array<double, 8> shape_function_d1(double x, double y, double z);
			constexpr std::array<double, 8> shape_function_d2(double x, double y, double z);

			constexpr double shape_function_0(double x, double y, double z);
			constexpr double shape_function_1(double x, double y, double z);
			constexpr double shape_function_2(double x, double y, double z);
			constexpr double shape_function_3(double x, double y, double z);
			constexpr double shape_function_4(double x, double y, double z);
			constexpr double shape_function_5(double x, double y, double z);
			constexpr double shape_function_6(double x, double y, double z);
			constexpr double shape_function_7(double x, double y, double z);

			constexpr double shape_function_0_d0(double x, double y, double z);
			constexpr double shape_function_1_d0(double x, double y, double z);
			constexpr double shape_function_2_d0(double x, double y, double z);
			constexpr double shape_function_3_d0(double x, double y, double z);
			constexpr double shape_function_4_d0(double x, double y, double z);
			constexpr double shape_function_5_d0(double x, double y, double z);
			constexpr double shape_function_6_d0(double x, double y, double z);
			constexpr double shape_function_7_d0(double x, double y, double z);

			constexpr double shape_function_0_d1(double x, double y, double z);
			constexpr double shape_function_1_d1(double x, double y, double z);
			constexpr double shape_function_2_d1(double x, double y, double z);
			constexpr double shape_function_3_d1(double x, double y, double z);
			constexpr double shape_function_4_d1(double x, double y, double z);
			constexpr double shape_function_5_d1(double x, double y, double z);
			constexpr double shape_function_6_d1(double x, double y, double z);
			constexpr double shape_function_7_d1(double x, double y, double z);

			constexpr double shape_function_0_d2(double x, double y, double z);
			constexpr double shape_function_1_d2(double x, double y, double z);
			constexpr double shape_function_2_d2(double x, double y, double z);
			constexpr double shape_function_3_d2(double x, double y, double z);
			constexpr double shape_function_4_d2(double x, double y, double z);
			constexpr double shape_function_5_d2(double x, double y, double z);
			constexpr double shape_function_6_d2(double x, double y, double z);
			constexpr double shape_function_7_d2(double x, double y, double z);
		};
	}
}
