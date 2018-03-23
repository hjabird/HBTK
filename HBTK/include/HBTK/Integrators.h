#pragma once
/*////////////////////////////////////////////////////////////////////////////
Integrators.h

Methods to perform integration of a function in one dimension.

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


#include <cassert>
#include <cmath>
#include <type_traits>
#include <stack>

namespace HBTK {

	// DECLARATIONS

	template< typename Tf, typename Tp, typename Tw>
	auto static_integrate(Tf & func, Tp & points, Tw & weights, int n_points)
		 -> decltype(func(points[0]) * weights[0]);

	template<int n_points, typename Tf, typename Tp, typename Tw>
	auto static_integrate(Tf & func, Tp & points, Tw & weights)
		 -> decltype(func(points[0]) * weights[0]) ;

	template<typename Tf_in, typename Tf, typename Ttol>
	auto adaptive_trapezoidal_integrate(Tf & func, Ttol tolerance, 
				Tf_in lower_limit, Tf_in upper_limit)
		->decltype(std::result_of<Tf(Tf_in)>::type);

	template<typename Tf_in, typename Tf, typename Ttol>
	auto adaptive_simpsons_integrate(Tf & func, Ttol tolerance, 
		Tf_in lower_limit, Tf_in upper_limit)
		->decltype(std::result_of<Tf(Tf_in)>::type);

	// DEFINITIONS

	/// \param func a function/lambda which accepts the value in points as its 
	/// only argument.
	/// \param points quadrature points. Indexable.
	/// \param weights quadrature weights. Indexable.
	/// \param n_ponts number of quadrature points.
	/// \returns the same type as returned by func.
	///
	/// \brief Integrate a function with a given quadrature.
	/// 
	/// Evaluates
	/// \f[ I = \sum\limits_{i=0}^{\texttt{n_points}} \texttt{func}(\texttt{points}_i) \times \texttt{weights}_i \f]
	///
	/// For example, using a six node gauss_legendre quadrature (overkill) - so 
	/// on interval [-1, 1] on a lambda my_fun:
	/// \code
	/// #include "HBTK/Integrators.h"
	/// const int num_points = 6;
	/// std::array<double, num_points> points, weights;
	/// HBTK::gauss_legendre<num_points, double>(points, weights);
	///
	/// auto my_fun = [](double x)->double
	/// {
	/// 	return x*x*x + x*x + 3;
	/// };
	///
	/// double result;
	/// result = HBTK::static_integrate(my_fun, points, weights, num_points);
	/// \endcode
	template< typename Tf, typename Tp, typename Tw>
	auto static_integrate(Tf & func, Tp & points, Tw & weights, int n_points)
		 -> decltype(func(points[0]) * weights[0]) 
	{
		assert(n_points > 0);
		int idx = 0;

		auto accumulator = func(points[idx]) * weights[idx];
		for (idx = 1; idx < n_points; idx++)
		{
			accumulator = accumulator + func(points[idx]) * weights[idx];
		}
		return accumulator;
	}



	/// \param func a function/lambda which accepts the value in points as its 
	/// only argument.
	/// \param points quadrature points. Indexable.
	/// \param weights quadrature weights. Indexable.
	/// \param n_points number of quadrature points.
	/// \returns the same type as returned by func.
	///
	/// \brief A specialised integrator templated with set number of points.
	/// 
	/// By specifying the number of integration points at compile time, it may be
	/// possible for the compiler to unroll the loop. It may or may not be
	/// different to normal...
	///
	/// It can be used as
	/// \code
	/// #include "HBTK/Integrators.h"
	/// const int num_points = 6;
	/// std::array<double, num_points> points, weights;
	/// HBTK::gauss_legendre<num_points, double>(points, weights);
	/// 
	/// auto my_fun = [](double x)->double
	/// {
	/// 	return x*x*x + x*x + 3;
	/// };
	/// 
	/// double result;
	/// result = HBTK::static_integrate<num_points>(my_fun, points, weights);
	/// \endcode
	template<int n_points, typename Tf, typename Tp, typename Tw>
	auto static_integrate(Tf & func, Tp & points, Tw & weights)
		 -> decltype(func(points[0]) * weights[0]) 
	{
		return static_integrate(func, points, weights, n_points);
	}


	/// \param func a function that takes a single argument of type Tf_in (ie. 
	/// that of lower and upper limit) and returns a floating point type.
	/// \param tolerance a floating point relative tolerance.
	/// \param lower_limit the lower limit of integration.
	/// \param upper_limit the upper limit of integration.
	///
	/// \brief Evaluate an integral using an adaptive trapezium rule method.
	template<typename Tf_in, typename Tf, typename Ttol>
	auto adaptive_trapezoidal_integrate(Tf & func, Ttol tolerance, 
				Tf_in lower_limit, Tf_in upper_limit)
		->decltype(std::result_of<Tf(Tf_in)>::type)
	{
		assert(tolerance > 0.0);
		assert(upper_limit > lower_limit);

		using R_Type = typename std::result_of<Tf(Tf_in)>::type;
		R_Type result = 0;
		R_Type coarse, fine;
		R_Type v_sub;
		Tf_in p_sub;

		int stack_size = 1;

		auto trap = [&](Tf_in x0, Tf_in x1, R_Type f0, R_Type f1)->R_Type {
			return (x1 - x0)*(f0 + f1) / 2.0;
		};

		typedef struct stack_frame {
			Tf_in l_lim, u_lim;
			R_Type l, u;
		} stack_frame;

		stack_frame tmp;

		std::stack<stack_frame> stack;

		stack.emplace(stack_frame{ lower_limit, upper_limit, 
									func(lower_limit), func(upper_limit) });

		while (!stack.empty())
		{
			tmp = stack.top();
			assert(tmp.u_lim != tmp.l_lim);
			p_sub = (tmp.l_lim + tmp.u_lim)*0.5;
			v_sub = func(p_sub);

			coarse = trap(tmp.l_lim, tmp.u_lim, tmp.l, tmp.u);
			fine = trap(tmp.l_lim, p_sub, tmp.l, v_sub)
				+ trap(p_sub, tmp.u_lim, v_sub, tmp.u);

			if (abs(fine - coarse) > (tmp.u_lim - tmp.l_lim) * tolerance)
			{
				stack.pop();
				stack.emplace(stack_frame{ tmp.l_lim, p_sub, tmp.l, v_sub });
				stack.emplace(stack_frame{ p_sub, tmp.u_lim, v_sub, tmp.u, });
				stack_size += 1;
			}
			else
			{
				stack.pop();
				stack_size--;
				result += fine;
			}
		}
		assert(stack_size == 0);
		return result;
	}


	/// \param func a function that takes a single argument of type Tf_in (ie. 
	/// that of lower and upper limit) and returns a floating point type.
	/// \param tolerance a floating point relative tolerance.
	/// \param lower_limit the lower limit of integration.
	/// \param upper_limit the upper limit of integration.
	///
	/// \brief Evaluate an integral using an adaptive Simpson'srule method.
	///
	/// \f[I = \int^\texttt{upper_limit}_\texttt{lower_limit} \texttt{func}(x)  dx = \texttt{adaptive_simpsons_integrate}(\texttt{func}, \texttt{tol}, \texttt{lower_limit},\texttt{upper_limit}) + \epsilon \f]
	/// where \f$|\epsilon| < \texttt{tol}\f$.
	///
	/// The code could be used as follows:
	/// \code
	/// #include "HBTK/Integrators.h"
	/// auto my_f = [](double x)->double
	/// { x*x*x*x*x*x*x*x*x; };
	/// auto result = HBTK::adaptive_simpsons_integrate(my_f, 1e-10, 0.0, 1.0);
	/// \endcode
	///	Uses a simple adaptive composite simpson's rule to evaluated to a given 
	/// tolerance.	
	template<typename Tf_in, typename Tf, typename Ttol>
	auto adaptive_simpsons_integrate(Tf & func, Ttol tolerance, 
		Tf_in lower_limit, Tf_in upper_limit)
		->decltype(std::result_of<Tf(Tf_in)>::type)
	{
		assert(tolerance > 0.0);
		assert(lower_limit < upper_limit);

		using R_Type = typename std::result_of<Tf(Tf_in)>::type;
		R_Type result = 0;
		R_Type coarse, fine;
		// 1/4 and 3/4 points coordinates and values:
		R_Type v_sub_l, v_sub_u;
		Tf_in p_sub_l, p_sub_u, p_cent;

		int stack_size = 1;

		auto simp = [&](Tf_in x0, Tf_in x2, R_Type f0, R_Type f1, R_Type f2)->R_Type 
		{
			return (x2 - x0)*(f0 + 4.0 * f1 + f2) / 6.0;
		};

		typedef struct stack_frame {
			Tf_in l_lim, u_lim;
			R_Type l, u, c;
		} stack_frame;

		stack_frame tmp;

		std::stack<stack_frame> stack;

		stack.emplace(stack_frame{ lower_limit, upper_limit, func(lower_limit), 
			func(upper_limit), func((upper_limit - lower_limit) / 2.0) });

		while (!stack.empty())
		{
			tmp = stack.top();
			assert(tmp.u_lim != tmp.l_lim);
			p_cent = (tmp.l_lim + tmp.u_lim)*0.5;
			p_sub_l = tmp.l_lim + (tmp.u_lim - tmp.l_lim)*0.25;
			p_sub_u = tmp.l_lim + (tmp.u_lim - tmp.l_lim)*0.75;
			v_sub_l = func(p_sub_l);
			v_sub_u = func(p_sub_u);

			coarse = simp(tmp.l_lim, tmp.u_lim, tmp.l, tmp.c, tmp.u);
			fine = simp(tmp.l_lim, p_cent, tmp.l, v_sub_l, tmp.c)
				+ simp(p_cent, tmp.u_lim, tmp.c, v_sub_u, tmp.u);

			if (abs(fine - coarse) > (tmp.u_lim - tmp.l_lim) * tolerance)
			{
				stack.pop();
				stack.emplace(stack_frame{ tmp.l_lim, p_cent, tmp.l, tmp.c, v_sub_l });
				stack.emplace(stack_frame{ p_cent, tmp.u_lim, tmp.c, tmp.u, v_sub_u });
				stack_size += 1;
			}
			else
			{
				stack.pop();
				stack_size--;
				result += fine;
			}
		}
		assert(stack_size == 0);
		return result;
	}

}

