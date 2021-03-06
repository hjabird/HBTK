#include "StaticQuadrature.h"
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

#include <cassert>
#include <cmath>

#include "Checks.h"
#include "Remaps.h"


HBTK::StaticQuadrature::StaticQuadrature(const std::vector<double> & points, 
	const std::vector<double> & weights, double lower_bound, double upper_bound)
	: m_points(points),
	m_weights(weights),
	m_lower_bound(lower_bound),
	m_upper_bound(upper_bound)
{
	assert(HBTK::check_finite(weights));
}

HBTK::StaticQuadrature::~StaticQuadrature()
{
}


/// \returns a pair of std::vector<double> points then weights.
///
/// \brief Get the quadrature points and weights.
/// 
/// Extract the points and weights that describe the quadrature.
///
/// For example
/// \code
/// #include <HBTK/GaussQuadrature.h>
/// #include <HBTK/StaticQuadrature.h> // Included in GaussQuad anyway
/// 
/// HBTK::StaticQuadrature quad = HBTK::gauss_legendre(10)
/// std::vector<double> points = quad.first;
/// std::vector<double> weights = quad.second;
/// \endcode
std::pair<std::vector<double>, std::vector<double>> HBTK::StaticQuadrature::get_quadrature() const
{
	return std::make_pair(m_points, m_weights);
}

/// \returns The lower limit of integration of the quadrature as double.
///
/// \brief Get the lower limit of integration
double HBTK::StaticQuadrature::lower_bound() const
{
	assert(num_points() > 0);
	return m_lower_bound;
}

/// \returns The upper limit of integration of the quadrature as double.
///
/// \brief Get the upper limit of integration
double HBTK::StaticQuadrature::upper_bound() const
{
	assert(num_points() > 0);
	return m_upper_bound;
}

/// \returns The number of points in the quadrature
///
/// \brief Get the number of integration points used by the quadratute
int HBTK::StaticQuadrature::num_points() const
{
	assert(m_points.size() == m_weights.size());
	return m_points.size();
}

/// \param new_lower_bound new lower limit of integration
/// \param new_upper_bound new upper limit of integration
///
/// \brief Linearly remap a point and a weight
void HBTK::StaticQuadrature::linear_remap(double new_lower_bound, double new_upper_bound)
{
	assert(HBTK::check_finite(new_lower_bound));
	assert(HBTK::check_finite(new_upper_bound));
	int size = (int)m_points.size();
	for (int i = 0; i < size; i++) {
		HBTK::linear_remap(m_points[i], m_weights[i], m_lower_bound, m_upper_bound,
			new_lower_bound, new_upper_bound);
	}
	m_upper_bound = new_upper_bound;
	m_lower_bound = new_lower_bound;
	return;
}

/// \param shift vector
///
/// \brief integrate x_l + delta to x_u + delta
///
/// Move the quadrature such that the limits change by 
/// the same amount.
void HBTK::StaticQuadrature::shift(double delta)
{
	assert(HBTK::check_finite(delta));
	for (double &point : m_points) { point += delta; }
	m_lower_bound += delta;
	m_upper_bound += delta;
	return;
}


/// \param singularity position. Should be upper or lower limit.
///
/// \brief Applies Telles' quadratic integral transfrom to a quadrature
/// points / weights
///
/// Telles' quadratic remap increases the accuracy of quadratures when 
/// there is a singularity at the boundary of the integration interval,
/// which must be mapped to [-1, 1]. 
/// The input point and weight are modified.
void HBTK::StaticQuadrature::telles_quadratic_remap(double singularity_position)
{
	assert(HBTK::check_finite(m_lower_bound));
	assert(HBTK::check_finite(m_upper_bound));
	assert((singularity_position == m_lower_bound) || (singularity_position == m_upper_bound));
	double m_original_upper, m_original_lower, remaped_sing_pos;
	m_original_upper = m_upper_bound;
	m_original_lower = m_lower_bound;
	remaped_sing_pos = (singularity_position == m_lower_bound ? -1 : 1);
	linear_remap(-1, 1);
	int size = num_points();
	for (int i = 0; i < size; i++) {
		HBTK::telles_quadratic_remap(m_points[i], m_weights[i], remaped_sing_pos);
	}
	linear_remap(m_original_lower, m_original_upper);
	assert(HBTK::check_finite(m_points));
	assert(HBTK::check_finite(m_weights));
	return;
}

/// \param singularity_pos the position of the singularity
///
/// \brief Applies Telles' cubic integral transfrom to a quadrature
/// point / weight
///
/// Telles' cubic remap increases the accuracy of quadratures when there  
/// is a singularity.
/// The inverval of integration must be mapped to [-1, 1]. 
/// The input point and weight are modified.
void HBTK::StaticQuadrature::telles_cubic_remap(double singularity_position)
{
	assert(HBTK::check_finite(m_lower_bound));
	assert(HBTK::check_finite(m_upper_bound));
	assert((singularity_position == m_lower_bound) || (singularity_position == m_upper_bound));
	double m_original_upper, m_original_lower;
	m_original_upper = m_upper_bound;
	m_original_lower = m_lower_bound;
	double dummy_weight;
	HBTK::linear_remap(singularity_position, dummy_weight, m_lower_bound, m_upper_bound, -1., 1.);
	linear_remap(-1, 1);
	int size = num_points();
	for (int i = 0; i < size; i++) {
		HBTK::telles_cubic_remap(m_points[i], m_weights[i], singularity_position);
	}
	linear_remap(m_original_lower, m_original_upper);
	assert(HBTK::check_finite(m_points));
	assert(HBTK::check_finite(m_weights));
	return;
}

/// \param singularity_pos either upper of lower limit of integration.
///
/// \brief Applies Sato's 4th order remap to points and weights to adapt
/// for a singularity at singularity_position.
/// Sato's high order is an effective method for increasing the accuracy
/// of qaudratures with a singularity.
void HBTK::StaticQuadrature::sato4_remap(double singularity_position)
{
	assert(HBTK::check_finite(m_lower_bound));
	assert(HBTK::check_finite(m_upper_bound));
	assert((singularity_position == m_lower_bound) || (singularity_position == m_upper_bound));
	double m_original_upper, m_original_lower, remaped_sing_pos;
	m_original_upper = m_upper_bound;
	m_original_lower = m_lower_bound;
	remaped_sing_pos = (singularity_position == m_lower_bound ? -1 : 1);
	linear_remap(-1, 1);
	int size = num_points();
	for (int i = 0; i < size; i++) {
		HBTK::sato_remap<4, double>(m_points[i], m_weights[i], remaped_sing_pos);
	}
	linear_remap(m_original_lower, m_original_upper);
	assert(HBTK::check_finite(m_points));
	assert(HBTK::check_finite(m_weights));
	return;
}

/// \param singularity_pos either upper of lower limit of integration.
///
/// \brief Applies Sato's 5th order remap to points and weights to adapt
/// for a singularity at singularity_position.
/// Sato's high order is an effective method for increasing the accuracy
/// of qaudratures with a singularity. Less numerically safe than the 
/// 4th order remap, but may be more effective against stronger 
/// weak singularities.
void HBTK::StaticQuadrature::sato5_remap(double singularity_position)
{
	assert(HBTK::check_finite(m_lower_bound));
	assert(HBTK::check_finite(m_upper_bound));
	assert((singularity_position == m_lower_bound) || (singularity_position == m_upper_bound));
	double m_original_upper, m_original_lower, remaped_sing_pos;
	m_original_upper = m_upper_bound;
	m_original_lower = m_lower_bound;
	remaped_sing_pos = (singularity_position == m_lower_bound ? -1 : 1);
	linear_remap(-1, 1);
	int size = num_points();
	for (int i = 0; i < size; i++) {
		HBTK::sato_remap<5, double>(m_points[i], m_weights[i], remaped_sing_pos);
	}
	linear_remap(m_original_lower, m_original_upper);
	assert(HBTK::check_finite(m_points));
	assert(HBTK::check_finite(m_weights));
	return;
}
