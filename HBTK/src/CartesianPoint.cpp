#include "CartesianPoint.h"
/*////////////////////////////////////////////////////////////////////////////
CartesianPoint.cpp

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

#include <cmath>

#include "CartesianPlane.h"
#include "CartesianVector.h"

HBTK::CartesianPoint3D::CartesianPoint3D() 
{
}

HBTK::CartesianPoint3D::CartesianPoint3D(const std::array<double, 3> & location)
	: m_coord(location)
{
}

HBTK::CartesianPoint3D::~CartesianPoint3D()
{
}

double & HBTK::CartesianPoint3D::x()
{
	return m_coord[0];
}

const double & HBTK::CartesianPoint3D::x() const
{
	return m_coord[0];
}

double & HBTK::CartesianPoint3D::y()
{
	return m_coord[1];
}

const double & HBTK::CartesianPoint3D::y() const
{
	return m_coord[1];
}

double & HBTK::CartesianPoint3D::z()
{
	return m_coord[2];
}

const double & HBTK::CartesianPoint3D::z() const
{
	return m_coord[2];
}

std::array<double, 3>& HBTK::CartesianPoint3D::as_array()
{
	return m_coord;
}

const std::array<double, 3>& HBTK::CartesianPoint3D::as_array() const
{
	return m_coord;
}

HBTK::CartesianPoint3D HBTK::CartesianPoint3D::operator+(const CartesianVector3D & other) const
{
	return CartesianPoint3D(std::array<double, 3>(
		{x() + other.x(),
		 y() + other.y(),
		 z() + other.z() }));
}

HBTK::CartesianPoint3D & HBTK::CartesianPoint3D::operator+=(const HBTK::CartesianVector3D & other)
{
	x() += other.x();
	y() += other.y();
	z() += other.z();
	return *this;
}

HBTK::CartesianPoint3D HBTK::CartesianPoint3D::operator-(const CartesianVector3D & other) const
{
	return CartesianPoint3D({ 
		x() - other.x(),
		y() - other.y(),
		z() - other.z() });
}

HBTK::CartesianPoint3D & HBTK::CartesianPoint3D::operator-=(const HBTK::CartesianVector3D & other)
{
	x() -= other.x();
	y() -= other.y();
	z() -= other.z();
	return *this;
}

HBTK::CartesianVector3D HBTK::CartesianPoint3D::operator-(const CartesianPoint3D & other) const
{
	return CartesianVector3D({ 
		x() - other.x(),
		y() - other.y(),
		z() - other.z() });
}

HBTK::CartesianPoint3D HBTK::CartesianPoint3D::origin()
{
	return CartesianPoint3D({ 0, 0, 0 });
}

bool HBTK::CartesianPoint3D::operator==(const CartesianPoint3D & other) const
{
	if ((x() == other.x()) && (y() == other.y()) && (z() == other.z())) {
		return true;
	}
	else {
		return false;
	}
}

bool HBTK::CartesianPoint3D::operator!=(const CartesianPoint3D & other) const
{
	return !operator==(other);
}

double HBTK::CartesianPoint3D::distance(const CartesianPlane & plane) const
{
	return plane.distance(*this);
}


HBTK::CartesianPoint2D::CartesianPoint2D()
{
}

HBTK::CartesianPoint2D::CartesianPoint2D(const std::array<double, 2> & location)
	: m_coord(location)
{
}

HBTK::CartesianPoint2D::~CartesianPoint2D()
{
}


HBTK::CartesianPoint2D HBTK::CartesianPoint2D::origin()
{
	return CartesianPoint2D({ 0, 0 });
}

bool HBTK::CartesianPoint2D::operator==(const CartesianPoint2D & other) const
{
	if ((x() == other.x()) && (y() == other.y())) {
		return true;
	}
	else {
		return false;
	}
}

bool HBTK::CartesianPoint2D::operator!=(const CartesianPoint2D & other) const
{
	return !operator==(other);
}

void HBTK::CartesianPoint2D::rotate(double angle) {
	double tx, ty;
	tx = x() * cos(angle) + y() * sin(angle);
	ty = x() * -sin(angle) + y() * cos(angle);
	x() = tx;
	y() = ty;
	return;
}


void HBTK::CartesianPoint2D::rotate(double angle, CartesianPoint2D other) {
	double tx, ty;
	tx = cos(angle) * (x() - other.x()) + sin(angle) * (y() - other.y());
	ty = -sin(angle) * (x() - other.x()) + cos(angle) * (y() - other.y());
	x() = tx;
	y() = ty;
	return;
}

double & HBTK::CartesianPoint2D::x()
{
	return m_coord[0];
}

const double & HBTK::CartesianPoint2D::x() const
{
	return m_coord[0];
}

double & HBTK::CartesianPoint2D::y()
{
	return m_coord[1];
}

const double & HBTK::CartesianPoint2D::y() const
{
	return m_coord[1];
}

HBTK::CartesianPoint2D HBTK::CartesianPoint2D::operator+(const CartesianVector2D & other) const
{
	return CartesianPoint2D(std::array<double, 2>(
		{ x() + other.x(),
		y() + other.y() }));
}

HBTK::CartesianPoint2D HBTK::CartesianPoint2D::operator+=(const HBTK::CartesianVector2D & other)
{
	x() += other.x();
	y() += other.y();
	return *this;
}

HBTK::CartesianPoint2D HBTK::CartesianPoint2D::operator-(const CartesianVector2D & other) const
{
	return CartesianPoint2D({
		x() - other.x(),
		y() - other.y() });
}

HBTK::CartesianPoint2D HBTK::CartesianPoint2D::operator-=(const HBTK::CartesianVector2D & other)
{
	x() -= other.x();
	y() -= other.y();
	return *this;
}

HBTK::CartesianVector2D HBTK::CartesianPoint2D::operator-(const CartesianPoint2D & other) const
{
	return CartesianVector2D({
		x() - other.x(),
		y() - other.y() });
}
