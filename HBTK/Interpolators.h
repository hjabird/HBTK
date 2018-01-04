#pragma once

#include <cassert>

namespace HBTK {

	// Reference_inputs is assumed to be sorted ascending. Returns nearest if out of bounds.
	template<typename TyIn, typename TyResult>
	TyResult linear_interpolate(std::vector<TyIn> reference_inputs,
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

		if ((lower_known != -1) && (lower_known != (int)reference_inputs.size())) {
			double fraction = (query_input - reference_inputs[lower_known]) / 
				(reference_inputs[lower_known + 1] - reference_inputs[lower_known]);
			interpolated_value = (reference_results[lower_known + 1] - reference_results[lower_known]) * fraction
				+ reference_results[lower_known];
		}
		else if (lower_known == -1) {
			interpolated_value = reference_results[0];
		}
		else {
			interpolated_value = reference_results[reference_results.size()];
		}

		return interpolated_value;
	}

}

