#include "..\include\HBTK\AerofoilParser.h"
#pragma once
/*////////////////////////////////////////////////////////////////////////////
AerofoilParser.cpp

Parses aerofoil .dat files and spits out AerofoilGeometry objects.

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

HBTK::AerofoilParser::AerofoilParser(AerofoilGeometry & target)
	: foil_name("UNKNOWN"),
	m_foil(target)
{
}

void HBTK::AerofoilParser::main_parser(std::istream input, std::ostream error_stream)
{
	std::string this_line;
	int line_counter = 0;				// Line counter.
	int coordinate_counter = 0;		// Number of coordinates counted so far.
	int upper_points, lower_points;	// Number of x/y points for Lednicer format.
	std::vector<double> x_coords, y_coords;	// X/Y coordinates of points.

	enum format {
		Lednicer, Selig, Unknown
	} format = Unknown;

	try {
		while (std::getline(input, this_line)) {
			line_counter++;
			if (line_counter == 1) {
				foil_name = this_line;
				continue;
			}
			std::vector<std::string> substr = tokenise(this_line);
			if (substr.size() == 0) {
				continue;
			}
			else if (substr.size() != 2) {
				throw std::invalid_argument("HBTK::AerofoilParser::main_parser(...) "
					"Unexpected number of tokens in input stream on line " +
					std::to_string(line_counter) + " when 2 args were expected. Found "
					+ std::to_string((int)substr.size()) + " arguments. Line was:\n"
					+ this_line + "\n" __FILE__ + std::to_string(__LINE__));
			}
			double x, y;

			try {
				x = stod(substr[0]);
				y = stod(substr[1]);
			}
			catch (std::invalid_argument&) {
				throw std::invalid_argument("HBTK::AerofoilParser::main_parser(...) "
					"Failed to parse floating point number on line " +
					std::to_string(line_counter) + ". Line was:\n"
					+ this_line + "\n" __FILE__ + std::to_string(__LINE__));
			}

			if (format == Unknown) {
				if (x > 0) {
					format = Lednicer;
					upper_points = (int) x;
					lower_points = (int) y;
					continue;
				}
				else {
					format = Selig;
				}
			}
			x_coords.emplace_back(x);
			y_coords.emplace_back(y);
			coordinate_counter++;
		}

		if (format = Lednicer) {
			if ((x_coords.size() + y_coords.size()) != (upper_points + lower_points)) {
				throw std::invalid_argument("HBTK::AerofoilParser::main_parser(...) "
					"Incorrect number of points found in Lednicer format foil. "
					"Expected " + std::to_string(upper_points) +
					" + " + std::to_string(lower_points) + " but recieved "
					+ std::to_string(x_coords.size() + y_coords.size()) 
					+ "instead.\n"
					__FILE__ + std::to_string(__LINE__));
			}
			std::reverse(x_coords.begin(), x_coords.begin() + upper_points);
			std::reverse(y_coords.begin(), y_coords.begin() + upper_points);
		}
		m_foil.set(x_coords, y_coords);
	}
	catch (std::invalid_argument & e) {
		error_stream << e.what();
		throw e;
	}
	return;
}

