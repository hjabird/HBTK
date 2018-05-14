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

#include "Checks.h"

HBTK::CartesianLine3D::CartesianLine3D()
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

double HBTK::CartesianLine3D::distance(const CartesianPoint3D & other) const
{
	double denominator = m_direction.magnitude();
	double numerator = (other - m_origin).cross(m_direction).magnitude();
	double distance = numerator / denominator;
	return distance;
}

double HBTK::CartesianLine3D::distance(const CartesianLine3D & other) const
{
	CartesianVector3D v1(m_direction);
	CartesianVector3D v2(other.m_direction);
	v1.normalise();
	v2.normalise();
	double dist;

	if (v1 == v2 || v1 == -v2) {
		// Colinear
		dist = distance(other.m_origin);
	}
	else {
		dist = std::abs(v1.cross(v2).dot(other.m_origin - m_origin));
	}
	return dist;
}

double HBTK::CartesianLine3D::intersection(const CartesianPoint3D & other) const
{
	CartesianVector3D vect = other - m_origin;
	double coeff_1 = vect.x() / m_direction.x();
	double coeff_2 = vect.y() / m_direction.y();
	double coeff_3 = vect.z() / m_direction.z();
	double coeff;
	if (distance(other) > 1e-8)
	{
		coeff = NAN;
	}
	else {
		// we might have division by zeros.
		if (!HBTK::check_finite(coeff_1)) {
			if (!HBTK::check_finite(coeff_2)) coeff = coeff_3;
			else if (!HBTK::check_finite(coeff_3)) coeff = coeff_2;
			else coeff = (coeff_3 + coeff_2) / 2;
		}
		else if (!HBTK::check_finite(coeff_2)) {
			if (!HBTK::check_finite(coeff_3)) coeff = coeff_1;
			else coeff = (coeff_1 + coeff_3) / 2;
		}
		else if (!HBTK::check_finite(coeff_3)) coeff = (coeff_1 + coeff_2) / 2;
		else coeff = (coeff_1 + coeff_2 + coeff_3) / 3;
	}
	return coeff;
}

double HBTK::CartesianLine3D::intersection(const CartesianLine3D & other) const
{
	CartesianVector3D vect = other.m_origin - m_origin;
	const CartesianVector3D & m_v = m_direction;
	const CartesianVector3D & o_v = other.m_direction;
	// Solve as a 2 x 2 linear problem in x, y, then check with z:
	int i1 = -1, i2 = 0;
	double det;
	do {
		i1++;
		i2++;
		det = m_v.as_array()[i1] * o_v.as_array()[i2]
			- m_v.as_array()[i2] * o_v.as_array()[i1];
		if (i2 == 3) throw std::invalid_argument(
			"HBTK::intersection of finite lines in 3D: "
			"It was not possible to invert the linear system to determine "
			"the intersection. Are you sure the lines aren't collinear? "
			__FILE__ ":" + std::to_string(__LINE__)
		);
	} while (det == 0);
	double tmp_m_coeff = o_v.as_array()[i2] * vect.as_array()[i1] - o_v.as_array()[i1] * vect.as_array()[i2];
	double tmp_o_coeff = -m_v.as_array()[i2] * vect.as_array()[i1] + m_v.as_array()[i1] * vect.as_array()[i2];
	double m_coeff = tmp_m_coeff / det;
	double o_coeff = -tmp_o_coeff / det;
	HBTK::CartesianPoint3D o_pnt, m_pnt;
	m_pnt = evaluate(m_coeff);
	o_pnt = other(o_coeff);
	if (abs(o_pnt - m_pnt) > 1e-8) {
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
