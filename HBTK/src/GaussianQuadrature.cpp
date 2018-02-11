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

#include <algorithm>
#include <cassert>

#include "Generators.h"

HBTK::StaticQuadrature HBTK::gauss_laguerre(int num_terms)
{
	return gauss_generalised_laguerre(num_terms, 0.0);
}

HBTK::StaticQuadrature HBTK::gauss_hermite(int num_terms)
{
	assert(num_terms >= 0);
	auto a_i = [=](int k)->double {(void)k;  return 2; };
	auto b_i = [=](int k)->double {(void)k; return 0; };
	auto c_i = [=](int k)->double {return 2 * (k - 1); };

	auto return_value = recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms, sqrt(HBTK::Constants::pi()));
	return StaticQuadrature(std::get<0>(return_value), std::get<1>(return_value),
		-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
}

HBTK::StaticQuadrature HBTK::gauss_chebyshev1(int num_terms)
{
	assert(num_terms >= 0);
	auto a_i = [=](int k)->double {(void)k; return 2; };
	auto b_i = [=](int k)->double {(void)k; return 0; };
	auto c_i = [=](int k)->double {(void)k; return 1; };

	auto return_value = recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms, HBTK::Constants::pi());
	return StaticQuadrature(std::get<0>(return_value), std::get<1>(return_value), -1, 1);
}

HBTK::StaticQuadrature HBTK::gauss_chebyshev2(int num_terms)
{
	assert(num_terms >= 0);
	auto a_i = [=](int k)->double {return (2 * k + 2) / (k + 1); };
	auto b_i = [=](int k)->double {(void)k; return 0; };
	auto c_i = [=](int k)->double {(void)k; return 1; };

	auto return_value = recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms, HBTK::Constants::pi()/2);
	return StaticQuadrature(std::get<0>(return_value), std::get<1>(return_value), -1, 1);
}

HBTK::StaticQuadrature HBTK::gauss_gegenbauer(int num_terms, double alpha)
{
	return gauss_jacobi(num_terms, alpha, alpha);
}

HBTK::StaticQuadrature HBTK::gauss_jacobi(int num_terms, double alpha, double beta)
{
	assert(num_terms > 0);
	const int n = num_terms;
	// Recurrence relation is taken from Wikipedia and valid for k >= 2.
	auto A = [=](int k) {return 2 * k*(k + alpha + beta)*(2 * k + alpha + beta - 2); };
	auto B = [=](int k) {return 2 * k + alpha + beta - 1; };
	auto C = [=](int k) {return (2 * k + alpha + beta)*(2 * k + alpha + beta - 2); };
	auto D = [=](int k) {(void)k;  return alpha * alpha - beta * beta; };
	auto E = [=](int k) {return 2 * (k + alpha - 1)*(k + beta - 1)*(2 * k + alpha + beta); };

	auto a_i = [=](int k) {return B(k) * C(k) / A(k); }; // On k = 1, we get a problem with zeros..
	auto b_i = [=](int k) {return B(k) * D(k) / A(k); };
	auto c_i = [=](int k) {return E(k) / A(k); };
	return recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms, jacobi_integral(alpha, beta));
}

HBTK::StaticQuadrature HBTK::gauss_generalised_laguerre(int num_terms, double alpha)
{
	assert(num_terms >= 0);
	assert(alpha > -1);
	auto a_i = [=](int k)->double {return -1.0 / k; };
	auto b_i = [=](int k)->double {return 2 + (alpha - 1.0)/k; };
	auto c_i = [=](int k)->double {return 1 + (alpha - 1.0)/k; };

	auto return_value = recurrence_relation_to_quadrature(a_i, b_i, c_i, num_terms, std::tgamma(alpha + 1));
	return StaticQuadrature(std::get<0>(return_value), std::get<1>(return_value), 
		0, std::numeric_limits<double>::infinity());
}

std::tuple<std::vector<double>, std::vector<double>> 
HBTK::recurrence_relation_to_quadrature(std::function<double(int)> a_i,
	std::function<double(int)> b_i,
	std::function<double(int)> c_i,
	int number_of_terms, double domain_weight_integral)
{
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
	assert(HBTK::check_finite(diagonal));
	assert(HBTK::check_finite(off_diagonal));
	auto result = jacobi_tridiagonal_to_quadrature(off_diagonal, diagonal);
	std::transform(std::get<1>(result).begin(), std::get<1>(result).end(), std::get<1>(result).begin(),
		[=](double w_i)->double { return domain_weight_integral * w_i * w_i; });
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
	// Outputs points and almost_weights
	// So called almost_weights because they need to be multiplied by the integral 
	// of the wieght funtion over the orthogonality domain.

	assert(off_diagonal.size() == diagonal.size() - 1);
	off_diagonal.push_back(0);

	std::vector<double> points, almost_weights;
	points.resize(diagonal.size());
	almost_weights.resize(diagonal.size());
	uniform(almost_weights, 0.0);
	almost_weights[0] = 1.0;

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
					f = almost_weights[j + 1];
					almost_weights[j + 1] = s * almost_weights[j] + c * f;
					almost_weights[j] = c * almost_weights[j] - s * f;
				} // End for(j >=1 )
				diagonal[i] = diagonal[i] - p;
				off_diagonal[i] = g;
				off_diagonal[m] = 0.0;
			} // End if(m != 1)
		} while (m != i);
	} // End for (idx)

	points = diagonal;
	// Compute the actual weights from the first of the eigenvectors.
	return std::make_tuple(points, almost_weights);
}

double HBTK::jacobi_integral(double alpha, double beta)
{
	auto fact = [](int n)->int {
		assert(n >= 0);
		int f = 1;
		for (int i = 2; i <= n; i++) { f *= i; }
		return f;
	};

	double result = 0;
	if (std::round(alpha) == alpha) {
		if (beta < 0) { assert(-beta > alpha); }
		result = fact((int)alpha) * pow(2, alpha + beta + 1) / (alpha + beta + 1);
		for (int n = 1; n <= alpha; n++) result /= beta + n;
	}
	else if (std::round(beta) == beta) {
		if (alpha < 0) { assert(-alpha > beta); }
		result = fact((int)beta) * pow(2, alpha + beta + 1) / (alpha + beta + 1);
		for (int n = 1; n <= beta; n++) result /= alpha + n;
	}
	else if ((alpha == beta) && (std::round(alpha * 2) == alpha * 2)) {
		assert(alpha > -1);
		if (alpha == -0.5) { result = HBTK::Constants::pi(); }
		else {
			int n = (int)(2 * alpha); // Should be an int anyway.
			result = HBTK::Constants::pi() * fact(n) / 
				(fact((n + 1) / 2) * fact((n - 1) / 2) * pow(2, n));
		}
	}
	else if (alpha == -beta) {
		if (abs(alpha) == 0.5) { result = HBTK::Constants::pi(); }
		else { assert(false); }
	}
	else { assert(false); } // Perhaps numerically integrate?
	return result;
}
