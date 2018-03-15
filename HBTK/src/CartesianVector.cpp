#include "CartesianVector.h"
/*////////////////////////////////////////////////////////////////////////////
CartesianVector.cpp

Vectors in Cartesian space.

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

HBTK::CartesianVector3D::CartesianVector3D()
{
}

HBTK::CartesianVector3D::CartesianVector3D(const std::array<double, 3> vector)
	: m_coord((std::array<double,3>) vector)
{
}

HBTK::CartesianVector3D::~CartesianVector3D()
{
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator+(const CartesianVector3D & other ) const
{
	return CartesianVector3D({
		x() + other.x(),
		y() + other.y(),
		z() + other.z() });
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator-(const CartesianVector3D & other) const
{
	return CartesianVector3D({
		x() - other.x(),
		y() - other.y(),
		z() - other.z() });
}

HBTK::CartesianPoint3D HBTK::CartesianVector3D::operator+(const CartesianPoint3D & other) const
{
	return CartesianPoint3D({
		x() + other.x(),
		y() + other.y(),
		z() + other.z() });
}

HBTK::CartesianPoint3D HBTK::CartesianVector3D::operator-(const CartesianPoint3D & other) const
{
	return CartesianPoint3D({
		x() - other.x(),
		y() - other.y(),
		z() - other.z() });
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator*(const double & multiplyer) const
{
	return CartesianVector3D({
		x() * multiplyer,
		y() * multiplyer,
		x() * multiplyer});
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator/(const double & divisor) const
{
	return CartesianVector3D({
		x() / divisor,
		y() / divisor,
		z() / divisor });
}

double HBTK::CartesianVector3D::length() const
{
	return sqrt(x() * x() + y() * y() + z() * z());
}

void HBTK::CartesianVector3D::normalise()
{
	double len = length();
	x() /= length();
	y() /= length();
	z() /= length();
	return;
}

double HBTK::CartesianVector3D::dot(const CartesianVector3D & other) const
{
	return x() * other.x() + y() * other.y() + z() * other.z();
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::cross(const CartesianVector3D & other) const
{
	CartesianVector3D result;
	result.x() = y() * other.z() - z() * other.y();
	result.y() = z() * other.x() - x() * other.z();
	result.z() = x() * other.y() - y() * other.x();
	return result;
}

double HBTK::CartesianVector3D::cos_angle(const CartesianVector3D & other) const
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return value;
}

double HBTK::CartesianVector3D::angle(const CartesianVector3D & other) const
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return acos(value);
}

double & HBTK::CartesianVector3D::x()
{
	return m_coord[0];
}

const double & HBTK::CartesianVector3D::x() const
{
	return m_coord[0];
}

double & HBTK::CartesianVector3D::y()
{
	return m_coord[1];
}

const double & HBTK::CartesianVector3D::y() const
{
	return m_coord[1];
}

double & HBTK::CartesianVector3D::z()
{
	return m_coord[2];
}

const double & HBTK::CartesianVector3D::z() const
{
	return m_coord[2];
}

bool HBTK::CartesianVector3D::operator==(const CartesianVector3D & other) const
{
	if ((x() == other.x()) && (y() == other.y()) && (z() == other.z())) {
		return true;
	}
	else {
		return false;
	}
}

bool HBTK::CartesianVector3D::operator!=(const CartesianVector3D & other) const
{
	return !operator==(other);
}

HBTK::CartesianVector3D::operator std::array<double, 3>() const
{
	return m_coord;
}

double HBTK::abs(const CartesianVector3D & vector)
{
	return vector.length();
}

HBTK::CartesianVector2D::CartesianVector2D()
	: x(0),
	y(0)
{
}

HBTK::CartesianVector2D::CartesianVector2D(const std::array<double, 2> & vector)
	: x(vector[0]),
	y(vector[1])
{
}

HBTK::CartesianVector2D::~CartesianVector2D()
{
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator+(const CartesianVector2D & other) const
{
	return CartesianVector2D({
		x + other.x,
		y + other.y});
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator-(const CartesianVector2D & other) const
{
	return CartesianVector2D({
		x - other.x,
		y - other.y});
}

HBTK::CartesianPoint2D HBTK::CartesianVector2D::operator+(const CartesianPoint2D & other) const
{
	return CartesianPoint2D({
		x + other.x(),
		y + other.y() });
}

HBTK::CartesianPoint2D HBTK::CartesianVector2D::operator-(const CartesianPoint2D & other) const
{
	return CartesianPoint2D({
		x - other.x(),
		y - other.y() });
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator*(const double & multiplyer) const
{
	return CartesianVector2D({
		x * multiplyer,
		y * multiplyer });
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator/(const double & divisor) const
{
	return CartesianVector2D({
		x / divisor,
		y / divisor });
}

double HBTK::CartesianVector2D::length() const
{
	return sqrt(x * x + y * y);
}

void HBTK::CartesianVector2D::normalise()
{
	double len = length();
	x /= len;
	y /= len;
	return;
}

double HBTK::CartesianVector2D::dot(const CartesianVector2D & other) const
{
	return x * other.x + y * other.y;
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::cross() const
{
	CartesianVector2D vect;
	vect.x = y;
	vect.y = -x;
	return vect;
}

double HBTK::CartesianVector2D::cos_angle(const CartesianVector2D & other) const
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return value;
}

double HBTK::CartesianVector2D::angle(const CartesianVector2D & other) const
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return acos(value);
}

bool HBTK::CartesianVector2D::operator==(const CartesianVector2D & other) const
{
	if ((x == other.x) && (y == other.y)) {
		return true;
	}
	else {
		return false;
	}
}

bool HBTK::CartesianVector2D::operator!=(const CartesianVector2D & other) const
{
	return !operator==(other);
}


HBTK::CartesianVector2D::operator std::array<double, 2>() const
{
	return { x, y };
}

double HBTK::abs(const CartesianVector2D & vector)
{
	return vector.length();
}
