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
	class CartesianLine3D;

	class CartesianPlane {
	public:
		CartesianPlane();
		// Create origin as given. Primary axis is given by primary_dir - origin normalised.
		// Other axis defined with secondary dir positive, normalised and orthogonal to firs dir...
		CartesianPlane(CartesianPoint3D origin, CartesianPoint3D primary_dir, CartesianPoint3D secondary_dir);
		// Define a plane with origin and normal.
		CartesianPlane(CartesianPoint3D origin, CartesianVector3D normal);
		CartesianPlane(CartesianLine3D origin_primary_dir, CartesianPoint3D secondary_dir);
		~CartesianPlane();

		CartesianPoint3D operator()(CartesianPoint2D & plane_point);
		CartesianPoint3D evaluate(CartesianPoint2D & plane_point);

	private:
		CartesianPoint3D m_origin;
		CartesianVector3D m_x_dir;
		CartesianVector3D m_y_dir;
	};
}
