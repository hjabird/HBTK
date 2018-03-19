#pragma once
/*////////////////////////////////////////////////////////////////////////////
AerofoilGenerators.h

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

#include <string>

#include "AerofoilGeometry.h"

namespace HBTK {
	namespace AerofoilGenerators {

		// UNFINISHED!
		AerofoilGeometry joukowsky(double thickness, double camber);

		// AerofoilGeometry karman_trefftz(double thickness, double camber, double te_angle);

		// Generate a NACA 4 digit aerofoil. NACA<MPTT> where M is camber as percent of chord,
		// P is camber_position as per dec (ie 10pc) of chord and TT is max thickness as 
		// percent of chord.
		AerofoilGeometry naca_four_digit(double thickness, double camber, double camber_position);
		AerofoilGeometry naca_four_digit(std::string name);
	}
}
