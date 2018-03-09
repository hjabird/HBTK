#include "CartesianFiniteLine.h"
/*////////////////////////////////////////////////////////////////////////////
CartesianFiniteLine.cpp

A straight finite line in Cartesian space.

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
#include "CartesianLine.h"
#include "CartesianVector.h"

HBTK::CartesianFiniteLine3D::CartesianFiniteLine3D()
	: m_start({0.0, 0.0, 0.0}),
	m_end({1.0, 0.0, 0.0})
{
}

HBTK::CartesianFiniteLine3D::CartesianFiniteLine3D(const CartesianPoint3D & start, const CartesianPoint3D & end)
	: m_start(start),
	m_end(end)
{
}

HBTK::CartesianFiniteLine3D::CartesianFiniteLine3D(const CartesianPoint3D & start, const CartesianVector3D & direction)
	: m_start(start),
	m_end(start + direction)
{
}

HBTK::CartesianFiniteLine3D::CartesianFiniteLine3D(const CartesianVector3D & direction, const CartesianPoint3D & end)
	: m_start(end - direction),
	m_end(end)
{
}

HBTK::CartesianFiniteLine3D::~CartesianFiniteLine3D()
{
}

HBTK::CartesianFiniteLine3D::operator HBTK::CartesianLine3D() const
{
	return CartesianLine3D(m_start, m_end - m_start);
}

HBTK::CartesianPoint3D HBTK::CartesianFiniteLine3D::operator()(double position) const
{
	CartesianVector3D vector = m_end - m_start;
	CartesianPoint3D output = m_start + vector * position;
	return output;
}

HBTK::CartesianPoint3D HBTK::CartesianFiniteLine3D::evaluate(double position) const
{
	return operator()(position);
}


HBTK::CartesianVector3D HBTK::CartesianFiniteLine3D::vector() const
{
	return CartesianVector3D(m_end - m_start);
}

double HBTK::CartesianFiniteLine3D::distance(const CartesianPoint3D & other)
{
	double denominator = vector().length();
	double numerator = (other - m_start).cross(vector()).length();
	return numerator / denominator;
}

double HBTK::CartesianFiniteLine3D::distance(const CartesianFiniteLine3D & other)
{
	CartesianVector3D normal = vector().cross(other.vector());
	return std::abs(normal.dot(other.start() - m_start));
}

double HBTK::CartesianFiniteLine3D::intersection(const CartesianPoint3D & other) const
{
	CartesianVector3D vect = other - m_start;
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

double HBTK::CartesianFiniteLine3D::intersection(const CartesianFiniteLine3D & other) const
{
	CartesianVector3D vect = other.start() - m_start;
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

bool HBTK::CartesianFiniteLine3D::operator==(const CartesianFiniteLine3D & other) const
{
	return (other.start() == m_start) && (other.end() == m_end);
}

bool HBTK::CartesianFiniteLine3D::operator!=(const CartesianFiniteLine3D & other) const
{
	return !operator==(other);
}
