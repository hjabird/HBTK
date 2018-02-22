#pragma once
/*////////////////////////////////////////////////////////////////////////////
CubicSpline1D.h

An object to represent a 1D cubic spline.

Copyright 2018 HJA Bird

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
#include <mutex>

namespace HBTK {
	class CubicSpline1D {
	public:
		// Construct a spline with derivatives at both bounds defined.
		CubicSpline1D(std::vector<double> point_locations,
			std::vector<double> point_values, 
			double derivative_x0, double derivative_x_n);
		// Construct a spline with the derivative at only the n = 0
		// end defined. The other end in natural.
		CubicSpline1D(std::vector<double> point_locations,
			std::vector<double> point_values,
			double derivative_x0);
		// Construct a spline with natural boundary condition at
		// both ends.
		CubicSpline1D(std::vector<double> point_locations,
			std::vector<double> point_values);

		~CubicSpline1D();

		double operator()(double location);
		double evaluate(double location);

		double lower_input_bound();
		double upper_input_bound();

	private:

		// The reference inputs x to interpolate y = f(x);
		std::vector<double> m_point_locations;
		// The reference outputs y of for interpolation y = f(x);
		std::vector<double> m_point_values;
		// The second derivatives needed to construct a cubic
		// spline.
		std::vector<double> m_second_derivatives;

		// Mutex: the second derivatives should not be computed at construction, but only 
		// when the spline is first evaluated. In a multihreaded enviroment, this causes
		// issues. 
		std::mutex m_deriv_compute_mutex;

		// Boundary conditions.
		double m_derivative_x0, m_derivative_xn;
		bool m_natural_bc_x0, m_natural_bc_xn;

		// Compute information needed for spline:
		void compute_second_derivatives();
		// Have we computed compute_second_derivatives() yet?
		volatile bool m_derivatives_computed;
	};
}

