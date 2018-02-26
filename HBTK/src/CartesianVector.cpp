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

#include "CartesianPoint.h"

HBTK::CartesianVector3D::CartesianVector3D()
	: m_vector({ 0, 0, 0 })
{
}

HBTK::CartesianVector3D::CartesianVector3D(std::array<double, 3> vector)
	: m_vector(vector)
{
}

HBTK::CartesianVector3D::~CartesianVector3D()
{
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator+(CartesianVector3D & other )
{
	return CartesianVector3D({
		x() + other.x(),
		y() + other.y(),
		z() + other.z() });
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator-(CartesianVector3D & other)
{
	return CartesianVector3D({
		x() - other.x(),
		y() - other.y(),
		z() - other.z() });
}

HBTK::CartesianPoint3D HBTK::CartesianVector3D::operator+(CartesianPoint3D & other)
{
	return CartesianPoint3D({
		x() + other.x(),
		y() + other.y(),
		z() + other.z() });
}

HBTK::CartesianPoint3D HBTK::CartesianVector3D::operator-(CartesianPoint3D & other)
{
	return CartesianPoint3D({
		x() - other.x(),
		y() - other.y(),
		z() - other.z() });
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator*(const double & multiplyer)
{
	return CartesianVector3D({
		x() * multiplyer,
		y() * multiplyer,
		x() * multiplyer});
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::operator/(const double & divisor)
{
	return CartesianVector3D({
		x() / divisor,
		y() / divisor,
		z() / divisor });
}

double HBTK::CartesianVector3D::length()
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

double HBTK::CartesianVector3D::dot(CartesianVector3D & other)
{
	return x() * other.x() + y() * other.y() + z() * other.z();
}

HBTK::CartesianVector3D HBTK::CartesianVector3D::cross(CartesianVector3D & other)
{
	CartesianVector3D result;
	result.x() = y() * other.z() - z() * other.y();
	result.y() = z() * other.x() - x() * other.z();
	result.z() = x() * other.y() - y() * other.x();
	return result;
}

double HBTK::CartesianVector3D::cos_angle(CartesianVector3D & other)
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return value;
}

double HBTK::CartesianVector3D::angle(CartesianVector3D & other)
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return acos(value);
}

double & HBTK::CartesianVector3D::x()
{
	return m_vector[0];
}

double & HBTK::CartesianVector3D::y()
{
	return m_vector[1];
}

double & HBTK::CartesianVector3D::z()
{
	return m_vector[2];
}

bool HBTK::CartesianVector3D::operator==(const CartesianVector3D & other)
{
	if (m_vector == other.m_vector) {
		return true;
	}
	else {
		return false;
	}
}

bool HBTK::CartesianVector3D::operator!=(const CartesianVector3D & other)
{
	return !operator==(other);
}

HBTK::CartesianVector3D::operator std::array<double, 3>()
{
	return m_vector;
}

double HBTK::abs(CartesianVector3D vector)
{
	return vector.length();
}

HBTK::CartesianVector2D::CartesianVector2D()
	: m_vector({ 0, 0 })
{
}

HBTK::CartesianVector2D::CartesianVector2D(std::array<double, 2> vector)
	: m_vector(vector)
{
}

HBTK::CartesianVector2D::~CartesianVector2D()
{
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator+(CartesianVector2D & other)
{
	return CartesianVector2D({
		x() + other.x(),
		y() + other.y()});
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator-(CartesianVector2D & other)
{
	return CartesianVector2D({
		x() - other.x(),
		y() - other.y()});
}

HBTK::CartesianPoint2D HBTK::CartesianVector2D::operator+(CartesianPoint2D & other)
{
	return CartesianPoint2D({
		x() + other.x(),
		y() + other.y() });
}

HBTK::CartesianPoint2D HBTK::CartesianVector2D::operator-(CartesianPoint2D & other)
{
	return CartesianPoint2D({
		x() - other.x(),
		y() - other.y() });
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator*(const double & multiplyer)
{
	return CartesianVector2D({
		x() * multiplyer,
		y() * multiplyer });
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::operator/(const double & divisor)
{
	return CartesianVector2D({
		x() / divisor,
		y() / divisor });
}

double HBTK::CartesianVector2D::length()
{
	return sqrt(x() * x() + y() * y());
}

void HBTK::CartesianVector2D::normalise()
{
	double len = length();
	x() /= length();
	y() /= length();
	return;
}

double HBTK::CartesianVector2D::dot(CartesianVector2D & other)
{
	return x() * other.x() + y() * other.y();
}

HBTK::CartesianVector2D HBTK::CartesianVector2D::cross()
{
	CartesianVector2D vect;
	vect.x() = y();
	vect.y() = -x();
	return vect;
}

double HBTK::CartesianVector2D::cos_angle(CartesianVector2D & other)
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return value;
}

double HBTK::CartesianVector2D::angle(CartesianVector2D & other)
{
	double value;
	value = dot(other);
	value /= length() * other.length();
	return acos(value);
}

double & HBTK::CartesianVector2D::x()
{
	return m_vector[0];
}

double & HBTK::CartesianVector2D::y()
{
	return m_vector[1];
}


HBTK::CartesianVector2D::operator std::array<double, 2>()
{
	return m_vector;
}

double HBTK::abs(CartesianVector2D vector)
{
	return vector.length();
}
