#pragma once
/*////////////////////////////////////////////////////////////////////////////
Tolerances.h

Tolerances for floating point types.

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
#include <complex>

namespace HBTK {

	/// \brief returns the tolerance of a type Ty.
	///
	/// Useage:
	/// \code Ty tol = HBTK::tolerance<double>() \endcode
	template < typename Ty >
	constexpr Ty tolerance(void);

	/// \brief returns the tolerance of double (10^-15)
	/// \code double tol = HBTK::tolerance<double>() \endcode
	template <>
	constexpr double tolerance<double>(void) 
	{
		return 1e-15;
	}


	/// \brief returns the tolerance of float (10^-7)
	/// \code float tol = HBTK::tolerance<float>() \endcode
	template <>
	constexpr float tolerance<float>(void)
	{
#pragma warning(suppress: 4305)
		return 1e-7;
	}


	/// \brief returns the tolerance of complex<double>
	/// \code std::complex<double> tol = HBTK::tolerance<std::complex<double>>() \endcode
	template <>
	constexpr std::complex<double> tolerance<std::complex<double>>(void)
	{
		std::complex<double> a(tolerance<double>(), tolerance<double>());
		return a;
	}
}
