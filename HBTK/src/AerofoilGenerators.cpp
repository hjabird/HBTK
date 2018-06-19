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
#include <cmath>

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
	assert((camber_position > 0) || (camber == 0));
	assert(camber_position < 1);

	double & m = camber;
	double & p = camber_position;
	// Thickness distribution function (all from Abbott and Doenhoff):
	auto thick_fn = [=](double x)->double {
		return 10 * thickness *(
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

HBTK::AerofoilGeometry HBTK::AerofoilGenerators::naca_four_digit(std::string name)
{
	double thick, camber, camber_pos;
	if ((int)name.size() != 4) {
		throw std::runtime_error(
			"HBTK::AerofoilGenerators::naca_four_digit Bad aerofoil name: "
			+ name + ". Expected four digits CPTT where C is camber(pc),"
			" P is max camber position (10ths of chord) and TT is thickness"
			"(pc). " __FILE__ + " : " + std::to_string(__LINE__));
	}
	camber = name[0] - '0';
	camber_pos =name[1] - '0';
	thick = std::stod(name.substr(2, 4));
	thick /= 100;
	camber /= 100;
	camber_pos /= 10;
	return naca_four_digit(thick, camber, camber_pos);
}

HBTK::AerofoilGeometry HBTK::AerofoilGenerators::sd7003(void)
{
	// Coordinates taken from 
	// http://airfoiltools.com/airfoil/details?airfoil=sd7003-il
	std::vector<double> x, z;
	x = { 1, 0.99681, 0.98745, 0.97235, 0.95193, 0.92639, 0.896,
		0.86112, 0.82224, 0.77985, 0.73449, 0.68673, 0.63717,
		0.58641, 0.53499, 0.4835, 0.43249, 0.3825, 0.33405,
		0.2876, 0.24358, 0.2024, 0.16442, 0.12993, 0.09921,
		0.07244, 0.04978, 0.0313, 0.01702, 0.00697, 0.00127,
		0.00025, 0.00457, 0.01408, 0.02839, 0.04763, 0.07182,
		0.10073, 0.13407, 0.1715, 0.21268, 0.25719, 0.30456,
		0.35426, 0.40572, 0.45837, 0.51161, 0.56484, 0.61748,
		0.66898, 0.71883, 0.76644, 0.81118, 0.85241, 0.88957,
		0.9221, 0.94952, 0.97134, 0.98718, 0.99679, 1.00001 };
	z = { 0, 0.00031, 0.00132, 0.0031, 0.00547, 0.00824, 0.01139,
		0.01494, 0.01884, 0.02304, 0.02744, 0.03197, 0.03649,
		0.04086, 0.04494, 0.04859, 0.05171, 0.05415, 0.05581,
		0.05658, 0.05639, 0.05518, 0.05292, 0.04961, 0.04526,
		0.03993, 0.03372, 0.02677, 0.01932, 0.01172, 0.00438,
		-0.00186, -0.00741, -0.01285, -0.01759, -0.02141,
		-0.02438, -0.0266, -0.02809, -0.02888, -0.029, -0.02852,
		-0.02752, -0.02608, -0.02428, -0.02217, -0.0198, -0.01723,
		-0.0145, -0.01167, -0.00887, -0.00628, -0.00403, -0.0022,
		-0.00082, 0.00008, 0.00052, 0.00057, 0.00037, 0.00011, 0 };

	return AerofoilGeometry(x, z);
}
