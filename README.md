# HBTK
A C++ library containing what I consider to be 'useful stuff'. Very much liable to change.

* Integral remaps - Telles, Sato
* Integrations methods - Gauss-legendre, generic static, adaptive Simpsons / Trapezoidal. Not restricted to floats / doubles.
* GMSH parser (ASCII & Binary v2.2 - physical groups, nodes and elements only)
* GMSH writer (ASCII 2.2, physical groups, nodes and elements only)
* GMSH elements (element node coordinate (unchecked!), shape descriptions, element names)
* Plot3D reader, Plot3D writer.
* MATLAB-like GNUPlot interface for 2D plotting.

## Getting Started

To build HBTK and the demo programs you'll need CMake and a modern c++ compiler (C++14 is used, so GCC 4.9, MSVC 19). 

To build the first step is to download/clone the library. Once you have it, cd to the directory.
Set up your enviroment by using "cmake CMakeLists.txt".

If you are on Windows, you'll end up with a series of vsxproj files. To modify the library, or build any of the examples,
open a vsxproj file in Visual Studio. Getting the Unit Tests to work with cmake is still in the TODO phase.

If you're on Linux, you'll be able to just go for "make" and everything work.

To generate any documentation you'll need Doxygen. I've not checked whether documentation is workiing at the moment.
Sorry...

## Running the tests

The library uses MSTest. Currently getting the tests working again is on the TODO lists - most of the
libary is lacking in unit tests sadly - I've not time to to this as thoroughly as I should.

## Authors

* **HJA Bird** - *Initial work*

See also the list of [contributors](https://github.com/hjabird/Quad1D/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
