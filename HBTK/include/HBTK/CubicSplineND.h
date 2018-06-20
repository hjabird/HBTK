#pragma once
/*////////////////////////////////////////////////////////////////////////////
CubicSplineND.h

An object to represent an n-dimensional cubic spline.

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

#include <array>

#include "CubicSpline1D.h"
#include "Generators.h"

namespace HBTK {
	template<int TNumDimensions>
	class CubicSplineND {
	public:
		// Initialise with a pre-existing spline for each coordinate:
		CubicSplineND(std::array<CubicSpline1D, TNumDimensions> dimensional_splines);

		// Initialise with a set of control points: x_i, y_i, ..., [nd]_i. One
		// vector for each dimension. Vector must be the same length. The resulting
		// Spline will have input from [-1, 1]
		CubicSplineND(std::array<std::vector<double>, TNumDimensions> control_points);

		~CubicSplineND();

		// Evaluate the spline.
		std::array<double, TNumDimensions> operator()(double local_position);
		std::array<double, TNumDimensions> evaluate(double local_position);

		// Get a subspline if you're only interested in one dimension:
		CubicSpline1D & operator[](const int dimension);

		// The derivatives with respect to the input parameter.
		std::array<double, TNumDimensions> derivative(double local_position);

		double lower_input_bound();
		double upper_input_bound();

	protected:
		// The spline is defined {X} = f(h) where h is a paramater
		// that controls the point on the spline. Each component of
		// X is defined by a "subspline".
		std::array<CubicSpline1D, TNumDimensions> m_subsplines;
	};
} // End namespace HBTK

// Definitions
namespace HBTK {
	template<int TNumDimensions>
	inline CubicSplineND<TNumDimensions>::CubicSplineND(std::array<CubicSpline1D, TNumDimensions> dimensional_splines)
		: m_subsplines(dimensional_splines)
	{
	}

	template<int TNumDimensions>
	inline CubicSplineND<TNumDimensions>::CubicSplineND(std::array<std::vector<double>, TNumDimensions> control_points)
	{
		int num_points = (int)control_points[0].size();
		for (auto & vector : control_points) { assert(num_points == (int)vector.size()); }
		std::vector<double> input_points = linspace(-1, 1, num_points);
		for (int i = 0; i < TNumDimensions; i++) {
			m_subsplines[i] = CubicSpline1D(input_points, control_points);
		}
	}

	template<int TNumDimensions>
	inline CubicSplineND<TNumDimensions>::~CubicSplineND()
	{
	}

	template<int TNumDimensions>
	inline std::array<double, TNumDimensions> CubicSplineND<TNumDimensions>::operator()(double local_position)
	{
		return evaluate(local_position);
	}

	template<int TNumDimensions>
	inline std::array<double, TNumDimensions> CubicSplineND<TNumDimensions>::evaluate(double local_position)
	{
		std::array<double, TNumDimensions> result;
		for (int i = 0; i < TNumDimensions; i++) {
			result[i] = m_subsplines[i](local_position);
		}
		return result;
	}

	template<int TNumDimensions>
	inline CubicSpline1D & CubicSplineND<TNumDimensions>::operator[](const int dimension)
	{
		assert(dimension > 0);
		assert(dimension < TNumDimensions);
		returm m_subsplines[dimension];
	}

	template<int TNumDimensions>
	inline std::array<double, TNumDimensions>
		CubicSplineND<TNumDimensions>::derivative(double local_position)
	{
		std::array<double, TNumDimensions> derivs;
		for (int i = 0; i < TNumDimensions; i++){
			derivs[i] = m_subsplines[i].derivative(local_position);
		}
		return derivs;
	}

	template<int TNumDimensions>
	inline double CubicSplineND<TNumDimensions>::lower_input_bound()
	{
		double lower_bound = m_subsplines[0].lower_bound();
		for (int i = 1; i < TNumDimensions; i++) {
			double other_lb = m_subsplines[i].lower_bound();
			if (lower_bound > other_lb) lower_bound = other_lb;
		}
		return lower_bound;
	}

	template<int TNumDimensions>
	inline double CubicSplineND<TNumDimensions>::upper_input_bound()
	{
		double upper_bound = m_subsplines[0].upper_bound();
		for (int i = 1; i < TNumDimensions; i++) {
			double other_lb = m_subsplines[i].upper_bound();
			if (upper_bound < other_lb) upper_bound = other_lb;
		}
		return upper_bound;
	}
}
