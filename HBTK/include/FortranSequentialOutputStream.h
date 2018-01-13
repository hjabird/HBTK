#pragma once
/*////////////////////////////////////////////////////////////////////////////
FortranSequentialInputStream.h

A create binary files with the Sequential record format used by FORTRAN
people at times.

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
#include <fstream>

namespace HBTK {
	class FortranSequentialOutputStream
	{
	public:
		FortranSequentialOutputStream();
		~FortranSequentialOutputStream();


		// When Fortran uses Sequential access to files, it leaves headers and
		// footers at the beginning and end of each "record". A record is made
		// for each call to WRITE. These markers are an annoyance for anyone
		// having to read or write binary interfacing Fortran programs.

		// Write a record start marker.
		void record_start(std::ofstream & output_stream);
		// Write a record end marker.
		void record_end(std::ofstream & output_stream);

	private:
		int m_last_record_start;
	};
}

