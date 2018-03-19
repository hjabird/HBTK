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
		descriptor = "point";
		break;
	case 2:
		descriptor = "polypoint";
		break;
	case 3:
		descriptor = "2 node line";
		break;
	case 4:
		descriptor = "polyline";
		break;
	case 5:
		descriptor = "3 node triangle";
		break;
	case 6:
		descriptor = "triangle strip";
		break;
	case 7:
		descriptor = "polygon";
		break;
	case 8:
		descriptor = "pixel";
		break;
	case 9:
		descriptor = "4 node quadrangle";
		break;
	case 10:
		descriptor = "4 node tetrahedron";
		break;
	case 11:
		descriptor = "voxel";
		break;
	case 12:
		descriptor = "8 node hexahedron";
		break;
	case 13:
		descriptor = "6 node wedge";
		break;
	case 14:
		descriptor = "5 node pyramid";
		break;
	case 21:
		descriptor = "3 node second order line";
		break;
	case 22:
		descriptor = "6 node second order triangle";
		break;
	case 23:
		descriptor = "8 node second order quadrangle";
		break;
	case 24:
		descriptor = "10 node second order tetrahedron";
		break;
	case 25:
		descriptor = "20 node second order hexahedron";
		break;
	default:
		descriptor = "INVALID TYPE INTEGER";
		break;
	}
	return descriptor;
}

const int HBTK::Vtk::element_node_count(int ele_id)
{
	int num;
	switch (ele_id) {
	case 1:
		num = 1;
		break;
	case 2:
		num = -2;
		break;
	case 3:
		num = 2;
		break;
	case 4:
		num = -2;
		break;
	case 5:
		num = 3;
		break;
	case 6:
		num = -2;
		break;
	case 7:
		num = -2;
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
	default:
		num = -1;
		break;
	}
	return num;
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
