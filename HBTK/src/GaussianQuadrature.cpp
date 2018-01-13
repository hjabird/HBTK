#include "stdafx.h"
#include "GaussianQuadrature.h"
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

#include <cassert>
#include "Generators.h"



std::tuple<std::vector<double>, std::vector<double>> HBTK::gauss_laguerre(int num_terms)
{
	assert(false); // This code is not ready for use yet.
	return generalised_gauss_laguerre(num_terms, 0.0);
}

std::tuple<std::vector<double>, std::vector<double>> HBTK::gauss_jacobi(int num_terms, double alpha, double beta)
{
	assert(false); // Untested. Not ready for use.
	assert(num_terms > 0);
	const int n = num_terms;
	auto A = [=](int k) {return 2 * k*(k + alpha + beta)*(2 * k + alpha + beta - 2); };
	auto B = [=](int k) {return 2 * k + alpha + beta - 1; };
	auto C = [=](int k) {return (2 * k + alpha + beta)*(2 * k + alpha + beta - 2); };
	auto D = [=](int k) {(void)k;  return alpha * alpha - beta * beta; };
	auto E = [=](int k) {return 2 * (k + alpha - 1)*(k + beta - 1)*(2 * k + alpha + beta); };

	auto a_i = [=](int k) {return B(k) * C(k) / A(k); };
	auto b_i = [=](int k) {return B(k) * D(k) / A(k); };
	auto c_i = [=](int k) {return E(k) / A(k); };
	return recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms);
}

std::tuple<std::vector<double>, std::vector<double>> HBTK::generalised_gauss_laguerre(int num_terms, double alpha)
{
	assert(false); // Yeilds incorrect result.
	assert(num_terms >= 0);
	auto a_i = [](int k)->double {return -1.0 / k; };
	auto b_i = [=](int k)->double {return 2 + (alpha - 1.0)/k; };
	auto c_i = [=](int k)->double {return 1 + (alpha - 1.0)/k; };

	auto return_value = recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms);
	return return_value;
}

std::tuple<std::vector<double>, std::vector<double>> HBTK::gauss_legendre_from_jacobi(int num_terms)
{
	assert(num_terms >= 0);
	auto a_i = [](int k)->double {return (2 * k - 1.0) / k; };
	auto b_i = [](int k)->double {(void)k; return 0.0; };
	auto c_i = [](int k)->double {return (k - 1.0) / k; };

	auto return_value = recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms);
	return return_value;
}

std::tuple<std::vector<double>, std::vector<double>> 
HBTK::recurrence_relation_to_quadrature(std::function<double(int)> a_i, 
	std::function<double(int)> b_i, 
	std::function<double(int)> c_i,
	int number_of_terms)
{
	assert(false); //Weight calculation is wrong - needs integral of 
	// weight function instead of just "2" (correct for Gauss Legendre).
	// Based on Golub & Welsch 1969.
	assert(number_of_terms > 0);
	std::vector<double> diagonal, off_diagonal;

	diagonal.resize(number_of_terms);
	off_diagonal.resize(number_of_terms - 1);

	for (int idx = 1; idx <= number_of_terms; idx++) {
		diagonal[idx - 1] = -b_i(idx) / a_i(idx);
	}
	for (int idx = 1; idx <= number_of_terms - 1; idx++) {
		off_diagonal[idx - 1] = sqrt(c_i(idx + 1) / (a_i(idx) * (a_i(idx + 1))));
	}
	auto result = jacobi_tridiagonal_to_quadrature(off_diagonal, diagonal);
	return result;
}


std::tuple<std::vector<double>, std::vector<double>> 
HBTK::jacobi_tridiagonal_to_quadrature(std::vector<double> off_diagonal, std::vector<double> diagonal)
{
	// The eigenvalues and eigenvectors of a jacobi matrix can be used to compute 
	// points and weights of a quadrature as per Golub & Welsch (1969). The methods
	// to compute the Eigen-X are a modifications of the tqli methods in Numerical
	// Recipes in C (first Ed). Modifications are made to so that only the first
	// value in the eigenvector is computed, and to correct errors (especially 
	// indexing) in Numerical Recipes.
	assert(off_diagonal.size() == diagonal.size() - 1);
	off_diagonal.push_back(0);

	std::vector<double> points, weights;
	points.resize(diagonal.size());
	weights.resize(diagonal.size());
	uniform(weights, 0.0);
	weights[0] = 1.0;

	double iterations, c, g, p, r, s;

	for (int i = 0; i < (int)diagonal.size(); i++) {
		iterations = 0;
		int m;

		do {
			for (m = i; m < (int)diagonal.size() - 1; m++) {
				double dd = abs(diagonal[m]) + abs(diagonal[m + 1]);
				if (abs(off_diagonal[m]) + dd == dd) break;
			}

			if (m != i) {
				g = (diagonal[i + 1] - diagonal[i]) / (2.0 * off_diagonal[i]);
				r = sqrt(g * g + 1.);
				g = diagonal[m] - diagonal[i] + off_diagonal[i] /
					(g + (g < 0 ? -abs(r) : abs(r)));
				s = 1.0;
				c = 1.0;
				p = 0.0;

				for (int j = m - 1; j >= i; j--) {
					double f = s * off_diagonal[j];
					double b = c * off_diagonal[j];

					if (abs(f) >= abs(g)) {
						c = g / f;
						r = sqrt((c*c) + 1.0);
						off_diagonal[j + 1] = f * r;
						s = 1.0 / r;
						c *= s;
					}
					else {
						s = f / g;
						r = sqrt((s*s) + 1.0);
						off_diagonal[j + 1] = g * r;
						c = 1.0 / r;
						s *= c;
					}

					g = diagonal[j + 1] - p;
					r = (diagonal[j] - g) * s + 2.0 * c * b;
					p = s * r;
					diagonal[j + 1] = g + p;
					g = c * r - b;

					// Compute the first value of the eigenvector.
					f = weights[j + 1];
					weights[j + 1] = s * weights[j] + c * f;
					weights[j] = c * weights[j] - s * f;
				} // End for(j >=1 )
				diagonal[i] = diagonal[i] - p;
				off_diagonal[i] = g;
				off_diagonal[m] = 0.0;
			} // End if(m != 1)
		} while (m != i);
	} // End for (idx)

	points = diagonal;
	// Compute the actual weights from the first of the eigenvectors.
	std::transform(weights.begin(), weights.end(), weights.begin(),
		[](double w_i)->double { return 2 * w_i * w_i; });
	return std::make_tuple(points, weights);
}
