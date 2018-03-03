#include "ElementShapeFunctions.h"
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

constexpr std::array<double, 2> HBTK::Elements::LinearShapeFunctions::shape_function(double x)
{
	return std::array<double, 2>({
		shape_function_0(x),
		shape_function_1(x)
		});
}

constexpr std::array<double, 2> HBTK::Elements::LinearShapeFunctions::shape_function_d0(double x)
{
	return std::array<double, 2>({
		shape_function_0_d0(x),
		shape_function_1_d0(x)
		});
}

constexpr double HBTK::Elements::LinearShapeFunctions::shape_function_0(double x)
{
	return -0.5 * (x - 1.0);
}

constexpr double HBTK::Elements::LinearShapeFunctions::shape_function_1(double x)
{
	return 0.5 * (x + 1.0);
}

constexpr double HBTK::Elements::LinearShapeFunctions::shape_function_0_d0(double x)
{
	return - 0.5;
}

constexpr double HBTK::Elements::LinearShapeFunctions::shape_function_1_d0(double x)
{
	return 0.5;
}

constexpr std::array<double, 3> HBTK::Elements::QuadraticShapeFunctions::shape_function(double x)
{
	return std::array<double, 3>({
		shape_function_0(x),
		shape_function_1(x),
		shape_function_2(x)
		});
}

constexpr std::array<double, 3> HBTK::Elements::QuadraticShapeFunctions::shape_function_d0(double x)
{
	return std::array<double, 3>({
		shape_function_0_d0(x),
		shape_function_1_d0(x),
		shape_function_2_d0(x)
		});
}

constexpr double HBTK::Elements::QuadraticShapeFunctions::shape_function_0(double x)
{
	return 0.5 * x * (x - 1.);
}

constexpr double HBTK::Elements::QuadraticShapeFunctions::shape_function_1(double x)
{
	return 0.5 * x * (x + 1.);
}

constexpr double HBTK::Elements::QuadraticShapeFunctions::shape_function_2(double x)
{
	return -1 * (x - 1) * (x + 1);
}

constexpr double HBTK::Elements::QuadraticShapeFunctions::shape_function_0_d0(double x)
{
	return x - 0.5;
}

constexpr double HBTK::Elements::QuadraticShapeFunctions::shape_function_1_d0(double x)
{
	return x + 0.5;
}

constexpr double HBTK::Elements::QuadraticShapeFunctions::shape_function_2_d0(double x)
{
	return -2 * x;
}

constexpr std::array<double, 4> HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function(double x, double y)
{
	return std::array<double, 4>({
		shape_function_0(x, y),
		shape_function_1(x, y),
		shape_function_2(x, y),
		shape_function_3(x, y),
		});
}

constexpr std::array<double, 4> HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_d0(double x, double y)
{
	return std::array<double, 4>({
		shape_function_0_d0(x, y),
		shape_function_1_d0(x, y),
		shape_function_2_d0(x, y),
		shape_function_3_d0(x, y),
		});
}

constexpr std::array<double, 4> HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_d1(double x, double y)
{
	return std::array<double, 4>({
		shape_function_0_d1(x, y),
		shape_function_1_d1(x, y),
		shape_function_2_d1(x, y),
		shape_function_3_d1(x, y),
		});
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_0(double x, double y)
{
	return 0.25 * (x - 1) * (y - 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_1(double x, double y)
{
	return -0.25 * (x + 1) * (y - 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_2(double x, double y)
{
	return 0.25 * (x + 1) * (y + 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_3(double x, double y)
{
	return -0.25 * (x - 1) * (y + 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_0_d0(double x, double y)
{
	return 0.25 * (y - 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_1_d0(double x, double y)
{
	return -0.25 * (y - 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_2_d0(double x, double y)
{
	return 0.25 * (y + 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_3_d0(double x, double y)
{
	return -0.25 * (y + 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_0_d1(double x, double y)
{
	return 0.25 * (x - 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_1_d1(double x, double y)
{
	return -0.25 * (x + 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_2_d1(double x, double y)
{
	return 0.25 * (x + 1);
}

constexpr double HBTK::Elements::BilinearQuad4ShapeFunctions::shape_function_3_d1(double x, double y)
{
	return - 0.25 * (x - 1);
}

constexpr std::array<double, 8> HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function(double x, double y)
{
	return std::array<double, 8>({
		shape_function_0(x, y),
		shape_function_1(x, y),
		shape_function_2(x, y),
		shape_function_3(x, y),
		shape_function_4(x, y),
		shape_function_5(x, y),
		shape_function_6(x, y),
		shape_function_7(x, y) 
		});
}

constexpr std::array<double, 8> HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_d0(double x, double y)
{
	return std::array<double, 8>({
		shape_function_0_d0(x, y),
		shape_function_1_d0(x, y),
		shape_function_2_d0(x, y),
		shape_function_3_d0(x, y),
		shape_function_4_d0(x, y),
		shape_function_5_d0(x, y),
		shape_function_6_d0(x, y),
		shape_function_7_d0(x, y)
		});
}

constexpr std::array<double, 8> HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_d1(double x, double y)
{
	return std::array<double, 8>({
		shape_function_0_d1(x, y),
		shape_function_1_d1(x, y),
		shape_function_2_d1(x, y),
		shape_function_3_d1(x, y),
		shape_function_4_d1(x, y),
		shape_function_5_d1(x, y),
		shape_function_6_d1(x, y),
		shape_function_7_d1(x, y)
		});
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_0(double x, double y)
{
	return -0.25 * (x - 1.0) * (y - 1.0) * (x + y + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_1(double x, double y)
{
	return 0.25 * (x + 1.0)*(y - 1.0)*(y - x + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_2(double x, double y)
{
	return 0.25 * (x + 1.0) * (y + 1.0) * (x + y - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_3(double x, double y)
{
	return -0.25 * (x - 1.0) * (y + 1.0) * (y - x - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_4(double x, double y)
{
	return 0.5 * (x + 1.0) * (x - 1.0) * (y - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_5(double x, double y)
{
	return - 0.5 * (x + 1.0) * (y - 1.0) * (y + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_6(double x, double y)
{
	return -0.5*(x + 1.0) * (x - 1.0) * (x + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_7(double x, double y)
{
	return 0.5 * (x - 1.0) * (x - 1.0) * (x + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_0_d0(double x, double y)
{
	return -0.25 * (y - 1.0)*((x + y + 1.0) + (x - 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_1_d0(double x, double y)
{
	return 0.25 * (y - 1.0)*((y - x + 1.0) - (x + 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_2_d0(double x, double y)
{
	return 0.25 * (y + 1.0) * ((x + y - 1.0) + (x + 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_3_d0(double x, double y)
{
	return - 0.25 * (y + 1.0) * ((y - x - 1.0) - (x - 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_4_d0(double x, double y)
{
	return x * (y - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_5_d0(double x, double y)
{
	return - 0.50 * (x * x - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_6_d0(double x, double y)
{
	return - x * (y + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_7_d0(double x, double y)
{
	return 0.50 * (y * y - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_0_d1(double x, double y)
{
	return - 0.25 * (x - 1.0) * ((x + y + 1.0) + (y - 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_1_d1(double x, double y)
{
	return 0.25 * (x + 1.0) * ((y - x + 1.0) + (y - 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_2_d1(double x, double y)
{
	return 0.25 * (x + 1.0) * ((x + y - 1.0) + (y + 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_3_d1(double x, double y)
{
	return -0.25 * (x - 1.0) * ((y - x - 1.0) + (y + 1.0));
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_4_d1(double x, double y)
{
	return 0.50 * (x * x - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_5_d1(double x, double y)
{
	return - y * (x + 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_6_d1(double x, double y)
{
	return - 0.50 * (x * x - 1.0);
}

constexpr double HBTK::Elements::SerendipityQuad8ShapeFunctions::shape_function_7_d1(double x, double y)
{
	return y * (x - 1.0);
}

constexpr std::array<double, 3> HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function(double x, double y)
{
	return std::array<double, 3>({
		shape_function_0(x, y),
		shape_function_1(x, y),
		shape_function_2(x, y)
		});
}

constexpr std::array<double, 3> HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_d0(double x, double y)
{
	return std::array<double, 3>({
		shape_function_0_d0(x, y),
		shape_function_1_d0(x, y),
		shape_function_2_d0(x, y)
		});
}

constexpr std::array<double, 3> HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_d1(double x, double y)
{
	return std::array<double, 3>({
		shape_function_0_d1(x, y),
		shape_function_1_d1(x, y),
		shape_function_2_d1(x, y)
		});
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_0(double x, double y)
{
	return - 1.0  *(x + y - 1.0);
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_1(double x, double y)
{
	return x;
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_2(double x, double y)
{
	return y;
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_0_d0(double x, double y)
{
	return -1.0;
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_1_d0(double x, double y)
{
	return 1.0;
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_2_d0(double x, double y)
{
	return 0.0; // Is 0.0
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_0_d1(double x, double y)
{
	return -1.0;
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_1_d1(double x, double y)
{
	return 0.0; // Intentional.
}

constexpr double HBTK::Elements::LinearTriangle3ShapeFunctions::shape_function_2_d1(double x, double y)
{
	return 1.0;
}

constexpr std::array<double, 6> HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function(double x, double y)
{
	return std::array<double, 6>({
		shape_function_0(x, y),
		shape_function_1(x, y),
		shape_function_2(x, y),
		shape_function_3(x, y),
		shape_function_4(x, y),
		shape_function_5(x, y)
		});
}

constexpr std::array<double, 6> HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_d0(double x, double y)
{
	return std::array<double, 6>({
		shape_function_0_d0(x, y),
		shape_function_1_d0(x, y),
		shape_function_2_d0(x, y),
		shape_function_3_d0(x, y),
		shape_function_4_d0(x, y),
		shape_function_5_d0(x, y)
		});
}

constexpr std::array<double, 6> HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_d1(double x, double y)
{
	return std::array<double, 6>({
		shape_function_0_d1(x, y),
		shape_function_1_d1(x, y),
		shape_function_2_d1(x, y),
		shape_function_3_d1(x, y),
		shape_function_4_d1(x, y),
		shape_function_5_d1(x, y)
		});
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_0(double x, double y)
{
	return 2.0 * (x + y - 1.0)*(x + y - 0.5);
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_1(double x, double y)
{
	return 2.0 * x * (x  - 0.5);
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_2(double x, double y)
{
	return 2.0 * y * (y - 0.5);
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_3(double x, double y)
{
	return -4.0 * x * (x + y - 1.0);
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_4(double x, double y)
{
	return 4.0 * x * y;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_5(double x, double y)
{
	return - 4.0 * (x + y - 1.0) * y;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_0_d0(double x, double y)
{
	return 4.0 * (x + y) - 3;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_1_d0(double x, double y)
{
	return 4.0 * x - 1.0;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_2_d0(double x, double y)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_3_d0(double x, double y)
{
	return -4.0 * (2 * x + y - 1.0);
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_4_d0(double x, double y)
{
	return -4.0 * x;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_5_d0(double x, double y)
{
	return -4.0 * y;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_0_d1(double x, double y)
{
	return 4.0 * (x + y) - 3.0;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_1_d1(double x, double y)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_2_d1(double x, double y)
{
	return 4.0 * y - 1.0;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_3_d1(double x, double y)
{
	return -4.0 * x;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_4_d1(double x, double y)
{
	return 4.0 * x;
}

constexpr double HBTK::Elements::QuadraticTriangle6ShapeFunctions::shape_function_5_d1(double x, double y)
{
	return -4.0 * (x + 2.0 * y - 1);
}

constexpr std::array<double, 4> HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function(double x, double y, double z)
{
	return std::array<double, 4>({
		shape_function_0(x, y, z),
		shape_function_1(x, y, z),
		shape_function_2(x, y, z),
		shape_function_3(x, y, z),
		});
}

constexpr std::array<double, 4> HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_d0(double x, double y, double z)
{
	return std::array<double, 4>({
		shape_function_0_d0(x, y, z),
		shape_function_1_d0(x, y, z),
		shape_function_2_d0(x, y, z),
		shape_function_3_d0(x, y, z),
		});
}

constexpr std::array<double, 4> HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_d1(double x, double y, double z)
{
	return std::array<double, 4>({
		shape_function_0_d1(x, y, z),
		shape_function_1_d1(x, y, z),
		shape_function_2_d1(x, y, z),
		shape_function_3_d1(x, y, z),
		});
}

constexpr std::array<double, 4> HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_d2(double x, double y, double z)
{
	return std::array<double, 4>({
		shape_function_0_d2(x, y, z),
		shape_function_1_d2(x, y, z),
		shape_function_2_d2(x, y, z),
		shape_function_3_d2(x, y, z),
		});
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_0(double x, double y, double z)
{
	return 1 - x - y - z;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_1(double x, double y, double z)
{
	return x;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_2(double x, double y, double z)
{
	return y;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_3(double x, double y, double z)
{
	return z;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_0_d0(double x, double y, double z)
{
	return -1.0;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_1_d0(double x, double y, double z)
{
	return 1.0;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_2_d0(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_3_d0(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_0_d1(double x, double y, double z)
{
	return -1.0;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_1_d1(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_2_d1(double x, double y, double z)
{
	return 1.0;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_3_d1(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_0_d2(double x, double y, double z)
{
	return -1.0;
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_1_d2(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_2_d2(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::LinearTetrahedron4ShapeFunctions::shape_function_3_d2(double x, double y, double z)
{
	return 1.0; 
}

constexpr std::array<double, 10> HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function(double x, double y, double z)
{
	return std::array<double, 10>({
		shape_function_0(x, y, z),
		shape_function_1(x, y, z),
		shape_function_2(x, y, z),
		shape_function_3(x, y, z),
		shape_function_4(x, y, z),
		shape_function_5(x, y, z),
		shape_function_6(x, y, z),
		shape_function_7(x, y, z),
		shape_function_8(x, y, z),
		shape_function_9(x, y, z),
		});
}

constexpr std::array<double, 10> HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_d0(double x, double y, double z)
{
	return std::array<double, 10>({
		shape_function_0_d0(x, y, z),
		shape_function_1_d0(x, y, z),
		shape_function_2_d0(x, y, z),
		shape_function_3_d0(x, y, z),
		shape_function_4_d0(x, y, z),
		shape_function_5_d0(x, y, z),
		shape_function_6_d0(x, y, z),
		shape_function_7_d0(x, y, z),
		shape_function_8_d0(x, y, z),
		shape_function_9_d0(x, y, z),
		});
}

constexpr std::array<double, 10> HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_d1(double x, double y, double z)
{
	return std::array<double, 10>({
		shape_function_0_d1(x, y, z),
		shape_function_1_d1(x, y, z),
		shape_function_2_d1(x, y, z),
		shape_function_3_d1(x, y, z),
		shape_function_4_d1(x, y, z),
		shape_function_5_d1(x, y, z),
		shape_function_6_d1(x, y, z),
		shape_function_7_d1(x, y, z),
		shape_function_8_d1(x, y, z),
		shape_function_9_d1(x, y, z),
		});
}

constexpr std::array<double, 10> HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_d2(double x, double y, double z)
{
	return std::array<double, 10>({
		shape_function_0_d2(x, y, z),
		shape_function_1_d2(x, y, z),
		shape_function_2_d2(x, y, z),
		shape_function_3_d2(x, y, z),
		shape_function_4_d2(x, y, z),
		shape_function_5_d2(x, y, z),
		shape_function_6_d2(x, y, z),
		shape_function_7_d2(x, y, z),
		shape_function_8_d2(x, y, z),
		shape_function_9_d2(x, y, z),
		});
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_0(double x, double y, double z)
{
	return 2 * (1 - x - y - z) * (0.5 - x - y - z);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_1(double x, double y, double z)
{
	return 2 * x * (x - 0.5);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_2(double x, double y, double z)
{
	return 2 * y * (y - 0.5);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_3(double x, double y, double z)
{
	return 2 * z * (z - 0.5);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_4(double x, double y, double z)
{
	return (1 - x - y - z) * x * 4;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_5(double x, double y, double z)
{
	return 4 * x * y;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_6(double x, double y, double z)
{
	return 4 * y * (1 - x - y - z);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_7(double x, double y, double z)
{
	return 4 * z * (1 - x - y - z);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_8(double x, double y, double z)
{
	return 4 * z * y;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_9(double x, double y, double z)
{
	return 4 * x * z;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_0_d0(double x, double y, double z)
{
	return - 2 * (0.5 - y - z - 2 * x) ;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_1_d0(double x, double y, double z)
{
	return 4 * x - 1;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_2_d0(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_3_d0(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_4_d0(double x, double y, double z)
{
	return 4 *  (1 - y - z - 2 * x);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_5_d0(double x, double y, double z)
{
	return 4 * y;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_6_d0(double x, double y, double z)
{
	return -4 * y;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_7_d0(double x, double y, double z)
{
	return -4 * z;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_8_d0(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_9_d0(double x, double y, double z)
{
	return 4 * z;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_0_d1(double x, double y, double z)
{
	return -2 * (0.5 - 2 * y - z - x);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_1_d1(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_2_d1(double x, double y, double z)
{
	return 4 * y - 1;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_3_d1(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_4_d1(double x, double y, double z)
{
	return -4 * x;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_5_d1(double x, double y, double z)
{
	return 4 * x;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_6_d1(double x, double y, double z)
{
	return 4 * (1 - x - z - 2 * y);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_7_d1(double x, double y, double z)
{
	return -4 * z;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_8_d1(double x, double y, double z)
{
	return 4 * z;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_9_d1(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_0_d2(double x, double y, double z)
{
	return -2 * (0.5 - y - 2 * z - x);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_1_d2(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_2_d2(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_3_d2(double x, double y, double z)
{
	return 4 * z - 1;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_4_d2(double x, double y, double z)
{
	return -4 * z;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_5_d2(double x, double y, double z)
{
	return 0.0; // Intentional
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_6_d2(double x, double y, double z)
{
	return -4 * y;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_7_d2(double x, double y, double z)
{
	return 4 * (1 - x - y - 2 * z);
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_8_d2(double x, double y, double z)
{
	return 4 * y;
}

constexpr double HBTK::Elements::QuadraticTetrahedron10ShapeFunctions::shape_function_9_d2(double x, double y, double z)
{
	return 4 * x;
}

constexpr std::array<double, 8> HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function(double x, double y, double z)
{
	return std::array<double, 8>({
		shape_function_0(x, y, z),
		shape_function_1(x, y, z),
		shape_function_2(x, y, z),
		shape_function_3(x, y, z),
		shape_function_4(x, y, z),
		shape_function_5(x, y, z),
		shape_function_6(x, y, z),
		shape_function_7(x, y, z)
		});
}

constexpr std::array<double, 8> HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_d0(double x, double y, double z)
{
	return std::array<double, 8>({
		shape_function_0_d0(x, y, z),
		shape_function_1_d0(x, y, z),
		shape_function_2_d0(x, y, z),
		shape_function_3_d0(x, y, z),
		shape_function_4_d0(x, y, z),
		shape_function_5_d0(x, y, z),
		shape_function_6_d0(x, y, z),
		shape_function_7_d0(x, y, z)
		});
}

constexpr std::array<double, 8> HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_d1(double x, double y, double z)
{
	return std::array<double, 8>({
		shape_function_0_d1(x, y, z),
		shape_function_1_d1(x, y, z),
		shape_function_2_d1(x, y, z),
		shape_function_3_d1(x, y, z),
		shape_function_4_d1(x, y, z),
		shape_function_5_d1(x, y, z),
		shape_function_6_d1(x, y, z),
		shape_function_7_d1(x, y, z)
		});
}

constexpr std::array<double, 8> HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_d2(double x, double y, double z)
{
	return std::array<double, 8>({
		shape_function_0_d2(x, y, z),
		shape_function_1_d2(x, y, z),
		shape_function_2_d2(x, y, z),
		shape_function_3_d2(x, y, z),
		shape_function_4_d2(x, y, z),
		shape_function_5_d2(x, y, z),
		shape_function_6_d2(x, y, z),
		shape_function_7_d2(x, y, z)
		});
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_0(double x, double y, double z)
{
	return (x - 1) * (y - 1) * (z - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_1(double x, double y, double z)
{
	return (x + 1) * (y - 1) * (z - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_2(double x, double y, double z)
{
	return (x + 1) * (y + 1) * (z - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_3(double x, double y, double z)
{
	return (x - 1) * (y + 1) * (z - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_4(double x, double y, double z)
{
	return (x - 1) * (y - 1) * (z + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_5(double x, double y, double z)
{
	return (x + 1) * (y - 1) * (z + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_6(double x, double y, double z)
{
	return (x + 1) * (y + 1) * (z + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_7(double x, double y, double z)
{
	return (x - 1) * (y + 1) * (z + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_0_d0(double x, double y, double z)
{
	return (y - 1) * (z - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_1_d0(double x, double y, double z)
{
	return (y - 1) * (z - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_2_d0(double x, double y, double z)
{
	return (y + 1) * (z - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_3_d0(double x, double y, double z)
{
	return (y + 1) * (z - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_4_d0(double x, double y, double z)
{
	return (y - 1) * (z + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_5_d0(double x, double y, double z)
{
	return (y - 1) * (z + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_6_d0(double x, double y, double z)
{
	return (y + 1) * (z + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_7_d0(double x, double y, double z)
{
	return (y + 1) * (z + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_0_d1(double x, double y, double z)
{
	return (x - 1) * (z - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_1_d1(double x, double y, double z)
{
	return (x + 1) * (z - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_2_d1(double x, double y, double z)
{
	return (x + 1) * (z - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_3_d1(double x, double y, double z)
{
	return (x - 1) * (z - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_4_d1(double x, double y, double z)
{
	return (x - 1) * (z + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_5_d1(double x, double y, double z)
{
	return (x + 1) * (z + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_6_d1(double x, double y, double z)
{
	return (x + 1) * (z + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_7_d1(double x, double y, double z)
{
	return (x - 1) * (z + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_0_d2(double x, double y, double z)
{
	return (x - 1) * (y - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_1_d2(double x, double y, double z)
{
	return (x + 1) * (y - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_2_d2(double x, double y, double z)
{
	return (x + 1) * (y + 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_3_d2(double x, double y, double z)
{
	return (x - 1) * (y + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_4_d2(double x, double y, double z)
{
	return (x - 1) * (y - 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_5_d2(double x, double y, double z)
{
	return (x + 1) * (y - 1) / -8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_6_d2(double x, double y, double z)
{
	return (x + 1) * (y + 1) / 8;
}

constexpr double HBTK::Elements::LinearHexahedron8ShapeFunctions::shape_function_7_d2(double x, double y, double z)
{
	return (x - 1) * (y + 1) / -8;
}
