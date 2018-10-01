#pragma once
/*////////////////////////////////////////////////////////////////////////////
Checks.h

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

#include <array>
#include <complex>
#include <vector>

namespace HBTK {
	/*
	Check finite: if a number is not real and something you can write down, return false.
	Check in range: true if min <= x <= max
	*/

	bool check_in_range(int x, int min, int max);

	bool check_finite(float x);
	bool check_in_range(float x, float min, float max);

	bool check_finite(double x);
	bool check_in_range(double x, double min, double max);

	bool check_finite(const long double x);
	bool check_in_range(const long double x, const long double min, const long double max);

	template<typename Ty>
	bool check_finite(const std::complex<Ty> x) {
		return check_finite(x.real()) && check_finite(x.imag());
	}

	template<typename Ty>
	bool check_finite(const std::vector<Ty> & x) {
		bool result = true;
		for (auto &a : x) {
			if (!check_finite(a)) { result = false; break; }
		}
		return result;
	}

	template<typename Ty, long unsigned int TySize>
	bool check_finite(const std::array<Ty, TySize> & x) {
		bool result = true;
		for (auto &a : x) {
			if (!check_finite(a)) { result = false; break; }
		}
		return result;
	}

	class CartesianPoint2D;
	bool check_finite(const CartesianPoint2D & x);
	class CartesianPoint3D;
	bool check_finite(const CartesianPoint3D & x);
	class CartesianVector2D;
	bool check_finite(const CartesianVector2D & x);
	class CartesianVector3D;
	bool check_finite(const CartesianVector3D & x);
	class CartesianFiniteLine2D;
	bool check_finite(const CartesianFiniteLine2D & x);
	class CartesianFiniteLine3D;
	bool check_finite(const CartesianFiniteLine3D & x);

	template<typename Ty>
	bool check_in_range(const std::vector<Ty> & x, const Ty & min, const Ty & max) {
		bool result = true;
		for (auto &a : x) {
			if (!check_in_range(a, min, max)) { result = false; break; }
		}
		return result;
	}

	template<typename Ty, long unsigned int TySize>
	bool check_in_range(const std::array<Ty, TySize> & x, const Ty & min, const Ty & max) {
		bool result = true;
		for (auto &a : x) {
			if (!check_in_range(a, min, max)) { result = false; break; }
		}
		return result;
	}

}
