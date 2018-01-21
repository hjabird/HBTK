#pragma once
/*////////////////////////////////////////////////////////////////////////////
GaussianQuadratures.h

Generates Gaussian quadratures.

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

#include <vector>
#include <tuple>
#include <functional>
// It'd be confusing if including Gauss quadrature did not include Gauss_Legendre.
#include "GaussLegendre.h"

namespace HBTK {
	std::tuple<std::vector<double>, std::vector<double>>
		gauss_laguerre(int num_terms);

	std::tuple<std::vector<double>, std::vector<double>>
		gauss_jacobi(int num_terms, double alpha, double beta);

	std::tuple<std::vector<double>, std::vector<double>>
		generalised_gauss_laguerre(int num_terms, double alpha);

	std::tuple<std::vector<double>, std::vector<double>>
		gauss_legendre_from_jacobi(int num_terms);

	std::tuple<std::vector<double>, std::vector<double>>
		recurrence_relation_to_quadrature(
			std::function<double(int)> a_i,
			std::function<double(int)> b_i,
			std::function<double(int)> c_i,
			int number_of_terms, double domain_weight_integral);


	// Compute a Gauss quadrature from a Jacobi matrix.
	static std::tuple<std::vector<double>, std::vector<double>>
		jacobi_tridiagonal_to_quadrature(std::vector<double> off_diagonal, std::vector<double> diagonal);

	// Compute the integral of a jacobi polynomial 
	// (1-x)^alpha (1+x)^beta
	// Only works for some inputs:
	// alpha or beta is integer and the other if negitive has greater magnitude.
	// If alpha==beta, n/2 where n is integer >= -1
	static double jacobi_integral(double alpha, double beta);
}