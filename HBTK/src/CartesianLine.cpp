#include "CartesianLine.h"
/*////////////////////////////////////////////////////////////////////////////
CartesianLine.cpp

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

#include <cmath>

#include "CartesianPoint.h"
#include "CartesianVector.h"

HBTK::CartesianLine3D::CartesianLine3D()
	: start({0.0, 0.0, 0.0}),
	end({1.0, 0.0, 0.0})
{
}

HBTK::CartesianLine3D::CartesianLine3D(const CartesianPoint3D & start, const CartesianPoint3D & end)
	: start(start),
	end(end)
{
}

HBTK::CartesianLine3D::CartesianLine3D(const CartesianPoint3D & start, const CartesianVector3D & direction)
	: start(start),
	end(start + direction)
{
}

HBTK::CartesianLine3D::CartesianLine3D(const CartesianVector3D & direction, const CartesianPoint3D & end)
	: start(end - direction),
	end(end)
{
}

HBTK::CartesianLine3D::~CartesianLine3D()
{
}

HBTK::CartesianPoint3D HBTK::CartesianLine3D::operator()(double position) const
{
	CartesianVector3D vector = end - start;
	CartesianPoint3D output = start + vector * position;
	return output;
}

HBTK::CartesianPoint3D HBTK::CartesianLine3D::evaluate(double position) const
{
	return operator()(position);
}


HBTK::CartesianVector3D HBTK::CartesianLine3D::vector() const
{
	return CartesianVector3D(end - start);
}

double HBTK::CartesianLine3D::distance(const CartesianPoint3D & other)
{
	double denominator = vector().length();
	double numerator = (other - start).cross(vector()).length();
	return numerator / denominator;
}

double HBTK::CartesianLine3D::distance(const CartesianLine3D & other)
{
	CartesianVector3D normal = vector().cross(other.vector());
	return std::abs(normal.dot(other.start - start));
}

double HBTK::CartesianLine3D::intersection(const CartesianPoint3D & other) const
{
	CartesianVector3D vect = other - start;
	double coeff_1 = vect.x / vector().x;
	double coeff_2 = vect.y / vector().y;
	double coeff_3 = vect.z / vector().z;
	double coeff;
	if ((std::abs(coeff_1 - coeff_2) > 1e-8) || (std::abs(coeff_2 - coeff_3) > 1e-8)) {
		coeff = NAN;
	}
	else {
		coeff = coeff_1;
	}
	return coeff_1;
}

double HBTK::CartesianLine3D::intersection(const CartesianLine3D & other) const
{
	CartesianVector3D vect = other.start - start;
	CartesianVector3D m_v = vector();
	CartesianVector3D o_v = other.vector();
	// Solve as a 2 x 2 linear problem in x, y, then check with z:
	double det = m_v.x * o_v.y - m_v.y * o_v.x;
	double tmp_m_coeff = o_v.y * vect.x - o_v.x * vect.y;
	double tmp_o_coeff = -m_v.y * vect.x + m_v.x * vect.y;
	double m_coeff = det * tmp_m_coeff;
	double o_coeff = det * tmp_o_coeff;
	if (abs(other(o_coeff) - evaluate(m_coeff)) < 1e-8) {
		m_coeff = NAN;
	}
	return m_coeff;
}
