#include "AerofoilGeometry.h"
/*////////////////////////////////////////////////////////////////////////////
AerofoilGeometry.cpp

An object to represent a vanilla aerofoil. The aerofoil is represented by
a set of points that are interpolated to obtain a surface. The x coordinates
of the aerofoil are in [0, 1], with x=0 as the leading edge.

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

#include <algorithm>
#include <iterator>

#include "Constants.h"
#include "Generators.h"

HBTK::AerofoilGeometry::AerofoilGeometry()
	: m_x_points_lower(25),
	m_x_points_upper(25),
	m_z_points_lower(25),
	m_z_points_upper(25)
{
	auto x_dist = [](double x)->double { 
		return 0.5 * (1 - cos(HBTK::Constants::pi() * x));
	};
	auto linear_dist = HBTK::linspace(0, 1, 25);

	for (int i = 0; i < 25; i++) {
		m_x_points_lower[i] = m_x_points_upper[i]
			= x_dist(linear_dist[i]);
		m_z_points_lower[i] = m_z_points_upper[i] = 0;
	}
	return;
}

HBTK::AerofoilGeometry::AerofoilGeometry(const std::vector<double> & x_points, 
	const std::vector<double> & z_points)
{
	assert(x_points.size() == z_points.size());
	double last_x_point;
	int split_point;

	last_x_point = 1.1;
	for (int i = 0; i < (int)x_points.size(); i++) {
		if (x_points[i] > last_x_point) {
			split_point = i;
			break;
		}
		last_x_point = x_points[i];
	}
	assert(i < (int)x_points.size());

	m_x_points_upper.resize(split_point);
	m_x_points_lower.resize(x_points.size() - split_point);
	m_z_points_upper.resize(split_point);
	m_x_points_lower.resize(x_points.size() - split_point);

	int j;
	for (j = 0; j < split_point; j++) {
		m_x_points_upper[split_point - j - 1] = x_points[j];
		m_z_points_upper[split_point - j - 1] = z_points[j];
	}
	for (; j < (int)x_points.size(); j++) {
		m_x_points_lower[j - split_point] = x_points[j];
		m_z_points_lower[j - split_point] = z_points[j];
	}
}

HBTK::AerofoilGeometry::~AerofoilGeometry()
{
}

void HBTK::AerofoilGeometry::set(const std::vector<double>& x_points, const std::vector<double>& z_points)
{
	AerofoilGeometry new_foil(x_points, z_points);
	*this = new_foil;
}

void HBTK::AerofoilGeometry::add_camber(std::function<double(double)> function)
{
	assert(function);
	if (function(0) != 0) {
		throw std::range_error("HTBK::AerofoilGeometry.add_camber(std::function)"
			" given function f does not evaluate to zero at leading edge (f(0) != 0). "
			__FILE__ ":" + std::to_string(__LINE__));
	}
	if (function(1) != 0) {
		throw std::range_error("HTBK::AerofoilGeometry.add_camber(std::function)"
			" given function f does not evaluate to zero at trailing edge (f(1) != 0). "
			__FILE__ ":" + std::to_string(__LINE__));
	}

	for (int i = 0; i < (int) m_x_points_lower.size(); i++) {
		m_z_points_lower[i] += function(m_x_points_lower[i]);
	}
	for (int i = 0; i < (int) m_x_points_lower.size(); i++) {
		m_z_points_upper[i] += function(m_x_points_upper[i]);
	}

	assert(HBTK::check_finite(m_z_points_upper));
	assert(HBTK::check_finite(m_z_points_lower));
}

void HBTK::AerofoilGeometry::add_thickness(std::function<double(double)> function)
{
	assert(function);
	if (function(0) != 0) {
		throw std::range_error("HTBK::AerofoilGeometry.add_thickness(std::function)"
			" given function f does not evaluate to zero at leading edge (f(0) != 0). "
			__FILE__ ":" + std::to_string(__LINE__));
	}

	for (int i = 0; i < (int) m_x_points_lower.size(); i++) {
		m_z_points_lower[i] -= function(m_x_points_lower[i]) / 2;
	}
	for (int i = 0; i < (int) m_x_points_lower.size(); i++) {
		m_z_points_upper[i] += function(m_x_points_upper[i]) / 2;
	}

	assert(HBTK::check_finite(m_z_points_upper));
	assert(HBTK::check_finite(m_z_points_lower));
}

HBTK::CubicSpline1D HBTK::AerofoilGeometry::get_thickness_spline()
{
	if (m_x_points_upper != m_x_points_lower) {
		AerofoilGeometry new_foil;
		new_foil.repoint(
			[](double x)->double { return 0.5 * (1 - cos(x * HBTK::Constants::pi()));}
			, std::max({ m_x_points_upper.size(), m_x_points_lower.size() })
			);
		return new_foil.get_thickness_spline();
	}
	else {
		std::vector<double> thickness(m_x_points_upper.size());
		for (int i = 0; i < (int) m_x_points_upper.size(); i++) {
			thickness[i] = m_z_points_upper[i] - m_z_points_lower[i];
		}
		return CubicSpline1D(m_x_points_lower, thickness);
	}
}

HBTK::CubicSpline1D HBTK::AerofoilGeometry::get_camber_spline()
{
	if (m_x_points_upper != m_x_points_lower) {
		AerofoilGeometry new_foil;
		new_foil.repoint(
			[](double x)->double { return 0.5 * (1 - cos(x * HBTK::Constants::pi())); }
			, std::max({ m_x_points_upper.size(), m_x_points_lower.size() })
		);
		return new_foil.get_thickness_spline();
	}
	else {
		std::vector<double> thickness(m_x_points_upper.size());
		for (int i = 0; i < (int) m_x_points_upper.size(); i++) {
			thickness[i] = (m_z_points_upper[i] + m_z_points_lower[i]) / 2;
		}
		return CubicSpline1D(m_x_points_lower, thickness);
	}
}

std::vector<double> HBTK::AerofoilGeometry::x_upper()
{
	return return_points_with_first_zero(m_x_points_upper);
}

std::vector<double> HBTK::AerofoilGeometry::x_lower()
{
	return return_points_with_first_zero(m_x_points_lower);
}

std::vector<double> HBTK::AerofoilGeometry::z_upper()
{
	auto points = return_points_with_first_zero(m_z_points_upper);
	if (m_x_points_upper[0] != 0) {
		points.insert(points.begin(), 0);
	}
	return points;
}

std::vector<double> HBTK::AerofoilGeometry::z_lower()
{
	auto points = return_points_with_first_zero(m_z_points_lower);
	if (m_x_points_lower[0] != 0) {
		points.insert(points.begin(), 0);
	}
	return points;
}

std::vector<double> HBTK::AerofoilGeometry::x_all()
{
	auto upper = m_x_points_upper;
	std::reverse(upper.begin(), upper.end());
	upper.insert(upper.end(), m_x_points_lower.begin(), m_x_points_lower.end());
	return upper;
}

std::vector<double> HBTK::AerofoilGeometry::z_all()
{
	auto upper = m_z_points_upper;
	std::reverse(upper.begin(), upper.end());
	upper.insert(upper.end(), m_x_points_lower.begin(), m_z_points_lower.end());
	return upper;
}

double HBTK::AerofoilGeometry::tailing_edge_gap()
{
	assert(m_x_points_upper.back() == 1);
	assert(m_x_points_lower.back() == 1);

	double gap = m_z_points_upper.back() - m_z_points_lower.back();
	assert(gap >= 0);
	assert(HBTK::check_finite(gap));
	return gap;
}

void HBTK::AerofoilGeometry::repoint(std::function<double(double)> function, int number_of_points)
{
	std::vector<double> points = linspace(0, 1, number_of_points);
	assert(false);
	return;
}

std::vector<double> HBTK::AerofoilGeometry::return_points_with_first_zero(std::vector<double> & input)
{
	int size = input.size();
	if (input[0] != 0) { size += 1; }
	std::vector<double> output;
	if (input[0] != 0) {
		output.emplace_back(0);
		std::copy(input.begin(), input.end(),
			std::back_inserter(output));
	}
	assert(HBTK::check_finite(output));
	return output;
}
