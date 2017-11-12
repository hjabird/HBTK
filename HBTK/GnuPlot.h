#pragma once

#include <vector>
#include <fstream>

namespace HBTK {
	class GnuPlot
	{
	public:
		GnuPlot();
		~GnuPlot();

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
		std::string m_terminal_type;
	};
}
