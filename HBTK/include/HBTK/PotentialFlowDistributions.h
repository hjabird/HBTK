#pragma once
/*////////////////////////////////////////////////////////////////////////////
PotentialFlowDistributions.h

Defines basic potential flow distributions.

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

#include <cmath>

namespace HBTK
{

	namespace PointDoublet 
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub);

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub);

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub, Ty angle);

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub);

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub, Ty angle);
	}

	namespace PointSource 
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor);

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor);

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor);
	}

	namespace PointVortex 
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor);

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor);

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor);
	}


		
	namespace PointDoublet
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub) {
			return -1 * (y_mes - y_dub) / (2 * M_PI*(pow(x_mes - x_dub, 2) + pow(y_mes - y_dub, 2)));
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub) {
			return (y_mes - y_dub)*(x_mes - x_dub) / (2 * M_PI*pow(pow(x_mes - x_dub, 2) + pow(y_mes - y_dub, 2), 2));
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub, Ty angle) {
			return cos(angle) * unity_u_vel(x_mes, y_mes, x_dub, y_dub) - sin(angle) * unity_v_vel(x_mes, y_mes, x_dub, y_dub);
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub) {
			return -1 * (pow(y_mes - y_dub, 2) - pow(x_mes - x_dub, 2)) / (2 * M_PI * pow(pow(x_mes - x_dub, 2) + pow(y_mes - y_dub, 2), 2));
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub, Ty angle) {
			return sin(angle) * unity_u_vel(x_mes, y_mes, x_dub, y_dub) + cos(angle) * unity_v_vel(x_mes, y_mes, x_dub, y_dub);
		}

	}

	namespace PointSource 
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor) {
			return log(hypot(x_mes - x_sor, y_mes - y_sor, 2)) / (2 * M_PI);
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor) {
			return (x_mes - x_sor) / (2 * M_PI*(pow(x_mes - x_sor, 2) + pow(y_mes - y_sor, 2)));
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor) {
			return (y_mes - y_sor) / (2 * M_PI*(pow(x_mes - x_sor, 2) + pow(y_mes - y_sor, 2)));
		}

	}

	namespace PointVortex 
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor) {
			return -1 * atan2(y_mes - y_vor, x_mes - x_vor) / (2 * M_PI);
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor) {
			return (y_mes - y_vor) / (2 * M_PI*(pow(x_mes - x_vor, 2) + pow(y_mes - y_vor, 2)));
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor) {
			return -1 * (x_mes - x_vor) / (2 * M_PI*(pow(x_mes - x_vor, 2) + pow(y_mes - y_vor, 2)));
		}

	}
} // END namespace HBTK


