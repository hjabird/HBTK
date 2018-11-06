#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkUnstructuredCellType.h

VTK cell type definition with mapping to integers

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

namespace HBTK {
	namespace Vtk {
		enum CellType {
			VTK_VERTEX = 1,
			VTK_POLY_VERTEX = 2,
			VTK_LINE = 3,
			VTK_POLY_LINE = 4,
			VTK_TRIANGLE = 5,
			VTK_TRIANGLE_STRIP = 6,
			VTK_POLYGON = 7,
			VTK_PIXEL = 8,
			VTK_QUAD = 9,
			VTK_TETRA = 10,
			VTK_VOXEL = 11,
			VTK_HEXAHEDRON = 12,
			VTK_WEDGE = 13,
			VTK_PYRAMID = 14,
			VTK_PENTAGONAL_PRISM = 15,
			VTK_HEXAGONAL_PRISM = 16,
			VTK_QUADRATIC_EDGE = 21,
			VTK_QUADRATIC_TRIANGLE = 22,
			VTK_QUADRATIC_QUAD = 23,
			VTK_QUADRATIC_TETRA = 24,
			VTK_QUADRATIC_HEXAHEDRON = 25,
			VTK_CUBIC_LINE = 35,
			VTK_POLYHEDRON = 42,
			VTK_PARAMETRIC_CURVE = 51,
			VTK_PARAMETRIC_SURFACE = 52,
			VTK_PARAMETRIC_TRI_SURFACE = 53,
			VTK_PARAMETRIC_QUAD_SURFACE = 55,
			VTK_PARAMETRIC_TETRA_REGION = 55,
			VTK_PARAMETRIC_HEX_REGION = 56,
			VTK_HIGHER_ORDER_EDGE = 60,
			VTK_HIGHER_ORDER_TRIANGLE = 61,
			VTK_HIGHER_ORDER_QUAD = 62,
			VTK_HIGHER_ORDER_POLYGON = 63,
			VTK_HIGHER_ORDER_TETRAHEDRON = 64,
			VTK_HIGHER_ORDER_WEDGE = 65,
			VTK_HIGHER_ORDER_PYRAMID = 66,
			VTK_HIGHER_ORDER_HEXAHEDRON = 67,
			VTK_LAGRANGE_CURVE = 68,
			VTK_LAGRANGE_TRIANGLE = 69,
			VTK_LAGRANGE_QUADRILATERAL = 70,
			VTK_LAGRANGE_TETRAHEDRON = 71,
			VTK_LAGRANGE_HEXAHEDRON = 72,
			VTK_LAGRANGE_WEDGE = 73,
			VTK_LAGRANGE_PYRAMID = 74
		};
	}
}
