#pragma once
/*////////////////////////////////////////////////////////////////////////////
CartesianVector.cpp

Vectors in Cartesian space.

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
	class CartesianPoint3D;	// Include CartesianPoint.h
	class CartesianPoint2D;	// Include CartesianPoint.h

	class CartesianVector3D {
	public:
		CartesianVector3D();
		CartesianVector3D(const std::array<double, 3> vector);
		~CartesianVector3D();

		CartesianVector3D operator+(const CartesianVector3D & other);
		CartesianVector3D operator-(const CartesianVector3D & other);
		CartesianPoint3D operator+(const CartesianPoint3D & other);
		CartesianPoint3D operator-(const CartesianPoint3D & other);
		CartesianVector3D operator*(const double & multiplyer);
		CartesianVector3D operator/(const double & divisor);

		// Returns the length of the vector. Same as: abs(this)
		double length();
		// Set vector length to 1.
		void normalise();
		// Dot product between to vectors.
		double dot(CartesianVector3D & other);
		// Cross product of two vectors
		CartesianVector3D cross(CartesianVector3D & other);
		// The cos of the angle between two vectors.
		double cos_angle(CartesianVector3D & other);
		// The angle between two vectors in radians.
		double angle(CartesianVector3D & other);


		double x;
		double y;
		double z;

		operator std::array<double, 3>();

		bool operator==(const CartesianVector3D & other);
		bool operator!=(const CartesianVector3D & other);
	};

	double abs(CartesianVector3D vector);

	class CartesianVector2D {
	public:
		CartesianVector2D();
		CartesianVector2D(std::array<double, 2> vector);
		~CartesianVector2D();

		CartesianVector2D operator+(CartesianVector2D & other);
		CartesianVector2D operator-(CartesianVector2D & other);
		CartesianPoint2D operator+(CartesianPoint2D & other);
		CartesianPoint2D operator-(CartesianPoint2D & other);
		CartesianVector2D operator*(const double & multiplyer);
		CartesianVector2D operator/(const double & divisor);

		// Returns the length of the vector. Same as: abs(this)
		double length();
		// Set vector length to 1.
		void normalise();
		// Dot product between to vectors.
		double dot(CartesianVector2D & other);
		// Cross product of two vectors
		CartesianVector2D cross();
		// The cos of the angle between two vectors.
		double cos_angle(CartesianVector2D & other);
		// The angle between two vectors in radians.
		double angle(CartesianVector2D & other);


		double x;
		double y;

		operator std::array<double, 2>();
	};

	double abs(CartesianVector2D vector);

} // End namespace HBTK
