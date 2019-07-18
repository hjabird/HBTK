#pragma once
/*////////////////////////////////////////////////////////////////////////////
CartesianVector.h

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

		CartesianVector3D operator+(const CartesianVector3D & other) const;
		CartesianVector3D & operator+=(const CartesianVector3D & other);
		CartesianVector3D operator-(const CartesianVector3D & other) const;
		CartesianVector3D operator-() const;
		CartesianVector3D & operator-=(const CartesianVector3D & other);
		CartesianPoint3D operator+(const CartesianPoint3D & other) const;
		CartesianVector3D operator*(const double & multiplyer) const;
		CartesianVector3D & operator*=(const double & multiplyer);
		CartesianVector3D operator/(const double & divisor) const;
		CartesianVector3D & operator/=(const double & divisor);

		// Returns the length of the vector. Same as: abs(this)
		double magnitude() const;
		// Set vector length to 1.
		void normalise();
		// Dot product between to vectors.
		double dot(const CartesianVector3D & other) const;
		// Cross product of two vectors
		CartesianVector3D cross(const CartesianVector3D & other) const;
		// The cos of the angle between two vectors.
		double cos_angle(const CartesianVector3D & other) const;
		// The angle between two vectors in radians.
		double angle(const CartesianVector3D & other) const;


		double & x();
		const double & x() const;
		double & y();
		const double & y() const;
		double & z();
		const double & z() const;
		std::array<double, 3> & as_array();
		const std::array<double, 3> & as_array() const;

		operator std::array<double, 3>() const;

		bool operator==(const CartesianVector3D & other) const;
		bool operator!=(const CartesianVector3D & other) const;
	private:
		std::array<double, 3> m_coord;
	};

	double abs(const CartesianVector3D & vector);
	CartesianVector3D operator*(const double lhs, const CartesianVector3D & rhs);

	class CartesianVector2D {
	public:
		CartesianVector2D();
		CartesianVector2D(const std::array<double, 2> & vector);
		~CartesianVector2D();

		CartesianVector2D operator+(const CartesianVector2D & other) const;
		CartesianVector2D& operator+=(const CartesianVector2D & other);
		CartesianVector2D operator-(const CartesianVector2D & other) const;
		CartesianVector2D operator-() const;
		CartesianVector2D& operator-=(const CartesianVector2D & other);
		CartesianPoint2D operator+(const CartesianPoint2D & other) const;
		CartesianVector2D operator*(const double & multiplyer) const;
		CartesianVector2D& operator*=(const double & multiplyer);
		CartesianVector2D operator/(const double & divisor)const ;
		CartesianVector2D& operator/=(const double & divisor);

		// Set vector length to 1.
		void normalise();
		// Rotate clockwise by angle (Radians) - mutating.
		CartesianVector2D & rotate(double angle);
		// Get a vector that is this one rotated clockwise.
		CartesianVector2D rotated(double angle) const;

		// Returns the length of the vector. Same as: abs(this)
		double magnitude() const;
		// Dot product between to vectors.
		double dot(const CartesianVector2D & other) const;
		// Cross product of.. well, its just a single vector.
		CartesianVector2D cross() const;
		// The cos of the angle between two vectors.
		double cos_angle(const CartesianVector2D & other) const;
		// The angle between two vectors in radians.
		double angle(const CartesianVector2D & other) const;

		double & x();
		const double & x() const;
		double & y();
		const double & y() const;
		std::array<double, 2> & as_array();
		const std::array<double, 2> & as_array() const;

		operator std::array<double, 2>() const;

		bool operator==(const CartesianVector2D & other) const;
		bool operator!=(const CartesianVector2D & other) const;

	private:
		std::array<double, 2> m_coord;
	};

	double abs(const CartesianVector2D & vector);
	CartesianVector2D operator*(const double lhs, const CartesianVector2D & rhs);

} // End namespace HBTK
