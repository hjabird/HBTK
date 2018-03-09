#include "CartesianPlane.h"
/*////////////////////////////////////////////////////////////////////////////
CartesianLine.cpp

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

#include <exception>
#include <string>

#include "CartesianFiniteLine.h"

HBTK::CartesianPlane::CartesianPlane()
	: m_origin({0, 0, 0}),
	m_x_dir({1, 0, 0}),
	m_y_dir({0, 1, 0})
{
}

HBTK::CartesianPlane::CartesianPlane(const CartesianPoint3D & origin, 
	const CartesianPoint3D & primary_dir, const CartesianPoint3D & secondary_dir)
	: m_origin(origin),
	m_x_dir(),
	m_y_dir()
{
	m_x_dir = primary_dir - origin;
	m_x_dir.normalise();
	if ((primary_dir == origin) || (secondary_dir == origin)) {
		throw std::invalid_argument("HBTK::CartesianPlane::CartesianPlane(point, point, point):"
			" Two of three points were identical. A plane could not be defined. "
			__FILE__ ":" + std::to_string(__LINE__));
	}

	m_y_dir = secondary_dir - origin;
	m_y_dir = m_y_dir - m_x_dir * (m_x_dir.dot(m_y_dir));
	m_y_dir.normalise();
	return;
}

HBTK::CartesianPlane::CartesianPlane(const CartesianPoint3D & origin, 
	const CartesianVector3D & normal)
	: m_origin(origin),
	m_x_dir(),
	m_y_dir()
{
	CartesianVector3D gen_axis({ 1, 0, 0 });
	gen_axis = (normal != gen_axis ? gen_axis : CartesianVector3D({0., 1., 0.}));
	m_x_dir = normal.cross(gen_axis);
	m_x_dir.normalise();
	m_y_dir = normal.cross(m_x_dir);
	m_y_dir.normalise();
}

HBTK::CartesianPlane::CartesianPlane(const CartesianFiniteLine3D & origin_primary_dir, 
	const CartesianPoint3D & secondary_dir)
	: m_origin(origin_primary_dir.start()),
	m_x_dir(),
	m_y_dir()
{
	m_x_dir = origin_primary_dir.vector();
	m_x_dir.normalise();
	m_y_dir = secondary_dir - m_origin;
	if (m_x_dir.cos_angle(m_y_dir) == 1) { throw - 1; }
	m_y_dir = m_y_dir - m_x_dir * m_x_dir.dot(m_y_dir);
	m_y_dir.normalise();
}

HBTK::CartesianPlane::~CartesianPlane()
{
}

HBTK::CartesianPoint3D HBTK::CartesianPlane::operator()(const CartesianPoint2D & plane_point) const
{
	return evaluate(plane_point);
}

HBTK::CartesianPoint3D HBTK::CartesianPlane::evaluate(const CartesianPoint2D & plane_point) const
{
	CartesianPoint3D point(m_origin);
	point = point + m_x_dir * plane_point.x;
	point = point + m_y_dir * plane_point.y;
	return point;
}

HBTK::CartesianPoint3D & HBTK::CartesianPlane::origin()
{
	return m_origin;
}

const HBTK::CartesianPoint3D & HBTK::CartesianPlane::origin() const
{
	return m_origin;
}
