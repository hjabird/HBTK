#pragma once
/*////////////////////////////////////////////////////////////////////////////
CartesianLine.h

A flat plane in Cartesian space.

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
#include "CartesianVector.h"

namespace HBTK {
	class CartesianFiniteLine3D;

	class CartesianPlane {
	public:
		CartesianPlane();
		// Create origin as given. Primary axis is given by primary_dir - origin normalised.
		// Other axis defined with secondary dir positive, normalised and orthogonal to firs dir...
		CartesianPlane(const CartesianPoint3D & origin, const CartesianPoint3D & primary_dir, const CartesianPoint3D & secondary_dir);
		// Define a plane with origin and normal.
		CartesianPlane(const CartesianPoint3D & origin, const CartesianVector3D & normal);
		CartesianPlane(const CartesianFiniteLine3D & origin_primary_dir, const CartesianPoint3D & secondary_dir);
		~CartesianPlane();

		CartesianPoint3D operator()(const CartesianPoint2D & plane_point) const;
		CartesianPoint3D evaluate(const CartesianPoint2D & plane_point) const;

		// Normal is of length 1.
		CartesianVector3D normal() const;
		double distance(const CartesianPoint3D & point_in_space) const;
		CartesianPoint2D projection(const CartesianPoint3D & point_in_space) const;
		CartesianPoint3D closest_point(const CartesianPoint3D & point_in_space) const;
		CartesianPoint3D symmetric_point(const CartesianPoint3D & point) const;

		// Returns the planes origin.
		CartesianPoint3D & origin();
		const CartesianPoint3D & origin() const;
	private:
		CartesianPoint3D m_origin;
		CartesianVector3D m_x_dir;
		CartesianVector3D m_y_dir;
	};
}
