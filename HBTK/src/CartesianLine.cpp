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
	: m_start({0.0, 0.0, 0.0}),
	m_end({1.0, 0.0, 0.0})
{
}

HBTK::CartesianLine3D::CartesianLine3D(CartesianPoint3D start, CartesianPoint3D end)
	: m_start(start),
	m_end(end)
{
}

HBTK::CartesianLine3D::CartesianLine3D(CartesianPoint3D start, CartesianVector3D direction)
	: m_start(start),
	m_end(start + direction)
{
}

HBTK::CartesianLine3D::CartesianLine3D(CartesianVector3D direction, CartesianPoint3D end)
	: m_start(end - direction),
	m_end(end)
{
}

HBTK::CartesianLine3D::~CartesianLine3D()
{
}

HBTK::CartesianPoint3D HBTK::CartesianLine3D::operator()(double position)
{
	CartesianVector3D vector = m_end - m_start;
	CartesianPoint3D output = m_start + vector * position;
	return output;
}

HBTK::CartesianPoint3D HBTK::CartesianLine3D::evaluate(double position)
{
	return operator()(position);
}

HBTK::CartesianPoint3D & HBTK::CartesianLine3D::start()
{
	return m_start;
}

HBTK::CartesianPoint3D & HBTK::CartesianLine3D::end()
{
	return m_end;
}

HBTK::CartesianVector3D HBTK::CartesianLine3D::vector()
{
	return CartesianVector3D(m_end - m_start);
}

double HBTK::CartesianLine3D::distance(CartesianPoint3D & other)
{
	double denominator = vector().length();
	double numerator = (other - m_start).cross(vector()).length();
	return numerator / denominator;
}

double HBTK::CartesianLine3D::distance(CartesianLine3D & other)
{
	CartesianVector3D normal = vector().cross(other.vector());
	return std::abs(normal.dot(other.start() - m_start));
}

double HBTK::CartesianLine3D::intesection(CartesianPoint3D & other)
{
	CartesianVector3D vect = other - m_start;
	double coeff_1 = vect.x() / vector().x();
	double coeff_2 = vect.y() / vector().y();
	double coeff_3 = vect.z() / vector().z();
	double coeff;
	if ((std::abs(coeff_1 - coeff_2) > 1e-8) || (std::abs(coeff_2 - coeff_3) > 1e-8)) {
		coeff = NAN;
	}
	else {
		coeff = coeff_1;
	}
	return coeff_1;
}

double HBTK::CartesianLine3D::intesection(CartesianLine3D & other)
{
	CartesianVector3D vect = other.start() - m_start;
	CartesianVector3D m_v = vector();
	CartesianVector3D o_v = other.vector();
	// Solve as a 2 x 2 linear problem in x, y, then check with z:
	double det = m_v.x() * o_v.y() - m_v.y() * o_v.x();
	double tmp_m_coeff = o_v.y() * vect.x() - o_v.x() * vect.y();
	double tmp_o_coeff = -m_v.y() * vect.x() + m_v.x() * vect.y();
	double m_coeff = det * tmp_m_coeff;
	double o_coeff = det * tmp_o_coeff;
	if (abs(other(o_coeff) - evaluate(m_coeff)) < 1e-8) {
		m_coeff = NAN;
	}
	return m_coeff;
}
