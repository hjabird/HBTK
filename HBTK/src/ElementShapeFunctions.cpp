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

constexpr std::array<double, 4> HBTK::Elements::BilinearShapeFunctions::shape_function(double x, double y)
{
	return std::array<double, 4>({
		shape_function_0(x, y),
		shape_function_1(x, y),
		shape_function_2(x, y),
		shape_function_3(x, y),
		});
}

constexpr std::array<double, 4> HBTK::Elements::BilinearShapeFunctions::shape_function_d0(double x, double y)
{
	return std::array<double, 4>({
		shape_function_0_d0(x, y),
		shape_function_1_d0(x, y),
		shape_function_2_d0(x, y),
		shape_function_3_d0(x, y),
		});
}

constexpr std::array<double, 4> HBTK::Elements::BilinearShapeFunctions::shape_function_d1(double x, double y)
{
	return std::array<double, 4>({
		shape_function_0_d1(x, y),
		shape_function_1_d1(x, y),
		shape_function_2_d1(x, y),
		shape_function_3_d1(x, y),
		});
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_0(double x, double y)
{
	return 0.25 * (x - 1) * (y - 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_1(double x, double y)
{
	return -0.25 * (x + 1) * (y - 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_2(double x, double y)
{
	return 0.25 * (x + 1) * (y + 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_3(double x, double y)
{
	return -0.25 * (x - 1) * (y + 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_0_d0(double x, double y)
{
	return 0.25 * (y - 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_1_d0(double x, double y)
{
	return -0.25 * (y - 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_2_d0(double x, double y)
{
	return 0.25 * (y + 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_3_d0(double x, double y)
{
	return -0.25 * (y + 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_0_d1(double x, double y)
{
	return 0.25 * (x - 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_1_d1(double x, double y)
{
	return -0.25 * (x + 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_2_d1(double x, double y)
{
	return 0.25 * (x + 1);
}

constexpr double HBTK::Elements::BilinearShapeFunctions::shape_function_3_d1(double x, double y)
{
	return - 0.25 * (x - 1);
}
