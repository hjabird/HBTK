#include "PotentialFlowDistributions.h"
/*////////////////////////////////////////////////////////////////////////////
PotentialFlowDistributions.cpp

Defines basic potential flow distributions.

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

#include "CartesianVector.h"
#include "Constants.h"

HBTK::CartesianVector3D HBTK::BiotSavart::unity_vel(CartesianPoint3D & mes_point, CartesianLine3D & filament)
{
	// See Katz & Plotkin ~pg 36, ~pg 255 (sec. 10.4.5)
	CartesianVector3D r0(filament.vector());
	CartesianVector3D r1(mes_point - filament.start);
	CartesianVector3D r2(mes_point - filament.end);

	double r1l = r1.length();
	double r2l = r2.length();
	double global_denominator = 4 * HBTK::Constants::pi() * pow(abs(r1.cross(r2)), 2);

	double r1c = r0.dot(r1) / r1l;
	double r2c = r0.dot(r2) / r2l;
	double K = (r1c + r2c) / global_denominator;
	CartesianVector3D output = r1.cross(r2) * K;
	return output;
}
