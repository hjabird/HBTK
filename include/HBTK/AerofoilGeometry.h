#pragma once
/*////////////////////////////////////////////////////////////////////////////
AerofoilGeometry.h

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

#include <functional>
#include <vector>

#include "CubicSpline1D.h"

namespace HBTK {
	class AerofoilGeometry {
	public:
		AerofoilGeometry();

		// Construct an aerofoil from a preexisting set of points - 
		// it is assumed that x: 1(TE) -> 0(LE) -> 1(TE) and
		// y is top surface first.
		AerofoilGeometry(const std::vector<double> & x_points, 
			const std::vector<double> & z_points);
		~AerofoilGeometry();

		// Define the points of an aerofoil.
		void set(const std::vector<double> & x_points,
			const std::vector<double> & z_points);

		// Add camber to the aerofoil using a function defined for 
		// x = [0,1]. Camber must be 0 at both LE and TE.
		void add_camber(std::function<double(double)> function);

		// Add thickness to the aerofoil using a function defined for 
		// x = [0,1]. Camber must be 0 at both LE. 
		void add_thickness(std::function<double(double)> function);

		// Returns a spline representing the thickness along the 
		// length of the aerofoil. 0->LE, 1->TE.
		CubicSpline1D get_thickness_spline();

		// Returns a spline representing the thickness along the 
		// length of the aerofoil. 0->LE, 1->TE.
		CubicSpline1D get_camber_spline();

		// Get the aerofoil points representing the upper and lower surfaces.
		// For only upper and lower, the (0,0) point may be added as needs be.
		std::vector<double> x_upper();
		std::vector<double> x_lower();
		std::vector<double> z_upper();
		std::vector<double> z_lower();
		std::vector<double> x_all();
		std::vector<double> z_all();

		// The gap at the tailing edge between the upper and lower surface.
		double tailing_edge_gap();

		// Reposition the points used to define the foil by interpolating the y
		// positions for a new X distribution. The function "function" maps
		// a equally space set of points from 0-1 to 0-1 as desired by the user
		// for given "number_of_points"
		void repoint(std::function<double(double)> function, int number_of_points);

	protected:
		// The coordinates that define the aerofoil. Stored as x=0 -> x=1
		std::vector<double> m_x_points_upper, m_x_points_lower;
		std::vector<double> m_z_points_upper, m_z_points_lower;

		// Copy an input, adding a zero to the beginning of a vector if not already 
		// there.
		std::vector<double> return_points_with_first_zero(std::vector<double> & input);
	};
}
