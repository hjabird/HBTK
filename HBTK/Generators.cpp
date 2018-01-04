#include "stdafx.h"
#include "Generators.h"
/*////////////////////////////////////////////////////////////////////////////
Generators.cpp

Generate vectors of values. Has functions like linspace, logspace, meshgrid...

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

#include <cassert>

std::vector<double> HBTK::linspace(double start, double end)
{
	return linspace(start, end, 100);
}

std::vector<double> HBTK::linspace(double start, double end, int number_of_points)
{
	assert(number_of_points >= 0);
	assert(HBTK::check_finite(start));
	assert(HBTK::check_finite(end));

	std::vector<double> return_vector;
	return_vector.resize(number_of_points);
	HBTK::linspace(start, end, number_of_points, return_vector);
	return return_vector;
}

std::vector<double> HBTK::logspace(double start, double end)
{
	return logspace(start, end, 100);
}

std::vector<double> HBTK::logspace(double start, double end, int number_of_points)
{
	return logspace(start, end, number_of_points, 10);
}

std::vector<double> HBTK::logspace(double start, double end, int number_of_points, double base)
{
	assert(number_of_points >= 0);
	assert(HBTK::check_finite(start));
	assert(HBTK::check_finite(end));

	std::vector<double> return_vector;
	return_vector.resize(number_of_points);
	HBTK::logspace(start, end, number_of_points, base, return_vector);
	return return_vector;
}

std::vector<double> HBTK::geomspace(double start, double end)
{
	return geomspace(start, end, 100);
}

std::vector<double> HBTK::geomspace(double start, double end, int number_of_points)
{
	return geomspace(start, end, number_of_points, 10);
}

std::vector<double> HBTK::geomspace(double start, double end, int number_of_points, double base)
{
	std::vector<double> result;
	result.resize(number_of_points);
	geomspace(start, end, number_of_points, base, result);
	return result;
}

std::vector<double> HBTK::uniform(double value, int number_of_points)
{
	std::vector<double> output;
	output.resize(number_of_points);
	uniform(output, value);
	return output;
}
