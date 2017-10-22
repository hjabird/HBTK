# HBTK
A C++ library containing what I consider to be 'useful stuff'.

* Integral remaps
* Integrations methods
* GMSH parser (ASCII & Binary v2.2 - physical groups, nodes and elements only)
* GMSH elements

## Getting Started

HBTK is a static library. If using Visual Studio, first, go to team explorer and pull this Repo. Probably best at this point to run the Unit tests (Test explorer - run all). 

To use this in a project in VS add HBTK to your references (References, add references). Otherwise, for most of the library you'll certainly need headers (so add include path directory in the appropriate place) and you may need to link .obj / .lib files if you use certain parts of the library - ie. if you get lnk2019 in VS.

### Prerequisites

To use the library you'll need an up to date C++ compiler (most importantly, one that's capable
of constexprs that include loops, etc.) such as msvc 19.10 or whatever the most recent GCC or
clang/LLVM is. Whilst there is no Windows only code intentionally in the library, the library
has only been tested with msvc on Windows. It is suggested that Visual Studio is used - 
especially since the unit tests use MSTest.

To generate the documentation you'll need Doxygen (and optionally Latex / Miktex if
you want .pdfs).

## Running the tests

The library uses MSTest. Open the project in Visual Studio, and run all test.
Due to the use of constexpr and templates, some of the function are (intentionally)
evaluated at compile time. Hence, debugging can be interesting.

## Authors

* **HJA Bird** - *Initial work*

See also the list of [contributors](https://github.com/hjabird/Quad1D/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
