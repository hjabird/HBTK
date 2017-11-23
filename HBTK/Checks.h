#pragma once
/*////////////////////////////////////////////////////////////////////////////
Checks.h

Methods to check validity of numbers (ie. finite) inc. in vectors, other std
containers, LibEigen's matrices.

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

namespace HBTK {

	bool constexpr check_valid(float x) {
		return std::isfinite(x);
	}

	bool constexpr check_valid(double x) {
		return std::isfinite(x);
	}

	bool constexpr check_valid(long double x) {
		return std::isfinite(x);
	}

	template<typename Ty>
	bool constexpr check_valid(std::complex<Ty> x) {
		return check_valid(x.real()) && check_valid(x.imag());
	}

	template<typename Ty, int Td1, int Td2>
	bool constexpr check_valid(Eigen::Matrix<Ty, Td1, Td2> x) {
		auto nCol = x.cols();
		auto nRow = x.rows();
		bool result = true;
		for (auto i = 0; i < nCol; i++) {
			for (auto j = 0; j < nRow; j++) {
				if (!check_valid(x(j, i))) { result = false; break; }
			}
		}
		return result;
	}

	template<typename Ty>
	bool constexpr check_valid(std::vector<Ty> x) {
		bool result = true;
		for (auto &a : x) {
			if (!check_valid(a)) { result = false; break; }
		}
		return result;
	}

}
