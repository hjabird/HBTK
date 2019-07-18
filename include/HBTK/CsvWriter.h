#pragma once
/*////////////////////////////////////////////////////////////////////////////
CsvWriter.h

Write comma separated value files from HBTK data structures.

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

#include <ostream>
#include <string>

#include "DoubleTable.h"

namespace HBTK {
	class CsvWriter {
	public:
		CsvWriter();
		~CsvWriter();
		
		// How should strings be printed? By default they're in
		// quotes: "<string>"
		std::string string_limiter;
		// End of line character(s). Default '\n'
		std::string line_ending;
		// Delimiter. Default is comma.
		std::string delimiter;
		// If true, padding will be inserted so everything lines up neatly.
		bool neat_columns;
		// Numeric precision
		int precision;

		// Write out an HBTK::DoubleTable to a path
		void write(std::string path, HBTK::DoubleTable & table);
		// Write out an HBTK::DoubleTable to an output stream.
		void write(std::ostream & output, HBTK::DoubleTable & table);

	private:

		void write(std::ostream & output, std::string str, int width);
		void write(std::ostream & output, double num, int width);
		void write_delimiter(std::ostream & output);
		void write_new_line(std::ostream & output);
		

	};
} // End namespace HBTK
