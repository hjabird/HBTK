#pragma once
/*////////////////////////////////////////////////////////////////////////////
Generators.h

Generate vectors of values. Has functions like linspace, logspace, meshgrid...

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
#include <type_traits>
#include <cassert>
#include <cmath>

#include "Checks.h"

namespace HBTK {

	std::vector<double> linspace(double start, double end);
	std::vector<double> linspace(double start, double end, int number_of_points);
	template< typename Ty >
	void linspace(double start, double end, int number_of_points, Ty & target_indexible);

	std::vector<double> logspace(double start_power, double end_power);
	std::vector<double> logspace(double start_power, double end_power, int number_of_points);
	std::vector<double> logspace(double start_power, double end_power, int number_of_points, double base);
	template< typename Ty >
	void logspace(double start_power, double end_power, int number_of_points, double base, Ty & target_indexible);

	std::vector<double> geomspace(double start, double end);
	std::vector<double> geomspace(double start, double end, int number_of_points);
	std::vector<double> geomspace(double start, double end, int number_of_points, double base);
	template< typename Ty >
	void geomspace(double start, double end, int number_of_points, double base, Ty & target_indexible);

	std::vector<double> uniform(double value, int number_of_points);
	template<typename TyStore, typename TyVal>
	void uniform(TyStore & target_indexable, TyVal fill_value);


} // End Namespace HBTK - Declarations

namespace HBTK // Definitions
{

	template<typename Ty>
	void linspace(double start, double end, int number_of_points, Ty & target_indexible)
	{
		assert(HBTK::check_finite(start));
		assert(HBTK::check_finite(end));
		assert(number_of_points > 0);
		//decltype(target_indexible[int])
		static_assert(std::is_floating_point<double>::value);
		for (int idx = 0; idx < number_of_points; idx++) {
			target_indexible[idx] = start + idx * (end - start) / (number_of_points - 1);
		}
		return;
	}

	template<typename Ty>
	void logspace(double start, double end, int number_of_points, double base, Ty & target_indexible)
	{
		assert(HBTK::check_finite(start));
		assert(HBTK::check_finite(end));
		assert(number_of_points > 0);

		//static_assert(std::is_floating_point<decltype(target_indexible[int])>::value);
		for (int idx = 0; idx < number_of_points; idx++) {
			auto linear_pos = start + idx * (end - start) / (number_of_points - 1);
			target_indexible[idx] = pow(base, linear_pos);
		}
		return;
	}

	template<typename Ty>
	void geomspace(double start, double end, int number_of_points, double base, Ty & target_indexible)
	{
		assert(HBTK::check_finite(start) && (start > 0));
		assert(HBTK::check_finite(end) && (end > 0));
		assert(number_of_points > 0);
		
		auto log_start = log(start) / log(base);
		auto log_end = log(end) / log(base);
		logspace(log_start, log_end, number_of_points, base, target_indexible);
		return;
	}

	template<typename TyStore, typename TyVal>
	void uniform(TyStore & target_indexable, TyVal uniform_value)
	{
		for (int idx = 0; idx < (int) target_indexable.size(); idx++) {
			target_indexable[idx] = uniform_value;
		}
	}

} // End HBTK namespace
