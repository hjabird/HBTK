#include "stdafx.h"
#include "Checks.h"
/*////////////////////////////////////////////////////////////////////////////
Checks.cpp

Methods to check validity of numbers (ie. finite) inc. in vectors, other std
containers.

Copyright 2017 HJA Bird

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
#include <complex>

#include "CartesianFiniteLine.h"
#include "CartesianPoint.h"
#include "CartesianVector.h"

namespace HBTK {
	bool check_in_range(int x, int min, int max)
	{
		return (x >= min) && (x <= max);
	}
	bool check_finite(float x) {
		return std::isfinite(x);
	}

	bool check_in_range(float x, float min, float max)
	{
		return (x >= min) && (x <= max);
	}

	bool check_finite(double x) {
		return std::isfinite(x);
	}

	bool check_in_range(double x, double min, double max)
	{
		return (x >= min) && (x <= max);
	}

	bool check_finite(const long double x) {
		return std::isfinite(x);
	}

	bool check_in_range(const long double x, const long double min, const long double max)
	{
		return  (x >= min) && (x <= max);
	}

	bool check_finite(const CartesianPoint2D & x)
	{
		return check_finite(x.x()) && check_finite(x.y());
	}

	bool check_finite(const CartesianPoint3D & x)
	{
		return check_finite(x.x()) && check_finite(x.y())
			&& check_finite(x.z());
	}

	bool check_finite(const CartesianVector2D & x)
	{
		return check_finite(x.x()) && check_finite(x.y());
	}

	bool check_finite(const CartesianVector3D & x)
	{
		return check_finite(x.x()) && check_finite(x.y())
			&& check_finite(x.z());
	}

	bool check_finite(const CartesianFiniteLine2D & x)
	{
		return check_finite(x.start()) && check_finite(x.end());
	}

	bool check_finite(const CartesianFiniteLine3D & x)
	{
		return check_finite(x.start()) && check_finite(x.end());
	}

}
