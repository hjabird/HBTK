
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

#include <HBTK/GaussianQuadrature.h>


int main()
{

	bool silent_flag = false;
    if(! silent_flag){
        std::cout << "Gauss Quadrature demo\n";
		std::cout << "Copyright HJA Bird 2018\n\n";
    }

	HBTK::StaticQuadrature quad = HBTK::gauss_hermite(4);
	std::vector<double> points, weights;
	std::tie(points, weights) = quad.get_quadrature();
	auto simple = [](double x) { return 1; };
	double result = quad.integrate(simple);

	for (int i = 0; i < (int)points.size(); i++) {
		std::cout << points[i] << "\t" << weights[i] << "\n";
	}
	return 0;
}