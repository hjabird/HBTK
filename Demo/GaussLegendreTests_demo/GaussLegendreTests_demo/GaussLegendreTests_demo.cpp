
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

#include <HBTK/GaussLegendre.h>
#include <HBTK/GnuPlot.h>
#include <HBTK/Constants.h>
#include <HBTK/Integrators.h>


int main()
{
	std::cout << "GaussLegendreTests demo\n\n";
	
	auto max_gl_points = 150;
	auto min_gl_points = 1;
	auto num_experiments = max_gl_points - min_gl_points;
	std::vector<double> points, weights;
	std::vector<float> pointsf, weightsf;
	
	std::vector<double> num_points, times, timesf, polynomial, cos8, cos20, exp4, recsqrt, logarithm;
	num_points.resize(num_experiments);
	times.resize(num_experiments);
	timesf.resize(num_experiments);
	polynomial.resize(num_experiments);
	cos8.resize(num_experiments);
	cos20.resize(num_experiments);
	exp4.resize(num_experiments);
	recsqrt.resize(num_experiments);
	logarithm.resize(num_experiments);

	auto polyfunc = [](double x) { return 2 + 3 * x + x*x - x*x*x + 5 * x*x*x*x; };
	auto cos8func = [](double x) { return cos(8 * x / HBTK::Constants::pi()); };
	auto cos20func = [](double x) { return cos(20 * x / HBTK::Constants::pi()); };
	auto exp4func = [](double x) { return exp(4 * x); };
	auto recsqrtfunc = [](double x) { return 1. / sqrt(x + 1.); };
	auto logarithmfunc = [](double x) { return log(x + 1); };

	for (auto idx = 0; idx < num_experiments; idx++) {
		num_points[idx] = idx + min_gl_points;
		points.resize((int)num_points[idx]);
		weights.resize((int)num_points[idx]);
		pointsf.resize((int)num_points[idx]);
		weightsf.resize((int)num_points[idx]);

		auto start = std::chrono::steady_clock::now();
		HBTK::gauss_legendre<double, std::vector<double>>((int)num_points[idx], points, weights);
		auto end = std::chrono::steady_clock::now();
		times[idx] = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();

		start = std::chrono::steady_clock::now();
		HBTK::gauss_legendre<float, std::vector<float>>((int)num_points[idx], pointsf, weightsf);
		end = std::chrono::steady_clock::now();
		timesf[idx] = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();

		polynomial[idx] = HBTK::static_integrate(polyfunc, points, weights, (int)num_points[idx]);
		cos8[idx] = HBTK::static_integrate(cos8func, points, weights, (int)num_points[idx]);
		cos20[idx] = HBTK::static_integrate(cos20func, points, weights, (int)num_points[idx]);
		exp4[idx] = HBTK::static_integrate(exp4func, points, weights, (int)num_points[idx]);
		recsqrt[idx] = HBTK::static_integrate(recsqrtfunc, points, weights, (int)num_points[idx]);
		logarithm[idx] = HBTK::static_integrate(logarithmfunc, points, weights, (int)num_points[idx]);

		polynomial[idx] = abs((polynomial[idx] - (20. / 3)) / (20. / 3));
		cos8[idx] = abs((cos8[idx] - 0.4402964086037879) / 0.4402964086037879);
		cos20[idx] = abs((cos20[idx] - 0.02604917796505642) / 0.02604917796505642);
		exp4[idx] = abs((exp4[idx] - 13.64495859856387) / 13.64495859856387);
		recsqrt[idx] = abs((recsqrt[idx] - 2.828427124746191) / 2.828427124746191);
		logarithm[idx] = abs((logarithm[idx] + 0.6137056388801094) / 0.6137056388801094);
	}

	HBTK::GnuPlot time_plt, acc_plt;
	time_plt.title("Time to generate Gauss-Legendre quadrature");
	time_plt.xlabel("Number of quadrature points");
	time_plt.ylabel("Time taken");
	time_plt.logscale("xy");
	time_plt.legend({ "double", "float" });
	time_plt.hold_on();
	time_plt.plot(num_points, times, "b-");
	time_plt.plot(num_points, timesf, "r-");

	acc_plt.title("Relative accuracty of Gauss-Legendre quadrature in  x in [-1, 1]");
	acc_plt.xlabel("Number of quadrature points");
	acc_plt.ylabel("abs( error / true_value)");
	acc_plt.replot_off();
	acc_plt.hold_on();
	acc_plt.plot(num_points, polynomial, "r-");
	acc_plt.plot(num_points, cos8, "b-");
	acc_plt.plot(num_points, cos20, "c-");
	acc_plt.plot(num_points, exp4, "g-");
	acc_plt.plot(num_points, recsqrt, "k-");
	acc_plt.plot(num_points, logarithm, "y-");
	acc_plt.logscale("xy");
	acc_plt.legend({ "Polynom O5",  "cos8x/pi", "cos20x/pi", "exp(4*x)", "1/sqrt(x+1)", "log(x+1)" });
	acc_plt.replot_on();
	acc_plt.replot();

	system("pause");
	return 0;
}

