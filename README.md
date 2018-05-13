# HBTK
A C++ library containing what I consider to be 'useful stuff'. Very much liable to change.

Usable features:
* Integral remaps - Telles, Sato
* Integrations methods - Gauss-legendre, Gauss Laguerre, generic static, adaptive Simpsons / Trapezoidal / Gauss-Lobatto. Not restricted to floats / doubles.
* GMSH parser (ASCII & Binary v2.2 - physical groups, nodes and elements only)
* GMSH writer (ASCII 2.2, physical groups, nodes and elements only)
* Plot3D reader, Plot3D writer.
* VTK writer(s) (limited legacy structured or xml unstructured - yes, wierd, I know)
* Cubic splines
* Cartesian Geometry
* XML writer
* Structured mesh "blocks"
* Fortran sequential IO emulation
* Tabulated output inc. CSV writer
* Aerofoil geometry

Features that seem to work better on some PCs that others:
* MATLAB-like GNUPlot interface for 2D plotting.

Unverified features:
* GMSH elements (element node coordinate (unchecked!), shape descriptions, element names)
* Integration methods Gauss hermite, Gauss Jacobi/Chebyshev etc etc (these don't work / are harder to verify)
* XML reader
* VTK reader (Well, actually useless right now)

Incomplete:
* DOCUMENTATION
* UNIT TESTS

## Getting Started

To build HBTK and the demo programs you'll need CMake and a modern c++ compiler (C++14 is used, so GCC 4.9, MSVC 19). 

Steps:
* Clone the library using git: git clone https://github.com/hjabird/HBTK
* make a build directory. Eg: mkdir HBTK/build
* cd into your build directory: Eg: cd HBTK/build
* Run cmake:
* At its most basic use cmake <path to HBTK> Eg: cmake ..
* You may want to change the build options Eg perhaps:
* Visual studio: cmake -G "Visual Studio 15 2017 Win64" for Win64 rather than Win32
* cmake -D CMAKE_INSTALL_PREFIX=<path to install> for where you want the library to end up.
* Then use your whatever generator you used tools to build and install. Eg, on Linux:
  make and then make install.
  * You're good!

To generate any documentation you'll need Doxygen. Documentation is generally incomplete.

## Running the tests

The library uses the Catch2 test framework. Most of the library currently does not have unit tests.
But for where it does, use the option -D BUILD_UNIT_TESTS=ON. Catch2 will be automatically downloaded,
and the tests should be buildable using your chosen build system.

To run the tests, go to build/TestHBTK. Under there somewhere will be an executable.
For Visual Studio, it appears as Debug/all_test.exe or Release/all_tests.exe depeding
on the compiler settings.

## Authors

* **HJA Bird** - *Initial work*

See also the list of [contributors](https://github.com/hjabird/Quad1D/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
