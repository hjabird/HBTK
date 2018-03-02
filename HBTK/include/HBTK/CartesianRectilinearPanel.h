#pragma once
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

#include <array>

#include "CartesianPoint.h"
#include "CartesianFiniteLine.h"

namespace HBTK {
	class CartesianRectilinearPanel {
	public:
		CartesianRectilinearPanel();
		CartesianRectilinearPanel(const CartesianPoint3D & corner_1, const CartesianPoint3D & corner_2,
			const CartesianPoint3D & corner_3, const CartesianPoint3D & corner_4);
		~CartesianRectilinearPanel();

		// Corners go anticlockwise round the panel from "bottom right". 0-4
		std::array<CartesianPoint3D, 4> corners;
		// Edges start on the bottom and go round.
		CartesianFiniteLine3D edge(int edge_number) const;
		void edge(int edge_number, const CartesianFiniteLine3D & new_value);

		// The panel's local coordinates are [-1, 1], [-1, 1]
		CartesianPoint3D operator()(const CartesianPoint2D & coordinate) const;\
		CartesianPoint3D operator()(double local_x, double local_y) const;
		CartesianPoint3D evaluate(const CartesianPoint2D & coordinate) const;
		CartesianPoint3D evaluate(double local_x, double local_y) const;
	
	};

}
