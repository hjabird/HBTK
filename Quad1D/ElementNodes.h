#pragma once
/*////////////////////////////////////////////////////////////////////////////
ElementNodes.h

Defines the nodal position of elements in their local coordinate system.

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

#include <array>

namespace Elements
{
	class Point1;
	
	class Line2;
	class Line3;
	class Line4;
	class Line5;
	class Line6;

	class Triangle3;
	class Triangle6;
	class Triangle9;
	class Triangle10;
	class Triangle12;
	class Triangle15O4;
	class Triangle15O5;
	class Triangle21;

	class Quadrangle4;
	class Quadrangle8;
	class Quadrangle9;
	class Quadrangle12;
	class Quadrangle16;

	class Tetrahedron4;
	class Tetrahedron10;
	class Tetrahedron20;

	class Hexahedron8;
	class Hexahedron20;
	class Hexahedron27;

	class Prism6;
	class Prism15;
	class Prism18;

	class Pyramid5;
	class Pyramid13;
	class Pyramid14;
}




namespace Elements
{
    class Point1
    {
        const std::array<std::array<double, 0>, 0> nodes = { {} };
    };

    class Line2
    {
        const std::array<std::array<double, 1>, 2> nodes = {{ {{ -1.0 }},{{ 1.0 }} }};
    };

    class Line3
    {
        const std::array<std::array<double, 1>, 3> nodes = {{ {{ -1.0 }},{{ 1.0 }},{{ 0.0 }} }};
    };

    class Line4
    {
        const std::array<std::array<double, 1>, 4> nodes = {{ 
        {{ -1.0 }},
        {{ 1.0 }},
        {{ -1.0 / 3.0 }},
        {{ 1.0 / 3.0 }} }};
    };

    class Line5
    {
        const std::array<std::array<double, 1>, 5> nodes = {{ 
        {{ -1.0 }},
        {{ 1.0 }},
        {{ -0.5 }},
        {{ 0.0 }},
        {{ 0.5 }} }};
    };

    class Line6
    {
        const std::array<std::array<double, 1>, 6> nodes = {{ 
        {{ -1.0 }},
        {{ 1.0 }},
        {{ -3.0 / 5.0 }},
        {{ -1.0 / 5.0 }},
        {{ 1.0 / 5.0 }},
        {{ 3.0 / 5.0 }} 
        }};
    };

    class Triangle3
    {
        const std::array<std::array<double, 2>, 3> nodes = {{ 
        {{ 0.0,  0.0 }},
        {{ 1.0,  0.0 }},
        {{ 0.0,  1.0 }} 
        }};
    };

    class Triangle6
    {
        const std::array<std::array<double, 2>, 6> nodes = {{ 
        {{ 0.0,  0.0 }},
        {{ 1.0,  0.0 }},
        {{ 0.0,  1.0 }},
        {{ 0.5,	0.0 }},
        {{ 0.5,	0.5 }},
        {{ 0.0,	0.5 }} 
        }};
    };

    class Triangle9
    {
        const std::array<std::array<double, 2>, 9> nodes = {{ 
        {{ 0.0,			0.0 }},
        {{ 1.0,			0.0 }},
        {{ 0.0,			1.0 }},
        {{ 1.0 / 3.0,	0.0 }},
        {{ 2.0 / 3.0,	0.0 }},
        {{ 2.0 / 3.0,	1.0 / 3.0 }},
        {{ 1.0 / 3.0,	2.0 / 3.0 }},
        {{ 0.0,			2.0 / 3.0 }},
        {{ 0.0,			1.0 / 3.0 }} }};
    };

    class Triangle10
    {
        const std::array<std::array<double, 2>, 10> nodes = {{ 
        {{ 0.0,			0.0 }},
        {{ 1.0,			0.0 }},
        {{ 0.0,			1.0 }},
        {{ 1.0 / 3.0,	0.0 }},
        {{ 2.0 / 3.0,	0.0 }},
        {{ 2.0 / 3.0,	1.0 / 3.0 }},
        {{ 1.0 / 3.0,	2.0 / 3.0 }},
        {{ 0.0,			2.0 / 3.0 }},
        {{ 0.0,			1.0 / 3.0 }},
        {{ 1.0 / 3.0,	1.0 / 3.0 }} }};
    };

    class Triangle12
    {
        const std::array<std::array<double, 2>, 12> nodes = {{ 
        {{ 0.0,     0.0 }},
        {{ 1.0,     0.0 }},
        {{ 0.0,     1.0 }},
        {{ 0.25,    0.0 }},
        {{ 0.5,     0.0 }},
        {{ 0.75,    0.0 }},
        {{ 0.75,    0.25 }},
        {{ 0.5,     0.5 }},
        {{ 0.25,    0.75 }},
        {{ 0.0,     0.75 }},
        {{ 0.0,     0.5 }},
        {{ 0.0,     0.25 }} }};
    };

    class Triangle15O4
    {
        const std::array<std::array<double, 2>, 15> nodes = {{ 
        {{ 0.0,  0.0 }},
        {{ 1.0,  0.0 }},
        {{ 0.0,  1.0 }},
        {{ 0.25, 0.0 }},
        {{ 0.5,  0.0 }},
        {{ 0.75, 0.0 }},
        {{ 0.75, 0.25 }},
        {{ 0.5,  0.5 }},
        {{ 0.25, 0.75 }},
        {{ 0.0,  0.75 }},
        {{ 0.0,  0.5 }},
        {{ 0.0,  0.25 }},
        {{ 0.25, 0.25 }},
        {{ 0.5,  0.25 }},
        {{ 0.25, 0.5 }} }};
    };

    class Triangle15O5
    {
        const std::array<std::array<double, 2>, 15> nodes = {{ 
        {{ 0.0,	0.0 }},
        {{ 1.0,	0.0 }},
        {{ 0.0,  1.0 }},
        {{ 0.2,	0.0 }},
        {{ 0.4,	0.0 }},
        {{ 0.6,	0.0 }},
        {{ 0.8,	0.0 }},
        {{ 0.8,	0.2 }},
        {{ 0.6,	0.4 }},
        {{ 0.4,	0.6 }},
        {{ 0.2,	0.8 }},
        {{ 0.8,	0.0 }},
        {{ 0.6,	0.0 }},
        {{ 0.4,	0.0 }},
        {{ 0.2,	0.0 }} }};
    };

    class Triangle21
    {
        const std::array<std::array<double, 2>, 21> nodes = {{ 
        {{ 0.0,  0.0 }},
        {{ 1.0,  0.0 }},
        {{ 0.0,  1.0 }},
        {{ 0.2,  0.0 }},
        {{ 0.4,  0.0 }},
        {{ 0.6,  0.0 }},
        {{ 0.8,  0.0 }},
        {{ 0.8,  0.2 }},
        {{ 0.6,  0.4 }},
        {{ 0.4,  0.6 }},
        {{ 0.2,  0.8 }},
        {{ 0.8,  0.0 }},
        {{ 0.6,  0.0 }},
        {{ 0.4,  0.0 }},
        {{ 0.2,  0.0 }},
        {{ 0.2,	0.2 }},
        {{ 0.4,	0.2 }},
        {{ 0.6,	0.2 }},
        {{ 0.4,	0.4 }},
        {{ 0.2,	0.6 }},
        {{ 0.2,	0.4 }} }};
    };

    class Quadrangle4
    {
        const std::array<std::array<double, 2>, 4> nodes = {{ 
        {{ -1.0, -1.0 }},
        {{ 1.0,  -1.0 }},
        {{ 1.0,  1.0 }},
        {{ -1.0, 1.0 }} }};
    };

    class Quadrangle8
    {
        const std::array<std::array<double, 2>, 8> nodes = {{ 
        {{ -1.0, -1.0 }},
        {{ 1.0,  -1.0 }},
        {{ 1.0,  1.0 }},
        {{ -1.0, 1.0 }},
        {{ 0.0,  -1.0 }},
        {{ 1.0,  0.0 }},
        {{ 0.0,  1.0 }},
        {{ -1.0, 0.0 }} }};
    };

    class Quadrangle9
    {
        const std::array<std::array<double, 2>, 9> nodes = {{ 
        {{ -1.0, -1.0 }},
        {{ 1.0,  -1.0 }},
        {{ 1.0,  1.0 }},
        {{ -1.0, 1.0 }},
        {{ 0.0,  -1.0 }},
        {{ 1.0,  0.0 }},
        {{ 0.0,  1.0 }},
        {{ -1.0, 0.0 }},
        {{ 0.0,  0.0 }} }};
    };

    class Quadrangle12
    {
        const std::array<std::array<double, 2>, 12> nodes = {{ 
        {{ -1.0,			-1.0 }},
        {{ 1.0,			-1.0 }},
        {{ 1.0,			1.0 }},
        {{ -1.0,			1.0 }},
        {{ -1.0 / 3.0,	-1.0 }},
        {{ 1.0 / 3.0,	-1.0 }},
        {{ 1.0,			-1.0 / 3.0 }},
        {{ 1.0,			1.0 / 3.0 }},
        {{ 1.0 / 3.0,	1.0 }},
        {{ -1.0 / 3.0,	1.0 }},
        {{ -1.0,			1.0 / 3.0 }},
        {{ -1.0,			-1.0 / 3.0 }} }};
    };

    class Quadrangle16
    {
        const std::array<std::array<double, 2>, 16> nodes = {{ 
        {{ -1.0,         -1.0 }},
        {{ 1.0,          -1.0 }},
        {{ 1.0,          1.0 }},
        {{ -1.0,         1.0 }},
        {{ -1.0 / 3.0,   -1.0 }},
        {{ 1.0 / 3.0,    -1.0 }},
        {{ 1.0,          -1.0 / 3.0 }},
        {{ 1.0,          1.0 / 3.0 }},
        {{ 1.0 / 3.0,    1.0 }},
        {{ -1.0 / 3.0,   1.0 }},
        {{ -1.0,         1.0 / 3.0 }},
        {{ -1.0,         -1.0 / 3.0 }},
        {{ -1.0 / 3.0,   -1.0 / 3.0 }},
        {{ 1.0 / 3.0,    -1.0 / 3.0 }},
        {{ 1.0 / 3.0,    1.0 / 3.0 }},
        {{ -1.0 / 3.0,   1.0 / 3.0 }} }};
    };

    class Tetrahedron4
    {
        const std::array<std::array<double, 3>, 4> nodes = {{ 
        {{ 0.0,  0.0,  0.0 }},
        {{ 1.0,  0.0,  0.0 }},
        {{ 0.0,  1.0,  0.0 }},
        {{ 0.0,  0.0,  1.0 }} }};
    };

    class Tetrahedron10
    {
        const std::array<std::array<double, 3>, 10> nodes = {{ 
        {{ 0.0,  0.0,  0.0 }},
        {{ 1.0,  0.0,  0.0 }},
        {{ 0.0,  1.0,  0.0 }},
        {{ 0.0,  0.0,  1.0 }},
        {{ 0.5,  0.0,  0.0 }},
        {{ 0.5,  0.5,  0.0 }},
        {{ 0.0,  0.5,  0.0 }},
        {{ 0.0,  0.0,  0.5 }},
        {{ 0.0,  0.5,  0.0 }},
        {{ 0.5,  0.0,  0.5 }} }};
    };

    class Tetrahedron20
    {
        const std::array<std::array<double, 3>, 20> nodes = {{ 
        {{ 0.0,			0.0,		0.0 }},
        {{ 1.0,			0.0,		0.0 }},
        {{ 0.0,			1.0,		0.0 }},
        {{ 0.0,			0.0,		1.0 }},
        {{ 1.0 / 3.0,	0.0,		0.0 }} ,
        {{ 2.0 / 3.0,	0.0,		0.0 }} ,
        {{ 2.0 / 3.0,	1.0 / 3.0,	0.0 }} ,
        {{ 1.0 / 3.0,	2.0 / 3.0,	0.0 }} ,
        {{ 0.0,			2.0 / 3.0,	0.0 }} ,
        {{ 0.0,			1.0 / 3.0,	0.0 }} ,
        {{ 0.0,			1.0 / 3.0,	0.0 }} ,
        {{ 0.0,			2.0 / 3.0,	0.0 }} ,
        {{ 0.0,			2.0 / 3.0,	1.0 / 3.0 }} ,
        {{ 0.0,			1.0 / 3.0,	2.0 / 3.0 }} ,
        {{ 2.0 / 3.0,	1.0 / 3.0,	0.0 }} ,
        {{ 1.0 / 3.0,	2.0 / 3.0,	0.0 }} ,
        {{ 1.0 / 3.0,	1.0 / 3.0,	0.0 }} ,
        {{ 1.0 / 3.0,	0.0,		1.0 / 3.0 }} ,
        {{ 0.0,			1.0 / 3.0,	1.0 / 3.0 }} ,
        {{ 1.0 / 3.0,	1.0 / 3.0,	2.0 / 3.0 }} }};
    };

    class Hexahedron8
    {
        const std::array<std::array<double, 3>, 8> nodes = {{ 
        {{ -1.0, -1.0, -1.0 }},
        {{ 1.0,	-1.0, -1.0 }},
        {{ 1.0,	1.0,  -1.0 }},
        {{ -1.0, 1.0,  -1.0 }},
        {{ -1.0, -1.0, 1.0 }},
        {{ 1.0,	-1.0, 1.0 }},
        {{ 1.0,	-1.0, 1.0 }},
        {{ 1.0,	1.0,  1.0 }} }};
    };

    class Hexahedron20
    {
        const std::array<std::array<double, 3>, 20> nodes = {{ 
        {{ -1.0, -1.0, -1.0 }},
        {{ 1.0,  -1.0, -1.0 }},
        {{ 1.0,  1.0,  -1.0 }},
        {{ -1.0, 1.0,  -1.0 }},
        {{ -1.0, -1.0, 1.0 }},
        {{ 1.0,  -1.0, 1.0 }},
        {{ 1.0,  -1.0, 1.0 }},
        {{ 1.0,  1.0,  1.0 }},
        {{ 0.0,  -1.0, -1.0 }},
        {{ -1.0, 0.0,  -1.0 }},
        {{ -1.0, -1.0, 0.0 }},
        {{ 1.0,  0.0, -1.0 }},
        {{ 1.0,  -1.0, 0.0 }},
        {{ 0.0,  1.0, -1.0 }},
        {{ 1.0,  1.0,  0.0 }},
        {{ -1.0, 1.0,  0.0 }},
        {{ 0.0,  -1.0, 1.0 }},
        {{ -1.0, 0.0,  1.0 }},
        {{ 1.0,  0.0,  1.0 }},
        {{ 0.0,  1.0,  1.0 }} }};
    };

    class Hexahedron27
    {
        const std::array<std::array<double, 3>, 27> nodes = {{ 
        {{ -1.0, -1.0, -1.0 }},
        {{ 1.0, -1.0, -1.0 }},
        {{ 1.0, 1.0, -1.0 }},
        {{ -1.0, 1.0, -1.0 }},
        {{ -1.0, -1.0, 1.0 }},
        {{ 1.0, -1.0, 1.0 }},
        {{ 1.0, -1.0, 1.0 }},
        {{ 1.0, 1.0, 1.0 }},
        {{ 0.0, -1.0, -1.0 }},
        {{ -1.0, 0.0, -1.0 }},
        {{ -1.0, -1.0, 0.0 }},
        {{ 1.0, 0.0, -1.0 }},
        {{ 1.0, -1.0, 0.0 }},
        {{ 0.0, 1.0, -1.0 }},
        {{ 1.0, 1.0, 0.0 }},
        {{ -1.0, 1.0, 0.0 }},
        {{ 0.0, -1.0, 1.0 }},
        {{ -1.0, 0.0, 1.0 }},
        {{ 1.0, 0.0, 1.0 }},
        {{ 0.0, 1.0, 1.0 }},
        {{ 0.0, 0.0, -1.0 }},
        {{ 0.0, -1.0, 0.0 }},
        {{ -1.0, 0.0, 0.0 }},
        {{ 1.0, 0.0, 0.0 }},
        {{ 0.0, 1.0, 0.0 }},
        {{ 0.0, 0.0, 1.0 }},
        {{ 0.0, 0.0, 0.0 }} }};
    };

    class Prism6
    {
        const std::array<std::array<double, 3>, 6> nodes = {{ 
        {{ 0.0, 0.0, -1.0 }},
        {{ 1.0, 0.0, -1.0 }},
        {{ 0.0, 1.0, -1.0 }},
        {{ 0.0, 0.0, 1.0 }},
        {{ 1.0, 0.0, 1.0 }},
        {{ 0.0, 1.0, 1.0 }} }};
    };

    class Prism15
    {
        const std::array<std::array<double, 3>, 15> nodes = {{ 
        {{ 0.0, 0.0, -1.0 }},
        {{ 1.0, 0.0, -1.0 }},
        {{ 0.0, 1.0, -1.0 }},
        {{ 0.0, 0.0, 1.0 }},
        {{ 1.0, 0.0, 1.0 }},
        {{ 0.0, 1.0, 1.0 }},
        {{ 0.5, 0.0, -1.0 }},
        {{ 0.0, 0.5, -1.0 }},
        {{ 0.0, 0.0, 0.0 }},
        {{ 0.5, 0.5, -1.0 }},
        {{ 1.0, 0.0, 0.0 }},
        {{ 0.0, 1.0, 0.0 }},
        {{ 0.5, 0.0, 1.0 }},
        {{ 0.0, 0.5, 1.0 }},
        {{ 0.5, 0.5, 1.0 }} }};
    };

    class Prism18
    {
        const std::array<std::array<double, 3>, 18> nodes = {{ 
        {{ 0.0, 0.0, -1.0 }},
        {{ 1.0, 0.0, -1.0 }},
        {{ 0.0, 1.0, -1.0 }},
        {{ 0.0, 0.0, 1.0 }},
        {{ 1.0, 0.0, 1.0 }},
        {{ 0.0, 1.0, 1.0 }},
        {{ 0.5, 0.0, -1.0 }},
        {{ 0.0, 0.5, -1.0 }},
        {{ 0.0, 0.0, 0.0 }},
        {{ 0.5, 0.5, -1.0 }},
        {{ 1.0, 0.0, 0.0 }},
        {{ 0.0, 1.0, 0.0 }},
        {{ 0.5, 0.0, 1.0 }},
        {{ 0.0, 0.5, 1.0 }},
        {{ 0.5, 0.5, 1.0 }},
        {{ 0.5, 0.0, 0.0 }},
        {{ 0.0, 0.5, 0.0 }},
        {{ 0.5, 0.5, 0.0 }} }};
    };

    class Pyramid5
    {
        const std::array<std::array<double, 3>, 5> nodes = {{ 
        {{ -1.0, -1.0, 0.0 }},
        {{ 1.0,	-1.0, 0.0 }},
        {{ 1.0,	1.0,  0.0 }},
        {{ -1.0, 1.0,  0.0 }},
        {{ 0.0,	0.0,  1.0 }} }};
    };

    class Pyramid13
    {
        const std::array<std::array<double, 3>, 13> nodes = {{ 
        {{ -1.0, -1.0, 0.0 }},
        {{ 1.0,  -1.0, 0.0 }},
        {{ 1.0,  1.0,  0.0 }},
        {{ -1.0, 1.0,  0.0 }},
        {{ 0.0,  0.0,  1.0 }},
        {{ 0.0,  -1.0, 0.0 }},
        {{ -1.0, 0.0,  0.0 }},
        {{ -0.5, -0.5, 0.5 }},
        {{ 1.0,  0.0,  0.0 }},
        {{ 0.5,  -0.5, 0.5 }},
        {{ 0.0,  1.0,  0.0 }},
        {{ 0.5,  0.5,  0.5 }},
        {{ -0.5, 0.5,  0.5 }} }};
    };

    class Pyramid14
    {
        const std::array<std::array<double, 3>, 14> nodes = {{ 
        {{ -1.0, -1.0, 0.0 }},
        {{ 1.0,  -1.0, 0.0 }},
        {{ 1.0,  1.0,  0.0 }},
        {{ -1.0, 1.0,  0.0 }},
        {{ 0.0,  0.0,  1.0 }},
        {{ 0.0,  -1.0, 0.0 }},
        {{ -1.0, 0.0,  0.0 }},
        {{ -0.5, -0.5, 0.5 }},
        {{ 1.0,  0.0,  0.0 }},
        {{ 0.5,  -0.5, 0.5 }},
        {{ 0.0,  1.0,  0.0 }},
        {{ 0.5,  0.5,  0.5 }},
        {{ -0.5, 0.5,  0.5 }},
        {{ 0.0,  0.0,  0.0 }} }};
    };

}

