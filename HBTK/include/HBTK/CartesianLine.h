#pragma once
/*////////////////////////////////////////////////////////////////////////////
CartesianLine.h

A straight line in Cartesian space.

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

#include "CartesianPoint.h"

namespace HBTK {
	class CartesianVector3D;

	class CartesianLine3D {
	public:
		CartesianLine3D();
		CartesianLine3D(const CartesianPoint3D & start, const CartesianPoint3D & end);
		CartesianLine3D(const CartesianPoint3D & start, const CartesianVector3D & direction);
		CartesianLine3D(const CartesianVector3D & direction, const CartesianPoint3D & end);
		~CartesianLine3D();

		// Get a point on the line. Position in 0, 1 -> start to end.
		CartesianPoint3D operator()(double position) const;
		CartesianPoint3D evaluate(double position) const;

		CartesianPoint3D start;
		CartesianPoint3D end;
		// Returns a vector of direction and length of the line:
		CartesianVector3D vector() const;

		// Distance between this line and a point.
		double distance(const CartesianPoint3D & other);
		double distance(const CartesianLine3D & other);

		// Intersection - returns double corresponding to position between
		// start and end of line as 0-1.
		double intersection(const CartesianPoint3D & other) const;
		double intersection(const CartesianLine3D & other) const;
	};
}

