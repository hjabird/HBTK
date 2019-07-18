#pragma once
/*////////////////////////////////////////////////////////////////////////////
DoubleTable.h

Column based storage of numeric data.
Data is stored in columns with a string as a heading. Rows, columns and
specific cells can be accessed. The table must, at times, be rectangular,
so a filler value is used in these cases.

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

#include <string>
#include <vector>

namespace HBTK {
	class DoubleTable {
	public:
		DoubleTable();
		~DoubleTable();

		int number_of_columns();
				
		int number_of_rows();
		int number_of_rows(std::string column_name);
		int number_of_rows(int column_idx);
	
		// The column is given a numeric name.
		int add_column();
		int add_column(std::string column_name);
		int add_column(std::string column_name, std::vector<double> & data);

		// Add a row at the bottom of the table. To make the rectangular,
		// some columns may be filled in with their fill values.
		void add_row(std::vector<double> row_data);

		// Get a column:
		std::vector<double> & operator[](int column_index);
		std::vector<double> & operator[](std::string column_name);
		std::vector<double> & column(int column_index);
		std::vector<double> & column(std::string column_name);
		std::vector<double> read_row(int index);
		void set_row(std::vector<double> row, int index);


		// Fills shorter columns with default values such that they match 
		// the lneght of the longest column.
		void fill_to_match_columns();

		// Set a default value to assign to variables in a column.
		void fill_value(int column_idx, double desired_value);
		// Get the value used to fill in data not given by the user.
		double fill_value(std::string column_heading);
		double fill_value(int column_index);
		// Set default fill value.
		void default_fill_value(double new_value);
		// Returns the default fill value.
		double default_fill_value();

		// Get the name of a column of index column_idx
		std::string column_name(int column_idx);
		// Get the column index of a column with head column name.
		int column_index(std::string column_name);

	private:

		std::vector<std::string> m_data_names;
		std::vector<std::vector<double>> m_data;

		// When a 'cell' of the table needs filling, but no value 
		// is explicitly supplied by the user, this is used.
		std::vector<double> m_fill_values;
		// And a default value for it:
		double m_default_fill_value;

		// Return false if the size of m_data, m_data_names or 
		// m_fill_values is different
		bool check_matching_sizes();




	};
}
