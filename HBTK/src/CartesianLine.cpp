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

HBTK::CartesianLine3D::CartesianLine3D()
	: m_origin({ 0.0, 0.0, 0.0 }),
	m_direction({ 1.0  })
{
}

HBTK::CartesianLine3D::CartesianLine3D(const CartesianPoint3D & start, const CartesianPoint3D & end)
	: m_origin(start),
	m_direction(end - start)
{
}

HBTK::CartesianLine3D::CartesianLine3D(const CartesianPoint3D & start, const CartesianVector3D & direction)
	: m_origin(start),
	m_direction(direction)
{
}

HBTK::CartesianLine3D::~CartesianLine3D()
{
}

HBTK::CartesianPoint3D HBTK::CartesianLine3D::operator()(double position) const
{
	CartesianPoint3D output = m_origin + m_direction * position;
	return output;
}

HBTK::CartesianPoint3D HBTK::CartesianLine3D::evaluate(double position) const
{
	return operator()(position);
}

HBTK::CartesianPoint3D & HBTK::CartesianLine3D::origin()
{
	return m_origin;
}

const HBTK::CartesianPoint3D & HBTK::CartesianLine3D::origin() const
{
	return m_origin;
}

HBTK::CartesianVector3D & HBTK::CartesianLine3D::direction()
{
	return m_direction;
}

const HBTK::CartesianVector3D & HBTK::CartesianLine3D::direction() const
{
	return m_direction;
}

double HBTK::CartesianLine3D::distance(const CartesianPoint3D & other)
{
	double denominator = m_direction.length();
	double numerator = (other - m_origin).cross(m_direction).length();
	return numerator / denominator;
}

double HBTK::CartesianLine3D::distance(const CartesianLine3D & other)
{
	CartesianVector3D normal = m_direction.cross(other.direction());
	return std::abs(normal.dot(other.origin() - m_origin));
}

double HBTK::CartesianLine3D::intersection(const CartesianPoint3D & other) const
{
	CartesianVector3D vect = other - m_origin;
	double coeff_1 = vect.x / m_direction.x;
	double coeff_2 = vect.y / m_direction.y;
	double coeff_3 = vect.z / m_direction.z;
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
	CartesianVector3D vect = other.origin() - m_origin;
	CartesianVector3D m_v = m_direction;
	CartesianVector3D o_v = other.direction();
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

bool HBTK::CartesianLine3D::operator==(const CartesianLine3D & other) const
{
	return (other.origin() == m_origin) && (other.direction() == m_direction);
}

bool HBTK::CartesianLine3D::operator!=(const CartesianLine3D & other) const
{
	return !operator==(other);
}

HBTK::CartesianLine2D::CartesianLine2D()
	: m_origin({ 0.0, 0.0}),
	m_direction({ 1.0 })
{
}

HBTK::CartesianLine2D::CartesianLine2D(const CartesianPoint2D & start, const CartesianPoint2D & end)
	: m_origin(start),
	m_direction(end - start)
{
}

HBTK::CartesianLine2D::CartesianLine2D(const CartesianPoint2D & start, const CartesianVector2D & direction)
	: m_origin(start),
	m_direction(direction)
{
}

HBTK::CartesianLine2D::~CartesianLine2D()
{
}

HBTK::CartesianPoint2D HBTK::CartesianLine2D::operator()(double position) const
{
	CartesianPoint2D output = m_origin + m_direction * position;
	return output;
}

HBTK::CartesianPoint2D HBTK::CartesianLine2D::evaluate(double position) const
{
	return operator()(position);
}

HBTK::CartesianPoint2D & HBTK::CartesianLine2D::origin()
{
	return m_origin;
}

const HBTK::CartesianPoint2D & HBTK::CartesianLine2D::origin() const
{
	return m_origin;
}

HBTK::CartesianVector2D & HBTK::CartesianLine2D::direction()
{
	return m_direction;
}

const HBTK::CartesianVector2D & HBTK::CartesianLine2D::direction() const
{
	return m_direction;
}


bool HBTK::CartesianLine2D::operator==(const CartesianLine2D & other) const
{
	return (other.origin() == m_origin) && (other.direction() == m_direction);
}

bool HBTK::CartesianLine2D::operator!=(const CartesianLine2D & other) const
{
	return !operator==(other);
}
