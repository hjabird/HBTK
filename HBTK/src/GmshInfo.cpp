#include "stdafx.h"
#include "GmshInfo.h"
/*////////////////////////////////////////////////////////////////////////////
GmshInfo.cpp

Information on GMSH elements.

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


const std::string HBTK::Gmsh::element_name(int ele_id)
{
	std::string res;
	switch (ele_id) {
	case 1:
		res = "2 node line";
		break;
	case 2:
		res = "3 node triangle";
		break;
	case 3:
		res = "4 node quadrangle";
		break;
	case 4:
		res = "4 node tetrahedron";
		break;
	case 5:
		res = "8 node hexahedron";
		break;
	case 6:
		res = "6 node prism";
		break;
	case 7:
		res = "5 node pyramid";
		break;
	case 8:
		res = "3 node second order line";
		break;
	case 9:
		res = "6 node second order triangle";
		break;
	case 10:
		res = "9 node second order quadrangle";
		break;
	case 11:
		res = "10 node second order tetrahedron";
		break;
	case 12:
		res = "27 node second order hexahedron";
		break;
	case 13:
		res = "18 node second order prism";
		break;
	case 14:
		res = "14 node second order pyramid";
		break;
	case 15:
		res = "1 node point";
		break;
	case 16:
		res = "8 node second order quadrangle";
		break;
	case 17:
		res = "20 node second order hexahedron";
		break;
	case 18:
		res = "15 node second order prism";
		break;
	case 19:
		res = "13 node second order pyramid";
		break;
	case 20:
		res = "9 node third order incomplete triangle";
		break;
	case 21:
		res = "10 node third order triangle";
		break;
	case 22:
		res = "12 node fourth order incomplete triangle";
		break;
	case 23:
		res = "15 node fourth order triangle";
		break;
	case 24:
		res = "15 node fifth order incomplete triangle";
		break;
	case 25:
		res = "21 node fifth order complete triangle";
		break;
	case 26:
		res = "4 node third order edge";
		break;
	case 27:
		res = "5 node fourth order edge";
		break;
	case 28:
		res = "6 node fifth order edge";
		break;
	case 29:
		res = "20 node third order tetrahedron";
		break;
	case 30:
		res = "35 node fourth order tetrahedron";
		break;
	case 31:
		res = "56 node fifth order tetrahedron";
		break;
	case 32:
		res = "64 node third order hexahedron";
		break;
	case 93:
		res = "125 node fourth order hexahedron";
		break;
	default:
		res = "INVALID TYPE INTEGER";
		break;
	}
	return res;
}


constexpr int HBTK::Gmsh::element_node_count(int ele_id)
{
	int res = -1;
	switch (ele_id) {
	case 1:
		res = 2;
		break;
	case 2:
		res = 3;
		break;
	case 3:
		res = 4;
		break;
	case 4:
		res = 4;
		break;
	case 5:
		res = 8;
		break;
	case 6:
		res = 6;
		break;
	case 7:
		res = 5;
		break;
	case 8:
		res = 3;
		break;
	case 9:
		res = 6;
		break;
	case 10:
		res = 9;
		break;
	case 11:
		res = 10;
		break;
	case 12:
		res = 27;
		break;
	case 13:
		res = 18;
		break;
	case 14:
		res = 14;
		break;
	case 15:
		res = 1;
		break;
	case 16:
		res = 8;
		break;
	case 17:
		res = 20;
		break;
	case 18:
		res = 15;
		break;
	case 19:
		res = 13;
		break;
	case 20:
		res = 9;
		break;
	case 21:
		res = 10;
		break;
	case 22:
		res = 12;
		break;
	case 23:
		res = 15;
		break;
	case 24:
		res = 15;
		break;
	case 25:
		res = 21;
		break;
	case 26:
		res = 4;
		break;
	case 27:
		res = 5;
		break;
	case 28:
		res = 6;
		break;
	case 29:
		res = 20;
		break;
	case 30:
		res = 35;
		break;
	case 31:
		res = 56;
		break;
	case 32:
		res = 64;
		break;
	case 93:
		res = 125;
		break;
	default:
		res = -1;
		break;
	}
	return res;
}


constexpr int HBTK::Gmsh::element_dimensions(int ele_id)
{
	int res = -1;
	switch (ele_id) {
	case 1:
		res = 1;
		break;
	case 2:
		res = 2;
		break;
	case 3:
		res = 2;
		break;
	case 4:
		res = 3;
		break;
	case 5:
		res = 3;
		break;
	case 6:
		res = 3;
		break;
	case 7:
		res = 3;
		break;
	case 8:
		res = 1;
		break;
	case 9:
		res = 2;
		break;
	case 10:
		res = 2;
		break;
	case 11:
		res = 3;
		break;
	case 12:
		res = 3;
		break;
	case 13:
		res = 3;
		break;
	case 14:
		res = 3;
		break;
	case 15:
		res = 0;
		break;
	case 16:
		res = 2;
		break;
	case 17:
		res = 3;
		break;
	case 18:
		res = 3;
		break;
	case 19:
		res = 3;
		break;
	case 20:
		res = 2;
		break;
	case 21:
		res = 2;
		break;
	case 22:
		res = 2;
		break;
	case 23:
		res = 2;
		break;
	case 24:
		res = 2;
		break;
	case 25:
		res = 2;
		break;
	case 26:
		res = 1;
		break;
	case 27:
		res = 1;
		break;
	case 28:
		res = 1;
		break;
	case 29:
		res = 3;
		break;
	case 30:
		res = 3;
		break;
	case 31:
		res = 3;
		break;
	case 32:
		res = 3;
		break;
	case 93:
		res = 3;
		break;
	default:
		res = -1;
		break;
	}
	return res;
}
