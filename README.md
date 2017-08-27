# Quad1D
A C++ quadrature library for basic 1D quadrature with extensive template use.

The library includes functions to generate Gauss-Legendre quadratures at compile and runtime,
integral remaps for handling singularities and adaptive integrators.

## Getting Started

Quad1D is a header only library. To use, just include the appropriate header file into your project.

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
