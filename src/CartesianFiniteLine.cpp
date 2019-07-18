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
#include "Checks.h"

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

HBTK::CartesianPoint3D & HBTK::CartesianFiniteLine3D::start()
{
	return m_start;
}

const HBTK::CartesianPoint3D & HBTK::CartesianFiniteLine3D::start() const
{
	return m_start;
}

HBTK::CartesianPoint3D & HBTK::CartesianFiniteLine3D::end()
{
	return m_end;
}

const HBTK::CartesianPoint3D & HBTK::CartesianFiniteLine3D::end() const
{
	return m_end;
}


HBTK::CartesianVector3D HBTK::CartesianFiniteLine3D::vector() const
{
	return CartesianVector3D(m_end - m_start);
}

HBTK::CartesianPoint3D HBTK::CartesianFiniteLine3D::midpoint() const
{
	return start() + (end() - start()) * 0.5;
}

double HBTK::CartesianFiniteLine3D::magnitude() const
{
	return vector().magnitude();
}

double HBTK::CartesianFiniteLine3D::distance(const CartesianPoint3D & other) const
{
	double denominator = vector().magnitude();
	double numerator = (other - m_start).cross(vector()).magnitude();
	double d_axis = numerator / denominator;
	double d_start = (other - m_start).magnitude();
	double d_end = (other - m_end).magnitude();
	double check_length = sqrt(d_start * d_start - d_axis * d_axis)
		+ sqrt(d_end * d_end - d_axis * d_axis);
	double distance = d_axis;
	if (check_length > magnitude()) {
		distance = (d_start < d_end ? d_start : d_end);
	}
	return distance;
}

double HBTK::CartesianFiniteLine3D::distance(const CartesianFiniteLine3D & other) const 
{
	CartesianVector3D v1(vector());
	CartesianVector3D v2(other.vector());
	v1.normalise();
	v2.normalise();
	double dist;
	// Accounting for finiteness we need to think of the endpoints.
	double d_start = distance(other.start());
	double d_end = distance(other.end());
	if (v1 == v2 || v1 == -v2) {
		// Colinear
		dist = (d_start <= d_end ? d_start : d_end);
	}
	else {
		// If both lines were infinitely long
		double d_axis = std::abs(v1.cross(v2).dot(other.start() - m_start));
		double check_length = sqrt(d_start * d_start - d_axis * d_axis)
			+ sqrt(d_end * d_end - d_axis * d_axis);
		dist = d_axis;
		if (check_length > magnitude()) {
			dist = (d_start < d_end ? d_start : d_end);
		}
	}
	return dist;
}

double HBTK::CartesianFiniteLine3D::intersection(const CartesianPoint3D & other) const
{
	CartesianVector3D vect = other - m_start;
	CartesianVector3D this_v = vector();
	double coeff_1 = vect.x() / this_v.x();
	double coeff_2 = vect.y() / this_v.y();
	double coeff_3 = vect.z() / this_v.z();
	double coeff;
	if (distance(other) > 1e-8)
	{
		coeff = NAN;
	}
	else {
		// we might have division by zeros.
		if (!HBTK::check_finite(coeff_1)) {
			if(!HBTK::check_finite(coeff_2)) coeff = coeff_3;
			else if (!HBTK::check_finite(coeff_3)) coeff = coeff_2;
			else coeff = (coeff_3 + coeff_2) / 2;
		} else if (!HBTK::check_finite(coeff_2)) {
			if (!HBTK::check_finite(coeff_3)) coeff = coeff_1;
			else coeff = (coeff_1 + coeff_3) / 2;
		} else if(!HBTK::check_finite(coeff_3)) coeff = (coeff_1 + coeff_2) / 2;
		else coeff = (coeff_1 + coeff_2 + coeff_3) / 3;
	}
	return coeff;
}

double HBTK::CartesianFiniteLine3D::intersection(const CartesianFiniteLine3D & other) const
{
	CartesianVector3D vect = other.start() - m_start;
	CartesianVector3D m_v = vector();
	CartesianVector3D o_v = other.vector();
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
	double tmp_o_coeff = - m_v.as_array()[i2] * vect.as_array()[i1] + m_v.as_array()[i1] * vect.as_array()[i2];
	double m_coeff = tmp_m_coeff / det;
	double o_coeff = - tmp_o_coeff / det;
	HBTK::CartesianPoint3D o_pnt, m_pnt;
	m_pnt = evaluate(m_coeff);
	o_pnt = other(o_coeff);
	if (abs(o_pnt - m_pnt) > 1e-8) {
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


HBTK::CartesianFiniteLine2D::CartesianFiniteLine2D()
	: m_start({ 0.0, 0.0 }),
	m_end({ 1.0, 0.0 })
{
}

HBTK::CartesianFiniteLine2D::CartesianFiniteLine2D(const CartesianPoint2D & start, const CartesianPoint2D & end)
	: m_start(start),
	m_end(end)
{
}

HBTK::CartesianFiniteLine2D::CartesianFiniteLine2D(const CartesianPoint2D & start, const CartesianVector2D & direction)
	: m_start(start),
	m_end(start + direction)
{
}

HBTK::CartesianFiniteLine2D::CartesianFiniteLine2D(const CartesianVector2D & direction, const CartesianPoint2D & end)
	: m_start(end - direction),
	m_end(end)
{
}

HBTK::CartesianFiniteLine2D::~CartesianFiniteLine2D()
{
}

HBTK::CartesianFiniteLine2D::operator HBTK::CartesianLine2D() const
{
	return CartesianLine2D(m_start, m_end - m_start);
}

HBTK::CartesianPoint2D HBTK::CartesianFiniteLine2D::operator()(double position) const
{
	CartesianVector2D vector = m_end - m_start;
	CartesianPoint2D output = m_start + vector * position;
	return output;
}

HBTK::CartesianPoint2D HBTK::CartesianFiniteLine2D::evaluate(double position) const
{
	return operator()(position);
}

HBTK::CartesianPoint2D & HBTK::CartesianFiniteLine2D::start()
{
	return m_start;
}

const HBTK::CartesianPoint2D & HBTK::CartesianFiniteLine2D::start() const
{
	return m_start;
}

HBTK::CartesianPoint2D & HBTK::CartesianFiniteLine2D::end()
{
	return m_end;
}

const HBTK::CartesianPoint2D & HBTK::CartesianFiniteLine2D::end() const
{
	return m_end;
}


HBTK::CartesianVector2D HBTK::CartesianFiniteLine2D::vector() const
{
	return CartesianVector2D(m_end - m_start);
}

HBTK::CartesianPoint2D HBTK::CartesianFiniteLine2D::midpoint() const
{
	return start() + (end() - start()) * 0.5;
}


double HBTK::CartesianFiniteLine2D::magnitude() const
{
	return vector().magnitude();
}

bool HBTK::CartesianFiniteLine2D::operator==(const CartesianFiniteLine2D & other) const
{
	return (other.start() == m_start) && (other.end() == m_end);
}

bool HBTK::CartesianFiniteLine2D::operator!=(const CartesianFiniteLine2D & other) const
{
	return !operator==(other);
}
