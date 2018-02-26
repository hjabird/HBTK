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
