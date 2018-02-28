#include "DoubleTable.h"
/*////////////////////////////////////////////////////////////////////////////
DoubleTable.cpp

Column based storage of numeric data.

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

#include <algorithm>
#include <cassert>
#include <cmath>
#include <stdexcept>

HBTK::DoubleTable::DoubleTable()
	: m_default_fill_value(NAN)
{
}

HBTK::DoubleTable::~DoubleTable()
{
}

int HBTK::DoubleTable::number_of_columns()
{
	assert(check_matching_sizes());
	int num_columns = (int)m_data.size();
	return num_columns;
}

int HBTK::DoubleTable::number_of_rows()
{
	assert(check_matching_sizes());
	int max = 0;
	for (int i = 0; i < (int)m_data.size(); i++) {
		if ((int)m_data[i].size() > max) max = (int)m_data[i].size();
	}
	return max;
}

int HBTK::DoubleTable::number_of_rows(std::string column_name)
{
	int idx = column_index(column_name);
	if (idx == -1) {
		throw std::invalid_argument("HBTK::DoubleTable::number_of_rows(column_name): "
			"string argument column heading (" + column_name + ") did not match"
			" the name of any columns in the table. " __FILE__ ":" +
			std::to_string(__LINE__));
	}
	return (int)m_data[idx].size();
}

int HBTK::DoubleTable::number_of_rows(int column_idx)
{
	assert(check_matching_sizes());
	assert(column_idx < (int)m_data.size());
	return (int)m_data[column_idx].size();
}

int HBTK::DoubleTable::add_column()
{
	std::string name = std::to_string(number_of_columns());
	add_column(name);
	return number_of_columns();
}

int HBTK::DoubleTable::add_column(std::string column_name)
{
	std::vector<double> a_column;
	add_column(column_name, a_column);
	return number_of_columns();
}

int HBTK::DoubleTable::add_column(std::string column_name, std::vector<double> & data)
{
	m_data.emplace_back(data);
	m_data_names.emplace_back(column_name);
	m_fill_values.emplace_back(default_fill_value());
	return number_of_columns();
}

void HBTK::DoubleTable::add_row(std::vector<double> row_data)
{
	assert(check_matching_sizes());
	if ((int)row_data.size() != number_of_columns()) {
		throw std::length_error("HBTK::DoubleTable::add_row(row_data):"
			" row_data size (" + std::to_string(row_data.size()) + ") does not "
			"match the number of columns in the table (" + std::to_string(number_of_columns())
			+ "). " __FILE__ ":" + std::to_string(__LINE__));
	}
	fill_to_match_columns();
	for (int i = 0; i < number_of_columns(); i++) {
		m_data[i].emplace_back(row_data[i]);
	}
	return;
}

std::vector<double>& HBTK::DoubleTable::operator[](int column_index)
{
	return m_data[column_index];
}

std::vector<double>& HBTK::DoubleTable::operator[](std::string column_name)
{
	int col_idx = column_index(column_name);
	if (col_idx < 0) {
		throw std::range_error("HBTK::DoubleTable::operator[](std::string column_name):"
			" column_name " + column_name + " is not a header in the table. "
			__FILE__ ":" + std::to_string(__LINE__));
	}
	return operator[](col_idx);
}

std::vector<double>& HBTK::DoubleTable::column(int column_index)
{
	return operator[](column_index);
}

std::vector<double>& HBTK::DoubleTable::column(std::string column_name)
{
	return operator[](column_name);
}

std::vector<double> HBTK::DoubleTable::read_row(int index)
{
	assert(index >= 0);
	std::vector<double> row(number_of_columns());
	for (int i = 0; i < number_of_columns(); i++) {
		if (index >= (int)m_data[i].size()) {
			row[i] = m_fill_values[i];
		}
		else {
			row[i] = m_data[i][index];
		}
	}

	return row;
}

void HBTK::DoubleTable::set_row(std::vector<double> row, int index)
{
	assert(index >= 0);
	if ((int)row.size() != number_of_columns()) {
		throw std::length_error("HBTK::DoubleTable::set_row(row_data, index):"
			" row_data size (" + std::to_string(row.size()) + ") does not "
			"match the number of columns in the table (" + std::to_string(number_of_columns())
			+ "). " __FILE__ ":" + std::to_string(__LINE__));
	}

	for (int i = 0; i < number_of_columns(); i++) {
		if (index > (int)m_data[i].size()) {
			int original_size = m_data[i].size();
			m_data[i].resize(index + 1);
			for (int j = original_size; j < index; j++) {
				m_data[i][j] = m_fill_values[i];
			}
		}
		m_data[i][index] = row[i];
	}
	return;
}

bool HBTK::DoubleTable::check_matching_sizes()
{
	int num_columns = (int)m_data.size();
	if (num_columns != (int) m_data_names.size()) { return false; }
	if (num_columns != (int)m_fill_values.size()) { return false; }
	return true;
}

void HBTK::DoubleTable::fill_to_match_columns()
{
	int rows_needed = number_of_rows();
	for (int i = 0; i < number_of_columns(); i++) {
		if ((int)m_data[i].size() < number_of_rows()) {
			int column_size = (int)m_data[i].size();
			int difference = rows_needed - column_size;
			m_data[i].resize(rows_needed);
			for (int j = column_size; j < rows_needed; j++) {
				m_data[i][j] = m_fill_values[i];
			}
		}
	}
	return;
}

void HBTK::DoubleTable::fill_value(int column_idx, double desired_value)
{
	m_fill_values[column_idx] = desired_value;
}

double HBTK::DoubleTable::fill_value(std::string column_heading)
{
	int idx = column_index(column_heading);
	if (idx == -1) {
		throw std::invalid_argument("HBTK::DoubleTable::fill_value(column_heading): "
			"string argument column heading (" + column_heading + ") did not match"
			" the name of any columns in the table. " __FILE__ ":" + 
			std::to_string(__LINE__));
	}
	return fill_value(idx);
}

double HBTK::DoubleTable::fill_value(int column_index)
{
	assert(column_index > 0);
	assert(column_index < (int)m_fill_values.size());
	return m_fill_values[column_index];
}

void HBTK::DoubleTable::default_fill_value(double new_value)
{
	m_default_fill_value = new_value;
}

double HBTK::DoubleTable::default_fill_value()
{
	return m_default_fill_value;
}

std::string HBTK::DoubleTable::column_name(int column_idx)
{
	assert(column_idx < (int)m_data_names.size());
	assert(check_matching_sizes());
	return m_data_names[column_idx];
}

int HBTK::DoubleTable::column_index(std::string column_name)
{
	int int_pos;
	auto pos = std::find(m_data_names.begin(), m_data_names.end(), column_name);
	if (pos == m_data_names.end()) { int_pos = -1; }
	else {
		int_pos = (int)(pos - m_data_names.begin());
	}
	return int_pos;
}

