#include "stdafx.h"
#include "GnuPlot.h"
/*////////////////////////////////////////////////////////////////////////////
GnuPlot.cpp

A MATLAB-like interface to GNUPlot.

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

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include "Generators.h"

namespace HBTK {
	GnuPlot::GnuPlot()
	{
		m_auto_replot_bool = true;
		m_hold_on_bool = false;
		m_grid_on = false;
		m_key_on = false;
		m_canvas_xsize = 600;
		m_canvas_ysize = 400;
		m_terminal_type = "wxt";
		m_default_line_specs = { "k-+", "b-x", "r-o", "g-d", "c-*", "m-^", "y-v" };
		m_xrange_set = false;
		m_yrange_set = false;

	// We need piped gnuplot on Windows.
#ifdef _MSC_VER
		m_gnuplot_pipe = _popen("gnuplot -persist > /nul 2>&1", "w");
#else
		m_gnuplot_pipe = popen("gnuplot", "w");
#endif
		if (!m_gnuplot_pipe) {
			std::cout << "Unable to initialise pipe to GNU Plot.\n";
		}
	} // End initialiser


	GnuPlot::~GnuPlot()
	{
		if (m_gnuplot_pipe) {
			fprintf(m_gnuplot_pipe, "exit\n");
#ifdef _MSC_VER
			_pclose(m_gnuplot_pipe);
#else
			pclose(m_gnuplot_pipe);
#endif
		}
	}

	bool GnuPlot::plot(std::vector<double> Y)
	{
		if (!m_hold_on_bool && plotting_data_already()) { clear(); }
		add_data_set(Y);
		add_line_specification(translate_matlab_linespec("k-"));
		auto_replot();
		return true;
	}

	bool GnuPlot::plot(std::vector<double> X, std::vector<double> Y)
	{
		std::string ln_spec = m_default_line_specs[m_Xs.size()];
		return plot(X, Y, ln_spec);
	}

	bool GnuPlot::plot(std::vector<double> X, std::vector<double> Y, std::string line_spec)
	{
		if (!m_hold_on_bool && plotting_data_already()) { clear(); }
		add_data_set(X, Y);
		add_line_specification(translate_matlab_linespec(line_spec));
		auto_replot();
		return true;
	}

	bool GnuPlot::plot(std::function<double(double)> func, double x_min, double x_max)
	{
		assert(func);
		auto x = HBTK::linspace(x_min, x_max, 300);
		std::vector<double> y;
		y.reserve(x.size());
		std::transform(x.begin(), x.end(), std::back_inserter(y), func);
		plot(x, y);
		return true;
	}

	bool GnuPlot::plot(std::function<double(double)> func, double x_min, double x_max, std::string line_spec)
	{
		assert(func);
		auto x = HBTK::linspace(x_min, x_max, 300);
		std::vector<double> y;
		y.reserve(x.size());
		std::transform(x.begin(), x.end(), std::back_inserter(y), func);
		plot(x, y, line_spec);
		return false;
	}

	void GnuPlot::title(std::string str)
	{
		m_title = str;
		auto_replot();
	}

	void GnuPlot::xlabel(std::string label)
	{
		m_xlabel = label;
		auto_replot();
	}

	void GnuPlot::ylabel(std::string label)
	{
		m_ylabel = label;
		auto_replot();
	}

	void GnuPlot::zlabel(std::string label)
	{
		m_zlabel = label;
		auto_replot();
	}

	void GnuPlot::legend(std::vector<std::string> labels)
	{
		m_data_names = labels;
		m_key_on = true;
	}

	bool GnuPlot::hold_on()
	{
		if (m_gnuplot_pipe) {
			m_hold_on_bool = true;
			return true;
		}
		return false;
	}

	bool GnuPlot::hold_off()
	{
		if (m_gnuplot_pipe) {
			m_hold_on_bool = false;
			return true;
		}
		return false;
	}

	bool GnuPlot::grid_on()
	{
		m_grid_on = true;
		return true;
	}

	bool GnuPlot::grid_off()
	{
		m_grid_on = false;
		return true;
	}

	bool GnuPlot::replot()
	{
		if (m_gnuplot_pipe) {
			if (m_Xs.size() > 0) {
				real_plot();
			}
			return true;
		}
		return false;
	}

	bool GnuPlot::replot_on()
	{
		if (m_gnuplot_pipe) {
			m_auto_replot_bool = true;
			return true;
		}
		return false;
	}

	bool GnuPlot::replot_off()
	{
		if (m_gnuplot_pipe) {
			m_auto_replot_bool = false;
			return true;
		}
		return false;
	}

	bool GnuPlot::key_on()
	{
		m_key_on = true;
		return true;
	}

	bool GnuPlot::key_off()
	{
		m_key_on = false;
		return true;
	}

	bool GnuPlot::xrange(double x_min, double x_max)
	{
		if (x_min != x_max) {
			m_xrange_set = true;
			m_x_max = x_max;
			m_x_min = x_min;
			return true;
		}
		else {
			return false;
		}
	}

	bool GnuPlot::yrange(double y_min, double y_max)
	{
		if (y_min != y_max) {
			m_yrange_set = true;
			m_y_max = y_max;
			m_y_min = y_min;
			return true;
		}
		else {
			return false;
		}
	}

	void GnuPlot::real_plot()
	{
		assert(m_Xs.size() > 0);
		assert(m_Xs.size() == m_Ys.size());
		assert(m_Xs.size() == m_Zs.size());
		assert(m_Xs.size() == m_line_specifications.size());

		int item_count = (int) m_Xs.size();
		std::string tmp_line;

		for (int idx = 0; idx < item_count; idx++) {
			set_linetype(idx+1, m_line_specifications[idx]);
		}

		send_title_and_axis_labels_to_gnuplot_pipe(); 
		axis_scale_to_gnuplot_pipe();
		send_canvas_size_to_gnuplot_pipe();
		send_grid_setting_to_gnuplot_pipe();
		send_key_setting_to_gnuplot_pipe();
		send_axis_setting_to_gnuplot_pipe(); 
		send_range_setting_to_gnuplot_pipe();

		// Main line
		tmp_line = "plot ";
		for (int idx = 0; idx < item_count; idx++) {
			tmp_line += "'-' ";
			if (idx < (int)m_data_names.size()) {
				tmp_line += "title \"" + m_data_names[idx] + "\" ";
			}
			tmp_line += "with linespoints lt " + std::to_string(idx+1);
			if (idx + 1 < item_count) { tmp_line += ", "; }
		}
		tmp_line += "\n";
		if (m_gnuplot_pipe) {
			fprintf(m_gnuplot_pipe, tmp_line.c_str());
		}

		// Input data
		for (int idx = 0; idx < item_count; idx++) {
			write_data_to_gnuplot_pipe(idx);
		}
		return;
	}

	void GnuPlot::auto_replot()
	{
		if (m_auto_replot_bool) {
			if (m_Xs.size() > 0) {
				real_plot();
			}
		}
		return;
	}

	bool GnuPlot::set_linetype(int linetype_id, std::string line_specification)
	{
		assert(linetype_id >= 1);
		if (!m_gnuplot_pipe) {
			return false;
		}
		fprintf(m_gnuplot_pipe, "set linetype %d %s\n", linetype_id, line_specification.c_str());
		return true;
	}

	bool GnuPlot::write_data_to_gnuplot_pipe(int data_idx)
	{
		assert(data_idx >= 0);
		assert(data_idx < (int)m_Xs.size());
		assert(m_Xs[data_idx].size() == m_Ys[data_idx].size());
		assert(m_Xs[data_idx].size() == m_Zs[data_idx].size());
		if (!m_gnuplot_pipe) {
			return false;
		}
		int num_coords = (int)m_Xs[data_idx].size();
		for (int idx = 0; idx < num_coords; idx++) {
			fprintf(m_gnuplot_pipe, "%E %E %E\n", m_Xs[data_idx][idx], 
				m_Ys[data_idx][idx], m_Zs[data_idx][idx]);
		}
		fprintf(m_gnuplot_pipe, "e\n");
		fflush(m_gnuplot_pipe);
		return true;
	}

	bool GnuPlot::send_title_and_axis_labels_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe){
			if (!m_title.empty()) { fprintf(m_gnuplot_pipe, "set title \"%s\"\n", m_title.c_str()); }
			if (!m_xlabel.empty()) { fprintf(m_gnuplot_pipe, "set xlabel \"%s\"\n", m_xlabel.c_str()); }
			if (!m_ylabel.empty()) { fprintf(m_gnuplot_pipe, "set ylabel \"%s\"\n", m_ylabel.c_str()); }
			if (!m_zlabel.empty()) { fprintf(m_gnuplot_pipe, "set zlabel \"%s\"\n", m_zlabel.c_str()); }
			return true;
		}
		return false;
	}

	bool GnuPlot::axis_scale_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe) {
			if (!m_scale_string.empty()) {
				fprintf(m_gnuplot_pipe, "set %s\n", m_scale_string.c_str());
			}
		}
		return false;
	}

	bool GnuPlot::send_canvas_size_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe) {
			fprintf(m_gnuplot_pipe, "set term %s size %d, %d\n",
				m_terminal_type.c_str(), m_canvas_xsize, m_canvas_ysize);
			return true;
		}
		return false;
	}

	bool GnuPlot::send_grid_setting_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe) {
			fprintf(m_gnuplot_pipe, "%s grid\n", (m_grid_on ? "set" : "unset"));
			return true;
		}
		return false;
	}

	bool GnuPlot::send_key_setting_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe) {
			fprintf(m_gnuplot_pipe, "%s key\n", (m_key_on ? "set" : "unset"));
			return true;
		}
		return false;
	}

	bool GnuPlot::send_axis_setting_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe) {
			if (m_axis_equal_on) {
				fprintf(m_gnuplot_pipe, "set size ratio -1\n");
			}
			else {
				// Cross that bridge when we come to it?
			}
		}
		return false;
	}

	bool GnuPlot::send_range_setting_to_gnuplot_pipe()
	{
		if (m_gnuplot_pipe) {
			if (m_xrange_set) {
				fprintf(m_gnuplot_pipe, "set xrange [%E : %E]\n", m_x_min, m_x_max);
			}
			else {
				// Cross that bridge when we come to it?
			}
			if (m_yrange_set) {
				fprintf(m_gnuplot_pipe, "set yrange [%E : %E]\n", m_y_min, m_y_max);
			}
			else {
				// Cross that bridge when we come to it?
			}
		}
		return false;
	}

	bool GnuPlot::clear()
	{
		m_Xs.clear();
		m_Ys.clear();
		m_Zs.clear();
		m_data_names.clear();
		m_line_specifications.clear();
		m_title = "";
		m_xlabel = "";
		m_ylabel = "";
		m_zlabel = "";
		m_scale_string = "";
		m_canvas_xsize = 600;
		m_canvas_ysize = 400;
		if (m_gnuplot_pipe) {
			fprintf(m_gnuplot_pipe, "clear\n");
			fflush(m_gnuplot_pipe);
			return true;
		}
		return false;
	}

	void GnuPlot::logscale(std::string axis)
	{
		logscale(axis, 10);
		return;
	}

	void GnuPlot::logscale(std::string axis, int base)
	{
		assert(base > 1);
		m_scale_string = "logscale " + axis + " " + std::to_string(base);
		return;
	}

	void GnuPlot::axis_equal_on()
	{
		m_axis_equal_on = true;
		return;
	}

	void GnuPlot::axis_equal_off()
	{
		m_axis_equal_on = false;
		return;
	}

	void GnuPlot::size(int x_size, int y_size)
	{
		assert(x_size > 0);
		assert(y_size > 0);
		m_canvas_xsize = x_size;
		m_canvas_ysize = y_size;
		auto_replot();
		return;
	}

	bool GnuPlot::plotting_data_already()
	{
		if (m_Xs.size() > 0) {
			return true;
		}
		return false;
	}

	void GnuPlot::add_data_set(std::vector<double> & Xs, std::vector<double> & Ys, std::vector<double> & Zs)
	{
		assert(Xs.size() == Ys.size());
		assert(Xs.size() == Zs.size());
		assert(Xs.size() > 0);
		m_Xs.emplace_back(Xs);
		m_Ys.emplace_back(Ys);
		m_Zs.emplace_back(Zs);
		return;
	}

	void GnuPlot::add_data_set(std::vector<double>& Xs, std::vector<double>& Ys)
	{
		assert(Xs.size() > 0);
		assert(Xs.size() == Ys.size());

		std::vector<double> Zs(Xs.size(), 0.0);
		add_data_set(Xs, Ys, Zs);
		return;
	}

	void GnuPlot::add_data_set(std::vector<double>& Ys)
	{
		assert(Ys.size() > 0);
		std::vector<double> Xs(Ys.size());
		for (int i = 0; i < (int)Xs.size(); i++) {
			Xs[i] = (double)i;
		}
		add_data_set(Xs, Ys);
		return;
	}

	void GnuPlot::add_line_specification(std::string line_spec)
	{
		m_line_specifications.emplace_back(line_spec);
	}

	std::string GnuPlot::translate_matlab_linespec(std::string line_spec)
	{
		int length = (int)line_spec.size();
		std::string colour = "black";
		std::string marker = "0";
		std::string dashes = "solid";
		std::string result;


		for (int idx = 0; idx < length; idx++) {
			switch( line_spec.c_str()[idx] ){
			case 'b':
				colour = "rgb \"blue\""; // no. 3
				break;
			case 'c':
				colour = "5"; //lightblue
				break;
			case 'g':
				colour = "2";
				break;
			case 'k':
				colour = "7";
				break;
			case 'r':
				colour = "rgb \"red\"";
				break;
			case 'm':
				colour = "4";
				break;
			case 'y':
				colour = "6";
				break;
			case 'w':
				colour = "white";
				break;
			case '-':
				dashes = "1"; //solid / 1
				if (idx + 1 < length && line_spec.c_str()[idx + 1] == '-') {
					dashes = "2";//dashes
				}
				else if (idx + 1 < length && line_spec.c_str()[idx + 1] == '-.') {
					dashes = "5"; //dot dashed
				}
				break;
			case ':':
				dashes = "4"; //dotted
				break;
			case '+':
				marker = "1";
				break;
			case 'x':
				marker = "2";
				break;
			case '*':
				marker = "3";
				break;
			case 's':
				marker = "4";
				break;
			case 'o':
				marker = "6";
				break;
			case '^':
				marker = "8";
				break;
			case 'v':
				marker = "10";
				break;
			case 'd':
				marker = "12";
				break;
			case '>':
			case '<':
			case 'p':
			case 'h':
				marker = "1";
				break;
			};
		}

		result = " lt " + dashes + " lc " + colour + " pt " + marker;
		return result;
	}



}
