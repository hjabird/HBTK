# HBTK
A C++ library containing useful code for numerical engineering applications,
narcissistically named after its creator (I'm unimaginative).

A statically linked library, mostly just header files. Heavy use of templates
and constexpr. Mostly written as individual routines intended to be integrated into 
user objects.

Contains the following:
- Gauss-Legendre quadrature
- Simple adaptive quadratures
- Integral remaps
- GMSH .msh parser
- GMSH element node coordinate definitions & shape definitions
- Basic 2D potential flow distributions

The library should be considered work in progress and liable to change. Essentially this is my
collection of things that I'm worried I'll implement multiple times otherwise.

## Getting Started

HBTK is a header only library. To use, just include the appropriate header file into your project.

### Prerequisites

To use the library you'll need an up to date C++ compiler (most importantly, one that's capable
of constexprs that include loops, etc.) such as msvc 19.10 or whatever the most recent GCC or
clang/LLVM is. Whilst there is no Windows only code intentionally in the library, the library
has only been tested with msvc on Windows. It is suggested that Visual Studio is used - 
especially since the unit tests use MSTest.

To generate the documentation you'll need Doxygen (and optionally Latex / Miktex if
you want .pds).

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

The library uses MSTest. Open the project in Visual Studio, and run all test.
Due to the use of constexpr and templates, some of the function are (intentionally)
evaluated at compile time. Hence, debugging can be interesting.

## Authors

* **HJA Bird** - *Initial work*

See also the list of [contributors](https://github.com/hjabird/Quad1D/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
