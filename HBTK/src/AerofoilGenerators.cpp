#include "AerofoilGenerators.h"
/*////////////////////////////////////////////////////////////////////////////
AerofoilGenerators.cpp

Routines to generate aerofoil geometries.

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

#include "AerofoilGeometry.h"
#include "Checks.h"
#include "Constants.h"
#include "Generators.h"

HBTK::AerofoilGeometry HBTK::AerofoilGenerators::joukowsky(double thickness, double camber)
{
	assert(thickness > 0);
	assert(HBTK::check_finite(thickness));
	assert(HBTK::check_finite(camber));

	std::vector<double> theta_points = HBTK::linspace(0, HBTK::Constants::pi(), 50);
	std::vector<double> x_points(theta_points.size()), z_points(theta_points.size());
	// Generate a circle on the complex plane in correct position...
	for (int i = 0; i < (int)z_points.size(); i++) {
		std::complex<double> circ_point = 0;
		x_points[i] = (1 + cos(theta_points[i])) / 2;
		z_points[i] = sin(theta_points[i]);
	}
	// And transform it to the aerofoil plane:
	// UNFINISHED.
	assert(false);
	return AerofoilGeometry();
}

HBTK::AerofoilGeometry HBTK::AerofoilGenerators::naca_four_digit(double thickness, double camber, double camber_position)
{
	assert(thickness > 0);
	assert(HBTK::check_finite(thickness));
	assert(HBTK::check_finite(camber));
	assert(camber_position > 0);
	assert(camber_position < 1);

	double & m = camber;
	double & p = camber_position;
	// Thickness distribution function (all from Abbott and Doenhoff):
	auto thick_fn = [=](double x)->double {
		return 5 * thickness *(
			0.29690 * sqrt(x)
			- 0.12600 * x
			- 0.35160 * x * x
			+ 0.28430 * x * x * x
			- 0.10150 * x * x * x * x
			);
	};
	// The camber is 
	auto mean_ln_fwd_fn = [=](double x)->double {
		return (m / (p * p)) * (2 * p * x - x * x);
	};
	// forward of the max camber and 
	auto mean_ln_rear_fn = [=](double x)->double {
		return (m / ((1 - p)*(1 - p))) * ((1 - 2 * p) + 2 * p * x - x * x);
	}; // behind the max ordinate, which are combined:
	auto mean_ln_fn = [&](double x)->double {
		return (x < p ? mean_ln_fwd_fn(x) : mean_ln_rear_fn(x));
	};

	std::vector<double> x_points = HBTK::linspace(0, HBTK::Constants::pi(), 30);
	for (auto & point : x_points) point = (1 - cos(point)) / 2;

	AerofoilGeometry foil;
	foil.add_thickness(thick_fn);
	foil.add_camber(mean_ln_fn);

	return foil;
}
