
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

	std::vector<double> points, weights;
	std::tie(points, weights) = HBTK::gauss_chebyshev1(4);

	for (int i = 0; i < (int)points.size(); i++) {
		std::cout << points[i] << "\t" << weights[i] << "\n";
	}
	return 0;
}