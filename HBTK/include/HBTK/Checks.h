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

#include <vector>
#include <complex>

namespace HBTK {

	bool check_finite(float x);

	bool check_finite(double x);

	bool check_finite(const long double x);

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

}
