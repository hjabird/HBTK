#include "CartesianRectilinearPanel.h"
/*////////////////////////////////////////////////////////////////////////////
CartesianRectilinearPanel.cpp

A rectilinear panel in cartesian space. Like a non-planar quadrilateral. 
Edges are straight.

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

#include <cassert>

#include "ElementShapeFunctions.h"

HBTK::CartesianRectilinearPanel::CartesianRectilinearPanel()
{
}

HBTK::CartesianRectilinearPanel::CartesianRectilinearPanel(const CartesianPoint3D & corner_1, 
	const CartesianPoint3D & corner_2,
	const CartesianPoint3D & corner_3,
	const CartesianPoint3D & corner_4)
	: corners({corner_1, corner_2, corner_3, corner_4})
{
}

HBTK::CartesianRectilinearPanel::~CartesianRectilinearPanel()
{
}

HBTK::CartesianFiniteLine3D HBTK::CartesianRectilinearPanel::edge(int edge_number) const
{
	assert(edge_number >= 0);
	assert(edge_number < 4);
	CartesianFiniteLine3D edge;
	edge.start() = corners[edge_number];
	edge.end() = corners[(edge_number + 1) % 4];
	return CartesianFiniteLine3D();
}

void HBTK::CartesianRectilinearPanel::edge(int edge_number, const CartesianFiniteLine3D & new_value)
{
	assert(edge_number >= 0);
	assert(edge_number < 4);
	corners[edge_number] = new_value.start();
	corners[(edge_number + 1) % 4] = new_value.end();
	return;
}

HBTK::CartesianPoint3D HBTK::CartesianRectilinearPanel::evaluate(double local_x, double local_y) const
{
	class Elements::BilinearQuad4ShapeFunctions quad4;
	double x = local_x;
	double y = local_y;

	std::array<double, 4> c = quad4.shape_function(x, y);

	double x_out = corners[0].x() * c[0] + corners[1].x() * c[1] +
		corners[2].x() * c[2] + corners[3].x() * c[3];
	double y_out = corners[0].y() * c[0] + corners[1].y() * c[1] +
		corners[2].y() * c[2] + corners[3].y() * c[3];
	double z_out = corners[0].z() * c[0] + corners[1].z() * c[1] +
		corners[2].z() * c[2] + corners[3].z() * c[3];

	return CartesianPoint3D({ x_out, y_out, z_out });
}

HBTK::CartesianPoint3D HBTK::CartesianRectilinearPanel::operator()(const CartesianPoint2D & coordinate) const
{
	return evaluate(coordinate.x(), coordinate.y());
}

HBTK::CartesianPoint3D HBTK::CartesianRectilinearPanel::operator()(double local_x, double local_y) const
{
	return evaluate(local_x, local_y);
}

HBTK::CartesianPoint3D HBTK::CartesianRectilinearPanel::evaluate(const CartesianPoint2D & coordinate) const
{
	return evaluate(coordinate.x(), coordinate.y());
}
