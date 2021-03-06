#include "FortranSequentialInputStream.h"
/*////////////////////////////////////////////////////////////////////////////
FortranSequentialInputStream.cpp

A class to handle the "records" created by Fortran WRITES in Sequential
binary mode.

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


HBTK::FortranSequentialInputStream::FortranSequentialInputStream()
	: m_record_length(-1),
	m_last_record_start(-1)
{
}

HBTK::FortranSequentialInputStream::~FortranSequentialInputStream()
{
}

int HBTK::FortranSequentialInputStream::record_open(std::ifstream & input_stream)
{
	assert(m_last_record_start == -1);  // If the last record was not ended, assert fails.
	assert(m_record_length == -1);		// If when not in record, this should be -1.
	char buffer[sizeof(m_record_length)];
	input_stream.read(buffer, sizeof(m_record_length));
	m_record_length = *reinterpret_cast<int*>(buffer);
	m_last_record_start = (int)input_stream.tellg();
	if (m_record_length < 0) { throw m_record_length; }
	return m_record_length;
}

int HBTK::FortranSequentialInputStream::record_open_reverse(std::ifstream & input_stream)
{
	assert(m_last_record_start == -1);  // If the last record was not ended, assert fails.
	assert(m_record_length == -1);		// If when not in record, this should be -1.

	char buffer[sizeof(m_record_length)];
	int record_end_pos = (int)input_stream.tellg() - sizeof(buffer);
	input_stream.seekg(record_end_pos);
	input_stream.read(buffer, sizeof(m_record_length));
	input_stream.seekg(record_end_pos);
	m_record_length = *reinterpret_cast<int*>(buffer);
	m_last_record_start = record_end_pos - m_record_length;
	if (m_record_length < 0) { throw m_record_length; }
	return m_record_length;
}

void HBTK::FortranSequentialInputStream::record_close(std::ifstream & input_stream)
{
	assert(m_record_length != -1);
	assert(m_last_record_start != -1);

	int pos = (int)input_stream.tellg();
	int end_bytes;
	char buffer[sizeof(end_bytes)];
	input_stream.read(buffer, sizeof(end_bytes));
	end_bytes = *reinterpret_cast<int*>(buffer);
	if (end_bytes != m_record_length) { throw 0; }

	// We want to have at least skipped the record footer before throwing for this.
	if (pos - m_last_record_start != m_record_length) { throw pos - m_last_record_start; }

	m_record_length = -1;
	m_last_record_start = -1;
	return;
}

void HBTK::FortranSequentialInputStream::record_close_reverse(std::ifstream & input_stream)
{
	assert(m_record_length != -1);
	assert(m_last_record_start != -1);

	char buffer[sizeof(m_record_length)];
	int record_start_pos = (int)input_stream.tellg() - sizeof(buffer);
	if ((int)input_stream.tellg() != m_last_record_start) { throw 0; }
	input_stream.seekg(record_start_pos);
	input_stream.read(buffer, sizeof(m_record_length));
	input_stream.seekg(record_start_pos);
	int start_bytes = *reinterpret_cast<int*>(buffer);
	if (start_bytes != m_record_length) { throw 0; }

	m_record_length = -1;
	m_last_record_start = -1;
	return;
}

int HBTK::FortranSequentialInputStream::seek_record_start(std::ifstream & input_stream)
{
	assert(m_record_length != -1);
	assert(m_last_record_start != -1);

	int pos = (int)input_stream.tellg();
	int relative_pos = pos - m_last_record_start;
	input_stream.seekg(m_last_record_start);
	return m_record_length;
}

int HBTK::FortranSequentialInputStream::seek_record_end(std::ifstream & input_stream)
{
	assert(m_record_length != -1);
	assert(m_last_record_start != -1);

	input_stream.seekg(m_last_record_start + m_record_length);

	return m_record_length;
}

