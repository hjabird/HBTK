#pragma once
/*////////////////////////////////////////////////////////////////////////////
ElementGeometry.h

Defines the shape of elements in cartesian coordinates.

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

#include <type_traits>

namespace HBTK {
	namespace Elements
	{
		class PointGeometry;
		class LineGemoetry;
		class RightAngleTriangleGeometry;
		class QuadrangleGeometry;
		class TetrahedronGeometry;
		class HexahedronGeometry;
		class RightAngleTrianglePrismGeometry;
		class PyramidGeometry;
	}

	namespace Elements
	{
		class PointGeometry {
			const int local_number_of_dimensions = 0;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return true;
			}
		};

		class LineGeometry {
			const int local_number_of_dimensions = 1;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				if (std::is_floating_point<TCoord>::value)
				{
					static_assert(false)
						// return local_coord >= -1.0 && local_coord <= 1.0
				}
				else
				{
					return local_coord[0] >= -1.0 && local_coord[0] <= 1.0
				}
			}
		};

		class RightAngleTriangleGeometry {
			const int local_number_of_dimensions = 2;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return (local_coord[0] >= 0.0
					&& local_coord[1] >= 0.0
					&& local_coord[0] + local_coord[1] >= 1.0);
			}
		};

		class QuadrangleGeometry {
			const int local_number_of_dimensions = 2;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return (local_coord[0] >= -1.0 && local_coord[0] <= 1.0
					&& local_coord[1] >= -1.0 && local_coord[1] <= 1.0);
			}
		};

		class TetrahedronGeometry {
			const int local_number_of_dimensions = 3;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return (local_coord[0] >= 0.0
					&& local_coord[1] >= 0.0
					&& local_coord[2] >= 0.0
					&& local_coord[0] + local_coord[1] + local_coord[2] >= 1.0);
			}
		};

		class HexahedronGeometry {
			const int local_number_of_dimensions = 3;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return (local_coord[0] >= -1.0 && local_coord[0] <= 1.0
					&& local_coord[1] >= -1.0 && local_coord[1] <= 1.0
					&& local_coord[2] >= -1.0 && local_coord[2] <= 1.0);
			}
		};

		class RightAngleTrianglePrismGeometry {
			const int local_number_of_dimensions = 3;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return (local_coord[0] >= 0.0
					&& local_coord[1] >= 0.0
					&& local_coord[0] + local_coord[1] >= 1.0
					&& local_coord[2] >= -1.0 && local_coord[2] <= 1.0);
			}
		};

		class PyramidGeometry {
			const int local_number_of_dimensions = 3;

			template < typename TCoord >
			constexpr bool is_local_coord_in_element(TCoord local_coord) {
				return (local_coord[0] >= -1.0 && local_coord[0] <= 1.0
					&& local_coord[1] >= -1.0 && local_coord[1] <= 1.0
					&& local_coord[2] >= 0.0 && local_coord[2] <= 1.0
					&& local_coord[2] + abs(local_coord[0]) <= 1.0
					&& local_coord[2] + abs(local_coord[1]) <= 1.0
					);
			}
		};
	}
}

