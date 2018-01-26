#pragma once
/*////////////////////////////////////////////////////////////////////////////
Constants.h

A collection of constants.

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
	namespace Constants {

		/// \brief Returns the value of pi = 3.14....
		///
		/// \code
		/// #include "HBTK/Constants.h"
		/// double d_pi;
		/// float f_pi;
		/// My_special_type mst_pi;
		/// // By default the function returns double.
		/// d_pi = Constants::pi();
		/// // By can either be cast 
		/// f_pi = Constants::pi();
		/// // Or actually generate a different type (possibly of better 
		/// // precision than double)
		/// f_pi = Constants::pi<float>();
		/// mst_pi = Constants::pi<My_special_type>();
		/// \endcode 
		template<typename Ty = double>
		Ty constexpr pi() {
			return (Ty)3.1415926535897932384626433832795028841971693993751058209749445;
		}

		/// \brief Returns the value of e = 2.71828....
		///
		/// \code
		/// #include "HBTK/Constants.h"
		/// double d_e;
		/// float f_e;
		/// My_special_type mst_e;
		/// // By default the function returns double.
		/// d_e = Constants::e();
		/// // By can either be cast 
		/// f_e = Constants::e();
		/// // Or actually generate a different type (possibly of better 
		/// // precision than double)
		/// f_e = Constants::e<float>();
		/// mst_e = Constants::e<My_special_type>();
		/// \endcode 
		template<typename Ty = double>
		Ty constexpr e() {
			return (Ty)2.71828182845904523536028747135266249775724709369995;
		}

		/// \brief Returns the value of the euler constant gamma = 0.577....
		///
		/// \code
		/// #include "HBTK/Constants.h"
		/// double d_g;
		/// float f_g
		/// My_special_type mst_pi;
		/// // By default the function returns double.
		/// d_g = Constants::euler();
		/// // By can either be cast 
		/// f_g = Constants::euler();
		/// // Or actually generate a different type (possibly of better 
		/// // precision than double)
		/// f_g = Constants::euler<float>();
		/// mst_g = Constants::euler<My_special_type>();
		/// \endcode 
		template<typename Ty = double>
		Ty constexpr euler() {
			return (Ty)0.5772156649015328606065120900824024310421;
		}

		/// \brief Returns the value of i = 0 + 1i
		///
		/// \code
		/// #include "HBTK/Constants.h"
		/// #include <complex>
		/// std::complex<double> d_i;
		/// d_i = Constants::i();
		/// // Or we can use a weird type for whatever reason.
		/// std::complex<Extra_super_special_type> other;
		/// other = Constants::i<Extra_super_special_type>()
		/// \endcode 
		template<typename Ty = double>
		std::complex<Ty> constexpr i() {
			return std::complex<Ty>(0, 1);
		}
	}
}