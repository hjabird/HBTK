#pragma once
/*////////////////////////////////////////////////////////////////////////////
NumericalDifferentiation.h

Methods for numerical differentiation.

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

#include <type_traits>
#include <array>
#include <cmath>
#include "Tolerances.h"

namespace Diff {
	// DECLARATIONS

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O1A2(TFunc function, TIn position);

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O2A2(TFunc function, TIn position);


	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O1A4(TFunc function, TIn position);

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O2A4(TFunc function, TIn position);


	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O1A6(TFunc function, TIn position);

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O2A6(TFunc function, TIn position);
	

	template<int Torder, typename TFunc, typename TIn, typename TArr>
	decltype(auto) apply_diff_weights_and_vertices(TFunc function, TIn position, TArr vertices, TArr weights);


	// DEFINITIONS
	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O1A2(TFunc function, TIn position)
	{
		std::array<TIn, 2> vertices { -1., 1. };
		std::array<TIn, 2> weights { -0.5, 0.5 };
		return apply_diff_weights_and_vertices<1>(function, position, vertices, weights);
	}

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O2A2(TFunc function, TIn position)
	{
		std::array<TIn, 3> vertices { -1., 0., 1. };
		std::array<TIn, 3> weights { 1., -2., 1.};
		return apply_diff_weights_and_vertices<2>(function, position, vertices, weights);
	}

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O1A4(TFunc function, TIn position)
	{
		std::array<TIn, 4> vertices { -2., -1., 1., 2. };
		std::array<TIn, 4> weights { 1. / 12., -2. / 3., 2. / 3., -1. / 12. };
		return apply_diff_weights_and_vertices<1>(function, position, vertices, weights);
	}

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O2A4(TFunc function, TIn position)
	{
		std::array<TIn, 5> vertices { -2., -1., 0., 1., 2. };
		std::array<TIn, 5> weights { -1. / 12., 4. / 3., -5. / 2., 4. / 3., -1. / 12. };
		return apply_diff_weights_and_vertices<2>(function, position, vertices, weights);
	}

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O1A6(TFunc function, TIn position)
	{
		std::array<TIn, 6> vertices { -3., -2., -1., 1., 2., 3. };
		std::array<TIn, 6> weights { -1. / 60., 3. / 20., -0.75, 0.75, -3. / 20., 1. / 60. };
		return apply_diff_weights_and_vertices<1>(function, position, vertices, weights);
	}

	template<typename TFunc, typename TIn>
	decltype(auto) central_difference_O2A6(TFunc function, TIn position)
	{
		std::array<TIn, 7> vertices { -3., -2., -1., 0., 1., 2., 3. };
		std::array<TIn, 7> weights { 1./90., -3./20., 3./2., -49./18.,  3. / 2., -3. / 20., 1. / 90., };
		return apply_diff_weights_and_vertices<2>(function, position, vertices, weights);
	}

	template<int Torder, typename TFunc, typename TIn, typename TArr>
	decltype(auto) apply_diff_weights_and_vertices(TFunc function, TIn position, TArr vertices, TArr weights)
	{
		TIn h = pow(Quad::tolerance<TIn>(), 1./(2*Torder));
		static_assert(std::is_floating_point<decltype(h)>::value);
		std::result_of<TFunc(TIn)>::type result = 0;
		for (int idx = 0; idx < (int) vertices.size(); idx++) {
			result += function(vertices[idx] * h + position) * weights[idx];
		}
		result = result / pow(h, Torder);
		return result;
	}

}