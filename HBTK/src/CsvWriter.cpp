#include "CsvWriter.h"
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

#include <fstream>
#include <iomanip>

HBTK::CsvWriter::CsvWriter()
	: string_limiter("\""),
	line_ending("\n"),
	delimiter(", "),
	neat_columns(false)
{
}

HBTK::CsvWriter::~CsvWriter()
{
}

void HBTK::CsvWriter::write(std::string path, HBTK::DoubleTable & table)
{
	std::ofstream output_stream(path, std::ios::binary);
	return write(output_stream, table);
}

void HBTK::CsvWriter::write(std::ostream & output, HBTK::DoubleTable & table)
{
	table.fill_to_match_columns();
	int n_col = table.number_of_columns();
	std::vector<int> col_widths(n_col);

	for (int i = 0; i < n_col; i++) {
		int width = (int)table.column_name(i).size() 
			+ 2 * string_limiter.size();
		if (neat_columns) {
			write(output, table.column_name(i), (precision + 6 > width ? precision + 6 : width));
		}
		else {
			write(output, table.column_name(i), width);
		}
		write_delimiter(output);
		col_widths[i] = width;
	}
	write_new_line(output);

	if (!neat_columns) {
		for (int & width : col_widths) width = 0; // Bit of a hack really.
	}

	int n_row = table.number_of_rows();
	std::vector<double> row(n_col);
	for (int i = 0; i < n_row; i++) {
		row = table.read_row(i);
		for (int j = 0; j < n_col; j++) {
			write(output, row[j], 
					(precision + 6 > col_widths[j] ? precision + 6 : col_widths[j]));
			write_delimiter(output);
		}
		write_new_line(output);
	}


}

void HBTK::CsvWriter::write(std::ostream & output, std::string str, int width)
{
	output << std::setw(width) << 
		string_limiter + str + string_limiter;
	return;
}

void HBTK::CsvWriter::write(std::ostream & output, double num, int width)
{
	output << std::setprecision(precision) << std::setw(width) << std::scientific << num;
}

void HBTK::CsvWriter::write_delimiter(std::ostream & output)
{
	output << delimiter;
}

void HBTK::CsvWriter::write_new_line(std::ostream & output)
{
	output << line_ending;
}


