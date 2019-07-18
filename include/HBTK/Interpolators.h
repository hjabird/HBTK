#pragma once
/*////////////////////////////////////////////////////////////////////////////
Interpolators.h

Methods and objects to perform interpolation of data.

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
#include <vector>

namespace HBTK {

	// Reference_inputs is assumed to be sorted ascending. Returns nearest if out of bounds.
	// Linearly interpolates query input value, to give a result based on reference results, 
	// interpolated lineary.
	template<typename TyIn, typename TyResult>
	TyResult linear_interpolate(std::vector<TyIn> reference_inputs,
		std::vector<TyResult> reference_results, TyIn query_input);

	// Reference_inputs is assumed to be sorted ascending. Returns nearest if out of bounds.
	// Returns the nearest known result to our input.
	template<typename TyIn, typename TyResult>
	TyResult nearest_interpolate(std::vector<TyIn> reference_inputs,
		std::vector<TyResult> reference_results, TyIn query_input);
}


// Definitions
namespace HBTK {

	template<typename TyIn, typename TyResult>
	TyResult linear_interpolate(std::vector<TyIn> reference_inputs, 
		std::vector<TyResult> reference_results, TyIn query_input)
	{
		assert(reference_inputs.size() == reference_results.size());
		TyResult interpolated_value;

		int lower_known = -1;
		for (int idx = 0; idx < (int)reference_inputs.size(); idx++) {
			if (query_input >= reference_inputs[idx]) {
				lower_known = idx;
			}
		}

		if ((lower_known != -1) && (lower_known != (int)reference_inputs.size() - 1)) {
			double fraction = (query_input - reference_inputs[lower_known]) / 
				(reference_inputs[lower_known + 1] - reference_inputs[lower_known]);
			interpolated_value = (reference_results[lower_known + 1] - reference_results[lower_known]) * fraction
				+ reference_results[lower_known];
		}
		else if (lower_known == -1) {
			interpolated_value = reference_results[0];
		}
		else {
			interpolated_value = reference_results.back();
		}

		return interpolated_value;
	}

	template<typename TyIn, typename TyResult>
	TyResult nearest_interpolate(std::vector<TyIn> reference_inputs, std::vector<TyResult> reference_results, TyIn query_input)
	{
		assert(reference_inputs.size() == reference_results.size());
		TyResult interpolated_value;

		int lower_known = -1;
		for (int idx = 0; idx < (int)reference_inputs.size(); idx++) {
			if (query_input >= reference_inputs[idx]) {
				lower_known = idx;
			}
		}

		if ((lower_known != -1) && (lower_known != (int)reference_inputs.size() - 1)) {
			double distance_to_lower = query_input - reference_inputs[lower_known];
			double distance_to_upper = reference_inputs[lower_known + 1] - query_input;
			interpolated_value = (distance_to_lower < distance_to_upper ?
				distance_to_lower : distance_to_upper);
		}
		else if (lower_known == -1) {
			interpolated_value = reference_results[0];
		}
		else {
			interpolated_value = reference_results.back();
		}

		return interpolated_value;
	}

}

