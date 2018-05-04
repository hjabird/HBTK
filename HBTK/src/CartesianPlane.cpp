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

#include <algorithm>
#include <cassert>
#include <exception>
#include <string>

#include "CartesianFiniteLine.h"
#include "Checks.h"

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
	point = point + m_x_dir * plane_point.x();
	point = point + m_y_dir * plane_point.y();
	return point;
}

HBTK::CartesianVector3D HBTK::CartesianPlane::normal() const
{
	CartesianVector3D norm = m_x_dir.cross(m_y_dir);
	norm.normalise();
	return norm;
}

double HBTK::CartesianPlane::distance(const CartesianPoint3D & point_in_space) const
{
	CartesianVector3D normal = m_x_dir.cross(m_y_dir);
	normal.normalise();
	CartesianVector3D origin_to_point = point_in_space - m_origin;
	double distance = normal.dot(origin_to_point);
	return distance;
}

HBTK::CartesianPoint2D  HBTK::CartesianPlane::projection(const CartesianPoint3D & point_in_space) const
{
	CartesianVector3D normal = m_x_dir.cross(m_y_dir);
	normal.normalise();
	CartesianVector3D origin_to_point = point_in_space - m_origin;
	double distance = normal.dot(origin_to_point);
	CartesianPoint3D on_plane = point_in_space - normal * distance;

	CartesianPoint2D local_sys;
	// Try and make our maths better by choosing the bigger elements of the vector:
	int ix, iy;
	ix = std::max_element(m_x_dir.as_array().begin(), m_x_dir.as_array().end(),
		[](const double &a, const double &b) {
		return (std::abs(b) > std::abs(a) ? true : false); })
		- m_x_dir.as_array().begin();
	// We don't wat the same index as ix for iy, so we take the max of the 
	// remaining indexes. These should never both be zero.
	iy = (std::abs(*(m_y_dir.as_array().begin() + (ix + 1) % 3))
			> std::abs(*(m_y_dir.as_array().begin() + (ix + 2) % 3)) ?
		(ix + 1) % 3 : (ix + 2) % 3);
	local_sys.y() = on_plane.as_array()[iy] - on_plane.as_array()[ix] 
		* m_x_dir.as_array()[iy] / m_x_dir.as_array()[ix];
	local_sys.y() /= m_y_dir.as_array()[iy] - m_y_dir.as_array()[ix]
		* m_x_dir.as_array()[iy] / m_x_dir.as_array()[ix];
	local_sys.x() = (on_plane.as_array()[ix] -
		local_sys.y() * m_y_dir.as_array()[ix]) /
		m_x_dir.as_array()[ix];
	assert(HBTK::check_finite(local_sys));
	return local_sys;
}

HBTK::CartesianPoint3D HBTK::CartesianPlane::closest_point(const CartesianPoint3D & point_in_space) const
{
	CartesianVector3D norm = normal();
	CartesianVector3D vect_from_plane = point_in_space - origin();
	CartesianPoint3D point = norm * (norm.dot(vect_from_plane));
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

HBTK::CartesianPoint3D HBTK::CartesianPlane::symmetric_point(const CartesianPoint3D & point) const
{
	double dist = distance(point);
	CartesianVector3D vect_to_symmetric = normal() * dist;
	CartesianPoint3D symettric_point = point - vect_to_symmetric * 2;
	assert(HBTK::check_finite(symettric_point));
	return symettric_point;
}
