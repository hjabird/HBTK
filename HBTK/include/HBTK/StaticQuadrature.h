#pragma once
/*////////////////////////////////////////////////////////////////////////////
StaticQuadrature.h

Represent a 1d non-adaptive quadrature.

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
#include <tuple>

#include "Integrators.h"

namespace HBTK {
	class StaticQuadrature
	{
	public:
		StaticQuadrature(const std::vector<double> & points, const std::vector<double> & weights,
			double lower_bound, double upper_bound);
		~StaticQuadrature();

		// Integrate a function:
		template<typename TyFunc>
		auto integrate(TyFunc & my_function) -> decltype(my_function((double)(0.0)));

		// Get the points and weights from the quadrature.
		std::pair<std::vector<double>, std::vector<double>> get_quadrature() const;

		// Lower bound of integration interval.
		double lower_bound() const;
		// Upper bound of integration inverval.
		double upper_bound() const;
		// Number of quadrature points.
		int num_points() const;

		// Linearly remap a quadrature to new bounds. New and old bounds must be finite.
		void linear_remap(double new_lower_bound, double new_upper_bound);
		// Shift the points in a quadrature in some direction (point += delta)
		void shift(double delta);

		// Apply Telles quadratic remap
		void telles_quadratic_remap(double singularity_position);
		// Apply Telles cubic remap
		void telles_cubic_remap(double singularity_position);
		// Apply Sato 4th order remap.
		void sato4_remap(double singularity_position);
		// Apply Sato 5th order remap.
		void sato5_remap(double singularity_position);

	private:
		double m_lower_bound, m_upper_bound;

		std::vector<double> m_points;
		std::vector<double> m_weights;

	};

	template<typename TyFunc>
	inline auto StaticQuadrature::integrate(TyFunc & my_function)
		-> decltype(my_function((double)(0.0)))
	{
		return HBTK::static_integrate(my_function, m_points, m_weights, num_points());
	}
} // End namespace HBTK

