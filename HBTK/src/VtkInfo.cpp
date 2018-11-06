#include "VtkInfo.h"
/*////////////////////////////////////////////////////////////////////////////
VtkInfo.cpp

Information on Vtk elements

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


const std::string HBTK::Vtk::element_name(int ele_id)
{
	std::string descriptor;
	switch (ele_id) {
	case 1:
		descriptor = "VTK_VERTEX";
		break;
	case 2:
		descriptor = "VTK_POLY_VERTEX";
		break;
	case 3:
		descriptor = "VTK_LINE";
		break;
	case 4:
		descriptor = "VTK_POLY_LINE";
		break;
	case 5:
		descriptor = "VTK_TRIANGLE";
		break;
	case 6:
		descriptor = "VTK_TRIANGLE_STRIP";
		break;
	case 7:
		descriptor = "VTK_POLYGON";
		break;
	case 8:
		descriptor = "VTK_PIXEL";
		break;
	case 9:
		descriptor = "VTK_QUAD";
		break;
	case 10:
		descriptor = "VTK_TETRA";
		break;
	case 11:
		descriptor = "VTK_VOXEL";
		break;
	case 12:
		descriptor = "VTK_HEXAHEDRON";
		break;
	case 13:
		descriptor = "VTK_WEDGE";
		break;
	case 14:
		descriptor = "VTK_PYRAMID";
		break;
	case 15:
		descriptor = "VTK_PENTAGONAL_PRISM";
		break;
	case 16:
		descriptor = "VTK_HEXAGONAL_PRISM";
		break;
	case 21:
		descriptor = "VTK_QUADRATIC_EDGE";
		break;
	case 22:
		descriptor = "VTK_QUADRATIC_TRIANGLE";
		break;
	case 23:
		descriptor = "VTK_QUADRATIC_QUAD";
		break;
	case 24:
		descriptor = "VTK_QUADRATIC_TETRA";
		break;
	case 25:
		descriptor = "VTK_QUADRATIC_HEXAHEDRON";
		break;
	case 35:
		descriptor = "VTK_CUBIC_LINE";
		break;
	case 42:
		descriptor = "VTK_POLYHEDRON";
		break;
	case 51:
		descriptor = "VTK_PARAMETRIC_CURVE";
		break;
	case 52:
		descriptor = "VTK_PARAMETRIC_SURFACE";
		break;
	case 53:
		descriptor = "VTK_PARAMETRIC_TRI_SURFACE";
		break;
	case 54:
		descriptor = "VTK_PARAMETRIC_QUAD_SURFACE";
		break;
	case 55:
		descriptor = "VTK_PARAMETRIC_TETRA_REGION";
		break;
	case 56:
		descriptor = "VTK_PARAMETRIC_HEX_REGION";
		break;
	case 60:
		descriptor = "VTK_HIGHER_ORDER_EDGE";
		break;
	case 61:
		descriptor = "VTK_HIGHER_ORDER_TRIANGLE";
		break;
	case 62:
		descriptor = "VTK_HIGHER_ORDER_QUAD";
		break;
	case 63:
		descriptor = "VTK_HIGHER_ORDER_POLYGON";
		break;
	case 64:
		descriptor = "VTK_HIGHER_ORDER_TETRAHEDRON";
		break;
	case 65:
		descriptor = "VTK_HIGHER_ORDER_WEDGE";
		break;
	case 66:
		descriptor = "VTK_HIGHER_ORDER_PYRAMID";
		break;
	case 67:
		descriptor = "VTK_HIGHER_ORDER_HEXAHEDRON";
		break;
	case 68:
		descriptor = "VTK_LAGRANGE_CURVE";
		break;
	case 69:
		descriptor = "VTK_LAGRANGE_TRIANGLE";
		break;
	case 70:
		descriptor = "VTK_LAGRANGE_QUADRILATERAL";
		break;
	case 71:
		descriptor = "VTK_LAGRANGE_TETRAHEDRON";
		break;
	case 72:
		descriptor = "VTK_LAGRANGE_HEXAHEDRON";
		break;
	case 73:
		descriptor = "VTK_LAGRANGE_WEDGE";
		break;
	case 74: 
		descriptor = "VTK_LAGRANGE_PYRAMID";
		break;
	default:
		descriptor = "VTK_INVALID_CELL_TYPE";
		break;
	}
	return descriptor;
}

const std::string HBTK::Vtk::element_name(CellType ele_id)
{
	return element_name((int) ele_id);
}

const int HBTK::Vtk::element_node_count(int ele_id)
{
	int num;
	switch (ele_id) {
	case 1:
		num = 1;
		break;
	case 2:
		num = -1;
		break;
	case 3:
		num = 2;
		break;
	case 4:
		num = -1;
		break;
	case 5:
		num = 3;
		break;
	case 6:
		num = -1;
		break;
	case 7:
		num = -1;
		break;
	case 8:
		num = 4;	// Voxel - constrained.
		break;
	case 9:
		num = 4;
		break;
	case 10:
		num = 4;
		break;
	case 11:
		num = 8;
		break;
	case 12:
		num = 8;
		break;
	case 13:
		num = 6;
		break;
	case 14:
		num = 5;
		break;
	case 15:
		num = 10;
		break;
	case 16:
		num = 12;
		break;
	case 21:
		num = 3;
		break;
	case 22:
		num = 6;
		break;
	case 23:
		num = 8;
		break;
	case 24:
		num = 10;
		break;
	case 25:
		num = 20;
		break;
	case 35:
		num = 4;
		break;
	case 42:
		num = -1;
		break;
	case 51:
		num = 20;
		break;
	case 71:
		num = 15;
		break;
	default:
		num = -2;
		break;
	}
	return num;
}

const int HBTK::Vtk::element_node_count(CellType ele_id)
{
	return element_node_count((int) ele_id);
}

const int HBTK::Vtk::element_dimensions(int ele_id)
{
	int num;
	switch (ele_id) {
	case 1:
		num = 0;
		break;
	case 2:
		num = 0;
		break;
	case 3:
		num = 1;
		break;
	case 4:
		num = 1;
		break;
	case 5:
		num = 2;
		break;
	case 6:
		num = 2;
		break;
	case 7:
		num = 2;
		break;
	case 8:
		num = 2;
		break;
	case 9:
		num = 2;
		break;
	case 10:
		num = 3;
		break;
	case 11:
		num = 3;
		break;
	case 12:
		num = 3;
		break;
	case 13:
		num = 3;
		break;
	case 14:
		num = 3;
		break;
	case 21:
		num = 1;
		break;
	case 22:
		num = 2;
		break;
	case 23:
		num = 2;
		break;
	case 24:
		num = 3;
		break;
	case 25:
		num = 3;
		break;
	default:
		num = -1;
		break;
	}
	return num;
}

const int HBTK::Vtk::element_dimensions(CellType ele_id)
{
	return element_dimensions((int) ele_id);
}

const int HBTK::Vtk::to_gmsh_element_id(int ele_id)
{
	int equiv;
	switch (ele_id) {
	case 1:
		equiv = 15;
		break;
	case 2:
		equiv = -1;
		break;
	case 3:
		equiv = 1;
		break;
	case 4:
		equiv = -1;
		break;
	case 5:
		equiv = 2;
		break;
	case 6:
		equiv = -1;
		break;
	case 7:
		equiv = -1;
		break;
	case 8:
		equiv = -1;
		break;
	case 9:
		equiv = 3;
		break;
	case 10:
		equiv = 4;
		break;
	case 11:
		equiv = -1;
		break;
	case 12:
		equiv = 5;
		break;
	case 13:
		equiv = 6;
		break;
	case 14:
		equiv = 7;
		break;
	case 21:
		equiv = 8;
		break;
	case 22:
		equiv = 9;
		break;
	case 23:
		equiv = 16;
		break;
	case 24:
		equiv = 11;
		break;
	case 25:
		equiv = 17;
		break;
	default:
		equiv = -1;
		break;
	}
	return equiv;
}

const int HBTK::Vtk::to_gmsh_element_id(CellType ele_id)
{
	return to_gmsh_element_id((int) ele_id);
}
