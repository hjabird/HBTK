#include "CubicSpline1D.h"
/*////////////////////////////////////////////////////////////////////////////
CubicSpline1D.cpp

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

#include <cassert>

void HBTK::CubicSpline1D::compute_second_derivatives()
{
	// Based on Numerical Recipes in C "spline" routine.
	assert(m_point_locations.size() == m_point_values.size());
	for (int i = 0; i < (int) m_point_locations.size() - 1; i++) {
		assert(m_point_locations[i] < m_point_locations[i + 1]);
	}
	// Alius variable names for convenience:
	std::vector<double> & x = m_point_locations;
	std::vector<double> & y = m_point_values;
	std::vector<double> & yd2 = m_second_derivatives;

	const int n = (int)m_point_locations.size();
	yd2.resize(n);
	std::vector<double> u(n);
	double qn, un;

	if (m_natural_bc_x0) { yd2[0] = u[0] = 0.0; }
	else { 
		yd2[0] = -0.5;
		u[0] = (3. / (x[1] - x[0])) * ((y[1] - y[0]) / (x[1] - x[0]) - m_derivative_x0);
	}
	for (int i = 1; i < n - 1; i++) {
		double sig = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
		double p = sig * yd2[i - 1] + 2.0;
		yd2[i] = (sig - 1.0) / p;
		u[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) 
			- (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
		u[i] = (6.0 * u[i] / (x[i + 1] - x[i - 1]) - sig * u[i - 1]) / p;
	}
	if (m_natural_bc_xn) {
		qn = un = 0.0;
	}
	else{
		qn = 0.5;
		un = (3.0 / (x[n - 1] - x[n - 2])) * (m_derivative_xn - (y[n - 1] - y[n - 2])
			/ (x[n - 1] - x[n - 2]));
	}

	yd2.back() = (un - qn * u[n - 2]) / (qn * yd2[n - 2] + 1.0);
	for (int i = n - 2; i >= 0; i--) {
		yd2[i] = yd2[i] * yd2[i + 1] + u[i];
	}
	m_derivatives_computed = true;
	return;
}

void HBTK::CubicSpline1D::check_computed_blocking()
{
	bool checking_mutex = true;
	while (checking_mutex) {
		if (m_derivatives_computed) break;
		if (m_deriv_compute_mutex.try_lock()) {
			compute_second_derivatives();
			m_deriv_compute_mutex.unlock();
		}
	}
	return;
}

HBTK::CubicSpline1D::CubicSpline1D(std::vector<double> point_locations, 
	std::vector<double> point_values, double derivative_x0, double derivative_xn)
	: m_natural_bc_x0(false),
	m_natural_bc_xn(false),
	m_point_locations(point_locations),
	m_point_values(point_values),
	m_derivative_x0(derivative_x0),
	m_derivative_xn(derivative_xn),
	m_derivatives_computed(false)
{
}

HBTK::CubicSpline1D::CubicSpline1D(std::vector<double> point_locations, std::vector<double> point_values, double derivative_x0)
	: m_natural_bc_x0(false),
	m_natural_bc_xn(true),
	m_point_locations(point_locations),
	m_point_values(point_values),
	m_derivative_x0(derivative_x0),
	m_derivatives_computed(false)
{
}

HBTK::CubicSpline1D::CubicSpline1D(std::vector<double> point_locations, std::vector<double> point_values)
	: m_natural_bc_x0(true),
	m_natural_bc_xn(true),
	m_point_locations(point_locations),
	m_point_values(point_values),
	m_derivatives_computed(false)
{
}

HBTK::CubicSpline1D::CubicSpline1D(const CubicSpline1D & other)
	: m_natural_bc_x0(other.m_natural_bc_x0),
	m_natural_bc_xn(other.m_natural_bc_xn),
	m_point_locations(other.m_point_locations),
	m_point_values(other.m_point_values),
	m_derivative_x0(other.m_derivative_x0),
	m_derivative_xn(other.m_derivative_xn),
	m_derivatives_computed(other.m_derivatives_computed)
{
}

HBTK::CubicSpline1D::~CubicSpline1D()
{
}

double HBTK::CubicSpline1D::operator()(double location)
{
	return evaluate(location);
}

double HBTK::CubicSpline1D::evaluate(double location)
{
	check_computed_blocking();
	int klo, khi, k;
	double h, b, a, y;

	// Bracketing of k in m_point_location
	klo = 1;
	khi = (int) m_point_locations.size();
	while (khi - klo > 1) {
		k = (khi + klo) >> 1;
		if (m_point_locations[k] > location) { khi = k; }
		else { klo = k; }
	}
	// And compute our position on the spline.
	h = m_point_locations[khi] - m_point_locations[klo];
	a = (m_point_locations[khi] - location) / h;
	b = (location - m_point_locations[klo]) / h;
	y = a * m_point_values[klo] + b * m_point_values[khi]
		+ ((a * a * a - a) * m_second_derivatives[klo]
			+ (b * b * b - b) * m_second_derivatives[khi])
		* (h * h) / 6.0;
	return y;
}

double HBTK::CubicSpline1D::derivative(double location)
{
	// Differentiated from above.
	check_computed_blocking();
	int klo, khi, k;
	double h, a, b, da, db, y;

	// Bracketing of k in m_point_location
	klo = 1;
	khi = (int)m_point_locations.size();
	while (khi - klo > 1) {
		k = (khi + klo) >> 1;
		if (m_point_locations[k] > location) { khi = k; }
		else { klo = k; }
	}
	// And compute our position on the spline.
	h = m_point_locations[khi] - m_point_locations[klo];
	da = -1 / h;
	db = 1 / h;
	a = (m_point_locations[khi] - location) / h;
	b = (location - m_point_locations[klo]) / h;
	y = da * m_point_values[klo] + db * m_point_values[khi]
		+ (da * (3 * a * a  - 1) * m_second_derivatives[klo]
			+ db * (3 * b * b - b) * m_second_derivatives[khi])
		* (h * h) / 6.0;
	return y;
}

double HBTK::CubicSpline1D::lower_input_bound()
{
	return m_point_locations[0];
}

double HBTK::CubicSpline1D::upper_input_bound()
{
	return m_point_locations.back();
}
