/*////////////////////////////////////////////////////////////////////////////
RemapsTests_demp.cpp

A program to demonstate non-linear remaps in HBTK/remaps.h.

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
#include <cmath>
#include <functional>
#include <iostream>

#include <HBTK/GaussLegendre.h>
#include <HBTK/Generators.h>
#include <HBTK/GnuPlot.h>
#include <HBTK/Integrators.h>
#include <HBTK/Remaps.h>


void add_to_plot(std::function<double(double)> func, std::function<void(double&, double&)> remapper,
	HBTK::GnuPlot & plt, double true_sol, std::string l_spec)
{
	assert(true_sol != 0);
	int pts = 39;
	std::vector<double> points, weights, Xs, Ys;
	points.resize(pts);
	weights.resize(pts);
	Xs.resize(pts);
	Ys.resize(pts);

	for (auto idx = 0; idx < pts; idx++) {
		Xs[idx] = 1 + idx;
		HBTK::gauss_legendre<double, std::vector<double>>( idx + 1, points, weights);
		for (auto idx2 = 0; idx2 < idx + 1; idx2++) {
			remapper(points[idx2], weights[idx2]);
		}

		Ys[idx] = abs((HBTK::static_integrate(func, points, weights, idx + 1) - true_sol) / true_sol);
	}

	plt.hold_on();
	plt.plot(Xs, Ys, l_spec);
	return;
}


void singular_plot_1(std::function<double(double)> func, double true_int, std::string name) {

	auto no_op = [](double & p, double & w) { return; };
	auto t2 = [](double & p, double & w) { HBTK::telles_quadratic_remap(p, w, -1.); };
	auto t3 = [](double & p, double & w) { HBTK::telles_cubic_remap(p, w, -1.); };
	auto s3 = [](double & p, double & w) { HBTK::sato_remap<3>(p, w, -1.); };
	auto s4 = [](double & p, double & w) { HBTK::sato_remap<4>(p, w, -1.); };
	auto s5 = [](double & p, double & w) { HBTK::sato_remap<5>(p, w, -1.); };
	auto s6 = [](double & p, double & w) { HBTK::sato_remap<6>(p, w, -1.); };

	HBTK::GnuPlot plt;
	plt.hold_on();
	plt.replot_off();
	add_to_plot(func, no_op, plt, true_int, "r-+");
	add_to_plot(func, t2, plt, true_int, "b-o");
	add_to_plot(func, t3, plt, true_int, "g-d");
	add_to_plot(func, s3, plt, true_int, "y-v");
	add_to_plot(func, s4, plt, true_int, "c->");
	add_to_plot(func, s5, plt, true_int, "k-<");
	add_to_plot(func, s6, plt, true_int, "m-x");
	plt.title("Effect of integral remaps on " + name);
	plt.ylabel("Rel error");
	plt.xlabel("Gauss points");
	plt.logscale("yx");
	plt.legend({ "No remap", "Telles2", "Telles3", "Sato3", "Sato4", "Sato5", "Sato6" });
	plt.replot();
	
	system("pause");
	return;
}

void singular_plot_2(std::function<double(double)> func, double true_int, std::string name) {

	auto no_op = [](double & p, double & w) { return; };
	auto t2s = [](double & p, double & w) { 
		if (p >= 0) {
			HBTK::linear_remap(p, w, 0.1, 1., -1., 1.);
			HBTK::telles_quadratic_remap(p, w, -1.);
			HBTK::linear_remap(p, w, -1., 1., 0.1, 1.);
		}
		else {
			HBTK::linear_remap(p, w, -1., 0.1, -1., 1.);
			HBTK::telles_quadratic_remap(p, w, 1.);
			HBTK::linear_remap(p, w, -1., 1., -1., 0.1);
		}
		return;
	};
	auto t3 = [](double & p, double & w) { HBTK::telles_cubic_remap(p, w, 0.); };
	auto d4 = [](double & p, double & w) { HBTK::doblare_remap(p, w, 0.); };

	HBTK::GnuPlot plt;
	plt.hold_on();
	plt.replot_off();
	add_to_plot(func, no_op, plt, true_int, "r-+");
	add_to_plot(func, t2s, plt, true_int, "b-o");
	add_to_plot(func, t3, plt, true_int, "g-d");
	add_to_plot(func, d4, plt, true_int, "c-x");
	plt.title("Effect of integral remaps on " + name);
	plt.ylabel("Rel error");
	plt.xlabel("Gauss points");
	plt.logscale("yx");
	plt.legend({ "No remap", "Telles2 split", "Telles3", "Doblare" });
	plt.replot();

	system("pause");
	return;
}

void see_transform_value_1(std::function<void(double&, double&)> func,  HBTK::GnuPlot & plt){
	double ignored_paramenter = 1;
	const int n_pts = 50;
	auto X = HBTK::linspace(-1, 1, n_pts);
	auto Y = X;
	for (auto &a : Y) { func(a, ignored_paramenter); }
	plt.plot(X, Y);
	return;
}

void see_transform_jacobian_1(std::function<void(double&, double&)> func, HBTK::GnuPlot & plt) {
	const int n_pts = 50;
	std::vector<double> Y(n_pts, 1.);
	auto X = HBTK::linspace(-1, 1, n_pts);
	auto ETA = X;
	for (int idx = 0; idx < n_pts; idx++) { func(ETA[idx], Y[idx]); }
	plt.plot(X, Y);
	return;
}

void see_transform_g_1(std::function<void(double&, double&)> func, HBTK::GnuPlot & plt, std::function<double(double)> kernal) {
	const int n_pts = 50;
	std::vector<double> Y(n_pts, 1.);
	auto X = HBTK::linspace(-1, 1, n_pts);
	auto XO = X;
	for (int idx = 0; idx < n_pts; idx++) { 
		func(X[idx], Y[idx]); 
		Y[idx] = kernal(X[idx]) * Y[idx];
	}
	plt.plot(XO, Y);
	return;
}

auto plot_remaps_1(std::function<double(double)> kernal)->void {
	auto no_op = [](double & p, double & w) { return; };
	auto t2 = [](double & p, double & w) { HBTK::telles_quadratic_remap(p, w, -1.); };
	auto t3 = [](double & p, double & w) { HBTK::telles_cubic_remap(p, w, 0.4); };
	auto s4 = [](double & p, double & w) { HBTK::sato_remap<4>(p, w, -1.); };
	auto s5 = [](double & p, double & w) { HBTK::sato_remap<5>(p, w, -1.); };
	auto s6 = [](double & p, double & w) { HBTK::sato_remap<6>(p, w, -1.); };
	auto d4 = [](double & p, double & w) { HBTK::doblare_remap(p, w, 0.4); };
	HBTK::GnuPlot val_plt, jac_plt;
	val_plt.title("G"); val_plt.hold_on(); val_plt.replot_off();
	jac_plt.title("Jacobians"); jac_plt.hold_on(); jac_plt.replot_off();
	for (auto &a : std::vector<std::function<void(double&, double&)>>{ no_op, t2, t3, s4, s5, s6, d4 }) {
		see_transform_g_1(a, val_plt, kernal);
		see_transform_jacobian_1(a, jac_plt);
	}
	val_plt.legend({ "No op", "Telles2", "Telles3", "Sato4", "Sato5", "Sato6", "Doblare@0.1" });
	jac_plt.legend({ "No op", "Telles2", "Telles3", "Sato4", "Sato5", "Sato6", "Doblare@0.1" });
	val_plt.yrange(-3, 3);
	val_plt.replot();
	jac_plt.replot();
	system("pause");
}

void inf_limit_plot_1(std::function<double(double)> func, double true_int, std::string name)
{
	auto exp = [](double & p, double & w) { HBTK::exponential_remap(p, w, 1.); };

	HBTK::GnuPlot plt;
	plt.logscale("xy");
	plt.title("Error of integral remap on " + name);
	plt.xlabel("Number of GL points");
	plt.ylabel("Relative error");
	add_to_plot(func, exp, plt, true_int, "r-");
	system("pause");
	return;
}



int main()
{
	std::cout << "Remap tests demo\n";

	plot_remaps_1([](double x) {return log(abs(x - 0.4)); });
	plot_remaps_1([](double x) {return 1.0 / abs(x - 0.4); });

	// -1, 1, singularity at -1
	auto logf = [](double x) { return log(x + 1); };
	auto logk10f = [](double x) { return log(10 * (x + 1)); };
	auto rsqrtf = [](double x) { return 1. / sqrt(1 + x); };

	auto logv = -0.6137056388801094;
	auto logk10v = 3.991464547107982;
	auto rsqrtv = 2.828427124746191;

	//singular_plot_1(logf, logv, "log(x+1)");
	//singular_plot_1(logk10f, logk10v, "log(10x+10)");
	//singular_plot_1(rsqrtf, rsqrtv, "1 / sqrt(1+x)");

	// -1, 1, singularity at 0.1
	auto logabsf = [](double x) { return log(abs(x-0.1)); };
	auto cvpintf = [](double x) { return 1 / (x-0.1); };
	auto logabsv = -2.;
	auto cvpintv = -0.2006706954621512;

	//singular_plot_2(logabsf, logabsv, "log(abs(x-0.1))");
	//singular_plot_2(cvpintf, cvpintv, "1/(x-0.1)");

	// 1 to infty
	auto sincf = [](double x) { return sin(x-1) / (x-1); };
	auto exppolyf = [](double x) { return exp(-x)*((sqrt(x*x - 1) - x) / x); };
	auto sincv = 1.570796326794897;
	auto exppolyv = -0.09425868914448465;

	//inf_limit_plot_1(sincf, sincv, "sin(x) / x");
	//inf_limit_plot_1(exppolyf, exppolyv, "Sclavounos 3.21 term 1 on RHS");

	// Unknown_solution [-1, 1], singularity central
	// Sclavounos1987 with N = 1
	auto sclavsteadyf = [](double x) {
		auto theta = acos(x);
		auto r = -3. * cos(3 * theta) / (sqrt(1 - x*x) * x);
		return r;
	};

    return 0;
}

