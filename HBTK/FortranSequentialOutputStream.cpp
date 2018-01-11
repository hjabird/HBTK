#include "stdafx.h"
#include "FortranSequentialOutputStream.h"
/*////////////////////////////////////////////////////////////////////////////
FortranSequentialInputStream.cpp

A create binary files with the Sequential record format used by FORTRAN
people at times.

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

HBTK::FortranSequentialOutputStream::FortranSequentialOutputStream()
	: m_last_record_start(-1)
{
}


HBTK::FortranSequentialOutputStream::~FortranSequentialOutputStream()
{
	assert(m_last_record_start == -1);
}


void HBTK::FortranSequentialOutputStream::record_start(std::ofstream & output_stream)
{
	assert(m_last_record_start == -1);
	// Skip over the header - we'll fill that in once we've written the record.
	char buffer[sizeof(int)];
	output_stream.write(buffer, sizeof(int));
	m_last_record_start = output_stream.tellp();
	return;
}


void HBTK::FortranSequentialOutputStream::record_end(std::ofstream & output_stream)
{
	assert(m_last_record_start != -1);
	int record_end = output_stream.tellp();
	int record_length = record_end - m_last_record_start;
	output_stream.seekp(m_last_record_start - sizeof(int));
	output_stream.write(reinterpret_cast<char*>(&record_length), sizeof(record_length));
	output_stream.seekp(record_end);
	output_stream.write(reinterpret_cast<char*>(&record_length), sizeof(record_length));
	m_last_record_start = -1;
	return;
}
