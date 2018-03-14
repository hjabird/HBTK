#pragma once
/*////////////////////////////////////////////////////////////////////////////
CartesianPoint.h

Points and vectors in Cartesian space.

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
	class CartesianVector3D;

	class CartesianPoint3D {
	public:
		CartesianPoint3D();
		CartesianPoint3D(const std::array<double, 3> & location);
		~CartesianPoint3D();

		double & x();
		const double & x() const;
		double & y();
		const double & y() const;
		double & z();
		const double & z() const;

		HBTK::CartesianVector3D operator-(const HBTK::CartesianPoint3D & other) const;
		CartesianPoint3D operator+(const HBTK::CartesianVector3D & other) const;
		CartesianPoint3D operator-(const HBTK::CartesianVector3D & other) const;

		static CartesianPoint3D origin();

		bool operator==(const CartesianPoint3D & other) const;
		bool operator!=(const CartesianPoint3D & other) const;

	private:
		std::array<double, 3> m_coord;
	};


	class CartesianPoint2D {
	public:
		CartesianPoint2D();
		CartesianPoint2D(const std::array<double, 2> & location);
		~CartesianPoint2D();

		// Rotate about the origin anticlockwise angle in radians.
		void rotate(double angle);
		// Rotate about another point anticlockwise some angle in rads.
		void rotate(double angle, CartesianPoint2D other);

		double & x();
		const double & x() const;
		double & y();
		const double & y() const;

		static CartesianPoint2D origin();

	private:
		std::array<double, 2> m_coord;
	};
}



