#include "ConformalMapping.h"
/*////////////////////////////////////////////////////////////////////////////
ConformalMapping.cpp

Conformal mappings.

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

#include "Constants.h"

std::complex<double> HBTK::joukowsky_transform(std::complex<double> zeta_point)
{
	return zeta_point + 1.0 / zeta_point;
}

std::complex<double> HBTK::joukowsky_transform_derivative(std::complex<double> zeta_point)
{
	return 1.0 - 1.0 / (zeta_point * zeta_point);
}

std::complex<double> HBTK::karman_trefftz_transform(std::complex<double> zeta_point, double alpha)
{
	double n = 2 - alpha / HBTK::Constants::pi();
	std::complex<double> plus, minus;
	plus = 1. + 1. / zeta_point;
	minus = 1. - 1. / zeta_point;
	return n * (pow(plus, n) + pow(minus, n)) / (pow(plus, n) - pow(minus, n));
}

std::complex<double> HBTK::karman_trefftz_transform_derivative(std::complex<double> zeta_point, double alpha)
{
	double n = 2 - alpha / HBTK::Constants::pi();
	std::complex<double> plus, minus;
	plus = 1. + 1. / zeta_point;
	minus = 1. - 1. / zeta_point;
	return 4. * n  * n * (pow(plus, n) * pow(minus, n)) / 
		(pow(pow(plus, n) - pow(minus, n), 2) * (zeta_point*zeta_point - 1.0));
}

