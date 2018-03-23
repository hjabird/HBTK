#pragma once
/*////////////////////////////////////////////////////////////////////////////
Remaps.h

A collection of integral remaps.

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
#include <cassert>

namespace HBTK {
	
	// Declarations

	template<typename Ty>
	constexpr void linear_remap(Ty & point, Ty & weight,
								Ty original_x0, Ty original_x1,
								Ty new_x0, Ty new_x1);

	template<typename Ty>
	constexpr void telles_quadratic_remap(Ty & point, Ty & weight, 
										const Ty & singularity);

	template<typename Ty>
	constexpr void telles_cubic_remap(Ty & point, Ty & weight, 
									  Ty singularity_pos);

	template<int Torder, typename Ty>
	constexpr void sato_remap(Ty & point, Ty & weight, 
							  Ty singularity_pos);

	template<typename Ty>
	constexpr void doblare_remap(Ty & point, Ty & weight,
										Ty singularity_pos);

	template<typename Ty>
	constexpr void exponential_remap(Ty & point, Ty & weight, Ty lower_limit);

	// TODO:
	// tanh_sinh
	// Sigmoidal

	// DEFINITIONS

	/// \param point coordinate of integration point - to be mutated
	/// \param weight weight of integration point - to be mutated
	/// \param original_x0 original lower limit of integration interval
	/// \param original_x1 original upper limit of integration interval
	/// \param new_x0 new lower limit of integration
	/// \param new_x1 new upper limit of integration
	///
	/// \brief Linearly remap a point and a weight
	///
	/// An integral can be approximated by a quadrature
	/// \f[\int^a_bf(x)dx = \sum w_if(x_i) ,\f] with points \f$x_i\f$
	/// and weights \f$w_i\f$.
	/// This quadrature integrates correctly the interval [a,b].
	/// However, it may be desired to use different limits:
	/// \f[\int^c_d f(x) dx.\f] By linearly remapping a quadrature this
	/// can be achieved.
	///
	/// To remap a point 0.0 with weight 1.0, from -1.0, 1.0 to 2.0, 6.0 
	/// one would write:
	/// \code
	/// #include "HBTK/Remaps.h"
	/// double p, w;
	/// p = 0.0;	w = 1.0;
	/// HBTK::linear_remap(p, w, -1.0, 1.0, 2.0, 6.0);
	/// std::cout << p << " , " << w << std::endl;	// prints 4.0 , 4.0
	/// \endcode
	/// Now the quadrature, will integrate the interval 2.0, 6.0.
	/// 
	/// Care must be taken to ensure that all arguments are of the same type, 
	/// or explicity typing must be used: \code
	/// HBTK::linear_remap<double>(p, w, -1, 1, 2, 6) \endcode
	///
	template<typename Ty>
	constexpr void linear_remap(Ty & point, Ty & weight,
							Ty original_x0, Ty original_x1,
							Ty new_x0, Ty new_x1) 
	{
		Ty Dx_ratio = (new_x1 - new_x0) / (original_x1 - original_x0);
		Ty offset = new_x0 - original_x0;
		weight = weight * Dx_ratio;
		point = (point - original_x0)*Dx_ratio + offset + original_x0;
		return;
	}

	/// \param point integration point - mutated.
	/// \param point integration weight - mutated.
	/// \param singularity position. Should be +1 or -1.
	///
	/// \brief Applies Telles' quadratic integral transfrom to a quadrature
	/// point / weight
	///
	/// Telles' quadratic remap increases the accuracy of quadratures when 
	/// there is a singularity at the boundary of the integration interval,
	/// which must be mapped to [-1, 1]. 
	/// The input point and weight are modified.
	/// The code can be used as follows:
	/// \code
	/// #include "HBTK/Remaps.h"
	/// double px, wx;
	/// px = -1;
	/// wx = 1;
	/// HBTK::telles_quadratic_remap(px, wx, true);
	/// \endcode
	template<typename Ty>
	constexpr void telles_quadratic_remap(Ty & point, Ty & weight, 
										  const Ty & singularity) 
	{
		assert(abs(singularity) == 1);
		const Ty & s_pos = singularity;
		Ty tmp_p( (1 - point*point)*(s_pos + sqrt(s_pos*s_pos - 1)) / 2 + point );
		Ty tmp_w( (-point * (s_pos + sqrt(s_pos*s_pos - 1)) + 1) *weight );
		point = tmp_p;
		weight = tmp_w;
		return;
	}

	/// \param point integration point - mutated.
	/// \param point integration weight - mutated.
	/// \param singularity_pos the position of the singularity
	///
	/// \brief Applies Telles' cubic integral transfrom to a quadrature
	/// point / weight
	///
	/// Telles' cubic remap increases the accuracy of quadratures when there  
	/// is a singularity.
	/// The inverval of integration must be mapped to [-1, 1]. 
	/// The input point and weight are modified.
	///
	/// The code can be used as follows:
	/// \code
	/// #include "HBTK/Remaps.h"
	/// double px, wx;
	/// px = -1;
	/// wx = 1;
	/// HBTK::telles_cubic_remap(px, wx, 0.75);
	/// \endcode
	template<typename Ty>
	constexpr void telles_cubic_remap(Ty & point, Ty & weight, Ty singularity_pos)
	{
		// remap singularity position.
		Ty sp_rm (cbrt((singularity_pos - 1)*(singularity_pos + 1)*(singularity_pos + 1))
			+   cbrt((singularity_pos - 1)*(singularity_pos - 1)*(singularity_pos + 1))
			+   singularity_pos );
		// and calculate new point & weight.
		Ty tmp_p( (pow(point - sp_rm, 3) + sp_rm*(sp_rm*sp_rm + 3)) 
			/ (3 * sp_rm*sp_rm + 1) );
		Ty tmp_w = ((3 * pow(sp_rm - point, 2)) / (3 * sp_rm*sp_rm + 1) * weight);
		point = tmp_p;
		weight = tmp_w;
		return;
	}

	/// \param point integration point - mutated.
	/// \param point integration weight - mutated.
	/// \param singularity_pos either -1 or 1 are valid.
	/// \param Torder the order of the transfromation to use.
	///
	/// \brief Applies Sato's transform of order Torder to point and weight.
	///
	/// Sato's high order is an effective method for increasing the accuracy
	/// of qaudratures with a singularity.
	///
	/// The code can be used as follows:
	/// \code
	/// #include "HBTK/Remaps.h"
	/// double px, wx;
	/// px = -1;
	/// wx = 1;
	/// HBTK::sato_remap<3>(px, wx, 1.0);
	/// \endcode
	/// where a third order remap is being used.
	/// If the arguments must be cast to a type use:
	///	\code
	/// #include "HBTK/Remaps.h"
	/// double px, 
	/// float wx;
	/// px = -1;
	/// wx = 1;
	/// HBTK::sato_remap<3, double>(px, wx, 1.0);
	/// \endcode
	/// or explicity type the arguments.
	template<int Torder, typename Ty>
	constexpr void sato_remap(Ty & point, Ty & weight, Ty singularity_pos)
	{
		static_assert(Torder > 1, "The order of a Sato remap must be greater than one.");
		static_assert(Torder < 10, "A Sato remap of this order is pretty much guarenteed to have numerical problems.");
		assert(abs(singularity_pos) == 1);
		Ty tmp_p = singularity_pos - (singularity_pos / pow(2, Torder - 1)) 
								* pow(1 - singularity_pos * point, Torder);
		Ty tmp_w = Torder * pow(2, 1 - Torder) * singularity_pos*singularity_pos 
						* pow(1 - singularity_pos*point, Torder - 1) * weight;
		point = tmp_p;
		weight = tmp_w;
		return;
	}

	/// \param point integration point - mutated.
	/// \param point integration weight - mutated.
	/// \param singularity_positive between -1, 1
	///
	/// \brief Applies Doblare transform for a CPV or weakly singular integrand.
	///
	///
	template<typename Ty>
	constexpr void doblare_remap(Ty & point, Ty & weight, Ty singularity_pos)
	{
		assert(abs(singularity_pos) < 1.);
		assert(abs(point) <= 1);
		Ty tmp_p = singularity_pos * ( 1 - pow(point, 4) ) + pow(point, 3);
		Ty tmp_w = weight * (-4. * pow(point, 3) * singularity_pos + 3 * point * point);
		point = tmp_p;
		weight = tmp_w;
		return;
	}

	/// \param point integration point - mutated.
	/// \param point integration weight - mutated.
	/// \param original_lower_limit 
	///
	/// \brief Applies an exponential transform to a semiinfinite
	/// integral
	///
	/// Applies a tranformation of the the form:
	/// \f[\int^\infty_{lower_limit}f(x)dx = \int^1_{-1}f(\phi(\lambda)d\lambda  ,\f]
	///
	template<typename Ty>
	constexpr void exponential_remap(Ty & point, Ty & weight, Ty original_lower_limit)
	{
		Ty tmp = exp(2 / (1 - point) - 1);
		Ty tmp_p = tmp - 1 + original_lower_limit;
		weight = 2 * tmp / (pow(1 - point, 2));
		point = tmp_p;
		return void();
	}

}

