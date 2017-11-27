#pragma once
/*////////////////////////////////////////////////////////////////////////////
GnuPlot.h

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
#include <vector>
#include <fstream>

namespace HBTK {
	class GnuPlot
	{
	public:
		GnuPlot();
		~GnuPlot();    
		GnuPlot(GnuPlot const &) = delete;
		void operator=(GnuPlot const &x) = delete;

		bool plot(std::vector<double> Y);
		bool plot(std::vector<double> X, std::vector<double> Y);
		bool plot(std::vector<double> X, std::vector<double> Y, std::string line_spec);
		bool clear();
		bool replot();

		void title(std::string str);
		void xlabel(std::string label);
		void ylabel(std::string label);
		void zlabel(std::string label);
		void legend(std::vector<std::string> labels);

		bool hold_on();
		bool hold_off();
		bool grid_on();
		bool grid_off();
		bool replot_on();
		bool replot_off();
		bool key_on();
		bool key_off();
		
		void logscale(std::string axis);
		void logscale(std::string axis, int base);
		
		void axis_equal_on();
		void axis_equal_off();

		void size(int x_size, int y_size);

		
	private:

		FILE *m_gnuplot_pipe;
		bool m_auto_replot_bool;
		bool m_hold_on_bool;

		// Plotting data.
		std::vector<std::vector<double>> m_Xs;
		std::vector<std::vector<double>> m_Ys;
		std::vector<std::vector<double>> m_Zs;

		std::vector<std::string> m_data_names;
		std::vector<std::string> m_line_specifications; // In GNUplot terms - not MATLAB!.

		// Strings...
		std::string m_title;
		std::string m_xlabel;
		std::string m_ylabel;
		std::string m_zlabel;
		std::string m_scale_string;

		// Plotting methods.
		void real_plot();
		void auto_replot(); // Calls plot if auto_replot_bool is true

		bool set_linetype(int linetype_id, std::string line_specification);
		bool write_data_to_gnuplot_pipe(int data_idx);
		bool send_title_and_axis_labels_to_gnuplot_pipe();
		bool axis_scale_to_gnuplot_pipe();
		bool send_canvas_size_to_gnuplot_pipe();
		bool send_grid_setting_to_gnuplot_pipe();
		bool send_key_setting_to_gnuplot_pipe();
		bool send_axis_setting_to_gnuplot_pipe();

		// Data handling methods.
		bool plotting_data_already();
		void add_data_set(std::vector<double> & Xs, std::vector<double> & Ys, std::vector<double> & Zs);
		void add_data_set(std::vector<double> & Xs, std::vector<double> & Ys);
		void add_data_set(std::vector<double> & Ys);
		void add_line_specification(std::string line_spec);
		
		// String conversion MATLAB -> GNUPLOT
		std::string translate_matlab_linespec(std::string line_spec);

		// Other
		int m_canvas_xsize, m_canvas_ysize;
		bool m_grid_on;
		bool m_key_on;
		bool m_axis_equal_on;
		std::string m_terminal_type;
	};
}
