#pragma once
/*////////////////////////////////////////////////////////////////////////////
GaussLegendre.h

Generates Gauss-Legendre quadratures.

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

#include <cmath>
#include <array>
#include <vector>
#include "Constants.h"
#include "Tolerances.h"

namespace HBTK {

	// DECLARATIONS

	std::pair<std::vector<double>, std::vector<double>> gauss_legendre(int n_points);

	template <typename Ty, typename TyStor>
	constexpr void gauss_legendre(int n_points, TyStor & points, 
												TyStor & weights);

	template <int n_points, typename Ty>
	constexpr void gauss_legendre(std::array<Ty, n_points> & points, 
								  std::array<Ty, n_points> & weights);


	// DEFINITIONS

	/// \param n_points number of guass points desired
	/// \param points an indexable container of Ty - 
	/// Gauss points written here
	/// \param weights an indexable container of Ty -  
	/// Weights of points written here
	///
	/// \brief generate gauss legendre quadrature
	///
	/// Generates points and weights for a gauss legendre quadrature.
	/// \code
	/// std::vector<double> points, weights;
	/// points.resize(3);
	/// weights.resize(3);
	/// HBTK::gauss_legendre<double>(3, points, weights);
	/// \endcode 
	/// points and weights now contain the coordinates and weights of a 
	/// GL quadrature.
	/// Not it is the responsibiltiy of the user to ensure the containers
	/// are large enough.
	/// 
	/// It may be that points and weights are different but can be cast 
	/// to an appropriate type.
	/// \code
	/// My_typeA points;
	/// My_typeB weights;
	/// HBTK::gauss_legendre<double, My_typeA>(3, points, weights);
	/// \endcode which is equivalent to \code
	/// HBTK::gauss_legendre<double>(3, points, (My_typeB) weights);
	/// \endcode
	template <typename Ty, typename TyStor>
	constexpr void gauss_legendre(int n_points, TyStor & points, 
												TyStor & weights) 
	{
		Ty m;
		Ty z, z1;
		Ty p1, p2, p3, pp;
		int idxO, idxI;

#pragma warning(suppress: 4244)
		m = (n_points + 1.0) / 2.0;

		for (idxO = 0; idxO < floor(m - 1) + 1; idxO++)
		{
#pragma warning(suppress: 4244)
			z = cos(HBTK::Constants::pi<Ty>() * (idxO + 0.75) / (n_points + 0.5));
			z1 = 12;
			while (abs(z - z1) > HBTK::tolerance<Ty>()) {
				p1 = 1;
				p2 = 0;
				for (idxI = 0; idxI < n_points; idxI++)
				{
					p3 = p2;	p2 = p1;
					p1 = ((2 * idxI + 1)*z*p2 - idxI*p3) / (idxI + 1);
				}
				pp = n_points *(z*p1 - p2) / (z*z - 1);
				z1 = z;
				z = z1 - p1 / pp;
			}
			points[idxO] = z;
			points[n_points - idxO - 1] = -z;
			weights[idxO] = 2 / ((1 - z*z)*pp*pp);
			weights[n_points - idxO - 1] = weights[idxO];
		}
		return;
	}


	/// \param points std::array of Ty, length n_ponts - 
	/// Gauss points written here
	/// \param weights std::array of Ty, length n_ponts-  
	/// Weights of points written here
	///
	/// \brief generate gauss legendre quadrature - likely to be evaluated 
	/// at compile time.
	///
	/// Generates points and weights for a gauss legendre quadrature.
	/// \code 
	/// std::array<double, 100> p, w;
	/// HBTK::gauss_legendre<100, double>(p, w);
	/// \endcode
	/// p now contians quadrature points, and w weights. This code 
	/// should be optimised away such that the solution is precalcuated
	/// at compile time.
	template <int n_points, typename Ty>
	constexpr void gauss_legendre(std::array<Ty, n_points> & points, 
								  std::array<Ty, n_points> & weights) 
	{
		static_assert(n_points > 0);
		gauss_legendre < Ty, std::array<Ty, n_points>>(n_points, points, 
																weights);
	}





}