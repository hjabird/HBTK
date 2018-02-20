#pragma once
/*////////////////////////////////////////////////////////////////////////////
PotentialFlowDistributions.h

Defines basic potential flow distributions.

Copyright 2017-2018 HJA Bird

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
#include <tuple>

#include "Checks.h"

namespace HBTK
{
	// DECLARATIONS

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

	namespace ConstantVortexDistribution
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1);

		template<typename Ty>
		constexpr std::pair<Ty, Ty> unity_vel(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1);
	}

	namespace LinearVortexDistribution
	{
		template<typename Ty>
		constexpr Ty vel_pot(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1, Ty gamma0, Ty gamma1);

		template<typename Ty>
		constexpr std::pair<Ty, Ty> vel(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1, 
			Ty gamma0, Ty gamma1);

	}

	// DEFINITIONS
		
	namespace PointDoublet
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub) {
			return -1 * (y_mes - y_dub) / (2 * Constants::pi<Ty>()*(pow(x_mes - x_dub, 2) + pow(y_mes - y_dub, 2)));
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub) {
			return (y_mes - y_dub)*(x_mes - x_dub) / (2 * Constants::pi<Ty>()*pow(pow(x_mes - x_dub, 2) + pow(y_mes - y_dub, 2), 2));
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub, Ty angle) {
			return cos(angle) * unity_u_vel(x_mes, y_mes, x_dub, y_dub) - sin(angle) * unity_v_vel(x_mes, y_mes, x_dub, y_dub);
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_dub, Ty y_dub) {
			return -1 * (pow(y_mes - y_dub, 2) - pow(x_mes - x_dub, 2)) / (2 * Constants::pi<Ty>() * pow(pow(x_mes - x_dub, 2) + pow(y_mes - y_dub, 2), 2));
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
			return log(hypot(x_mes - x_sor, y_mes - y_sor, 2)) / (2 * Constants::pi<Ty>());
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor) {
			return (x_mes - x_sor) / (2 * Constants::pi<Ty>()*(pow(x_mes - x_sor, 2) + pow(y_mes - y_sor, 2)));
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_sor, Ty y_sor) {
			return (y_mes - y_sor) / (2 * Constants::pi<Ty>()*(pow(x_mes - x_sor, 2) + pow(y_mes - y_sor, 2)));
		}

	}

	namespace PointVortex 
	{
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor) {
			return -1 * atan2(y_mes - y_vor, x_mes - x_vor) / (2 * Constants::pi<Ty>());
		}

		template<typename Ty>
		constexpr Ty unity_u_vel(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor) {
			return (y_mes - y_vor) / (2 * Constants::pi<Ty>()*(pow(x_mes - x_vor, 2) + pow(y_mes - y_vor, 2)));
		}

		template<typename Ty>
		constexpr Ty unity_v_vel(Ty x_mes, Ty y_mes, Ty x_vor, Ty y_vor) {
			return -1 * (x_mes - x_vor) / (2 * Constants::pi<Ty>()*(pow(x_mes - x_vor, 2) + pow(y_mes - y_vor, 2)));
		}

	}

	namespace ConstantVortexDistribution {
		template<typename Ty>
		constexpr Ty unity_vel_pot(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1)
		{
			Ty length = hypot(x_vor1 - x_vor0, y_vor1 - y_vor0);
			Ty cos_ang = (y_vor1 - y_vor0) / length;
			Ty sin_ang = (x_vor1 - x_vor0) / length;
			// xt and yt indicate that a coordinate has been transformed to a plane where 
			// the vortex panel is now on yt = 0. xtm and ytm indicate the transformed pos
			// of the mesurment point. xt1 yt1 the transformed end 1 of the panel. 
			Ty xtm = (x_mes - x_vor0) * cos_ang - (y_mes - y_vor0) * sin_ang;
			Ty ytm = (x_mes - x_vor0) * sin_ang + (y_mes - y_vor0) * cos_ang - y_vor0;
			Ty xt1 = (x_vor1 - x_vor0) * cos_ang - (y_vor1 - y_vor0) * sin_ang;
			Ty yt1 = 0.0;
			Ty xt0 = x_vor0;
			Ty yt0 = 0.0;
			// Compute velocity potential as Katz2001 Eq 10.37
			Ty term_1, term_2, term_21, term_22, term_23;
			term_1 = -1. / (2 * HBTK::Constants::pi<Ty>());
			term_21 = (xtm - xt0) * atan2(ytm, xtm - xt0);
			term_22 = (xtm - xt1) * atan2(ytm, xtm - xt1);
			term_23 = ytm * log((pow(xtm - xt0, 2) + ytm * ytm) / (pow(xtm - xtm1, 2) + ytm * ytm)) / 2.0;
			term_2 = term_21 - term_22 + term_23;
			Ty val = term_1 * term_2;
			assert(HBTK::check_finite(val));
			return val;
		}

		template<typename Ty>
		constexpr std::pair<Ty, Ty> unity_vel(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1)
		{
			Ty length = hypot(x_vor1 - x_vor0, y_vor1 - y_vor0);
			Ty cos_ang = (y_vor1 - y_vor0) / length;
			Ty sin_ang = (x_vor1 - x_vor0) / length;
			// xt and yt indicate that a coordinate has been transformed to a plane where 
			// the vortex panel is now on yt = 0. xtm and ytm indicate the transformed pos
			// of the mesurment point. xt1 yt1 the transformed end 1 of the panel. 
			Ty xtm = (x_mes - x_vor0) * cos_ang - (y_mes - y_vor0) * sin_ang;
			Ty ytm = (x_mes - x_vor0) * sin_ang + (y_mes - y_vor0) * cos_ang - y_vor0;
			Ty xt1 = (x_vor1 - x_vor0) * cos_ang - (y_vor1 - y_vor0) * sin_ang;
			Ty yt1 = 0.0;
			Ty xt0 = x_vor0;
			Ty yt0 = 0.0;

			// Local u velocity (Katz2001 10.39)
			Ty term_u1, term_u2, term_u21, term_u22;
			term_u1 = 1. / (2 * HBTK::Constants::pi<Ty>());
			term_u21 = atan2(ytm, xtm - xt1);
			term_u22 = atan2(ytm, xtm - xt2);
			term_u2 = term_u21 - term_u22;
			Ty ut = term_u1 * term_u2;
			assert(HBTK::check_finite(ut));
			// Local v velocity (Katz2001 10.40)
			Ty term_v1, term_v2;
			term_v1 = 1. / (4 * HBTK::Constants::pi<Ty>());
			verm_v2 = log((pow(xtm - xt1, 2) + ytm * ytm) / (pow(xtm - xtm0, 2) + ytm * ytm));
			Ty vt = term_v1 * term_v2;
			assert(HBTK::check_finite(vt));

			// Rotate our velocity back into our original reference frame.
			Ty v, u;
			u = cos_ang * u + sin_ang * v;
			v = -sin_ang * u + cos_ang * v;
			return std::make_pair(u, v);
		}

	}

	namespace LinearVortexDistribution {
		template<typename Ty>
		constexpr Ty vel_pot(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1, Ty gamma0, Ty gamma1)
		{
			Ty length = hypot(x_vor1 - x_vor0, y_vor1 - y_vor0);
			Ty cos_ang = (y_vor1 - y_vor0) / length;
			Ty sin_ang = (x_vor1 - x_vor0) / length;
			// xt and yt indicate that a coordinate has been transformed to a plane where 
			// the vortex panel is now on yt = 0. xtm and ytm indicate the transformed pos
			// of the mesurment point. xt1 yt1 the transformed end 1 of the panel. 
			Ty xtm = (x_mes - x_vor0) * cos_ang - (y_mes - y_vor0) * sin_ang;
			Ty ytm = (x_mes - x_vor0) * sin_ang + (y_mes - y_vor0) * cos_ang - y_vor0;
			Ty xt1 = (x_vor1 - x_vor0) * cos_ang - (y_vor1 - y_vor0) * sin_ang;
			Ty yt1 = 0.0;
			Ty xt0 = x_vor0;
			Ty yt0 = 0.0;

			// The part due to the constant part of the distribution.
			Ty velocity_potential = HBTK::ConstantVortexDistribution::unity_vel_pot(
				x_mes, y_mes, x_vor0, y_vor0, x_vor1, y_vor1) * gamma0;
			// The part due to the varying part of the distribution. Katz2001 Eq10.71
			Ty term_1, term_2, term_21, term_22, term_23, term_24;
			term_1 = - gamma1 / (2 * HBTK::Constants::pi<Ty>());
			term_21 = (xtm - xt0) * ytm * log((pow(xtm - xt0, 2) + ytm * ytm) / (pow(xtm - xt1, 2) + ytm * ytm)) / 2.0;
			term_22 = ytm * (xt1 - xt0);
			term_23 = (pow(xtm - xt0, 2) - xt0 * xt0 - ytm * ytm) * atan2(ytm, xtm - xt0) / 2.;
			term_24 = (pow(xtm - xt0, 2) - xt1 * xt1 - ytm * ytm) * atan2(ytm, xtm - xt1) / 2.;
			term_2 = term_21 + term_22 + term_23 - term_24;
			velocity_potential += term_1 * term_2;
			assert(HBTK::check_finite(vel_pot));
			return vel_pot;
		}

		template<typename Ty>
		constexpr std::pair<Ty, Ty> vel(Ty x_mes, Ty y_mes, Ty x_vor0, Ty y_vor0, Ty x_vor1, Ty y_vor1, Ty gamma0, Ty gamma1)
		{
			Ty length = hypot(x_vor1 - x_vor0, y_vor1 - y_vor0);
			Ty cos_ang = (y_vor1 - y_vor0) / length;
			Ty sin_ang = (x_vor1 - x_vor0) / length;
			// xt and yt indicate that a coordinate has been transformed to a plane where 
			// the vortex panel is now on yt = 0. xtm and ytm indicate the transformed pos
			// of the mesurment point. xt1 yt1 the transformed end 1 of the panel. 
			Ty xtm = (x_mes - x_vor0) * cos_ang - (y_mes - y_vor0) * sin_ang;
			Ty ytm = (x_mes - x_vor0) * sin_ang + (y_mes - y_vor0) * cos_ang - y_vor0;
			Ty xt1 = (x_vor1 - x_vor0) * cos_ang - (y_vor1 - y_vor0) * sin_ang;
			Ty yt1 = 0.0;
			Ty xt0 = x_vor0;
			Ty yt0 = 0.0;

			Ty u, v;
			std::tie(u, v) = ConstantVortexDistribution::unity_vel(x_mes, y_mes, x_vor0, y_vor0, x_vor1, y_vor1) * gamma0;

			Ty term_common_1, term_common_2, term_common_21, term_common_22;
			term_common_1 = log((pow(xtm - xt0, 2) + ytm * ytm) / (pow(xtm - xt1, 2) + ytm * ytm));
			term_common_21 = atan2(ytm, xtm - xt1);
			term_common_22 = atan2(ytm, xtm - xt2);
			term_common_2 = term_common_21 - term_common_22;
			// Katz2001 Eq 10.72
			Ty term_u1, term_u2, term_u21, term_u22, ut;
			term_u1 = -gamma1 / (4 * HBTK::Constants::pi<Ty>());
			term_u21 = ytm * term_common_1;
			term_u22 = -2 * xtm * term_common_2;
			term_u2 = term_u21 + term_u22;
			ut = term_u1 * term_u2;
			// Katz2001 Eq10.73
			Ty term_v1, term_v2, term_v21, term_v23, term_v22, vt;
			term_v1 = -gamma1 / (2 * HBTK::Constants::pi<Ty>());
			term_v21 = xtm * term_common_1 / 2.;
			term_v22 = xt0 - xt1;
			term_v23 = ytm * term_common_2;
			term_v2 = term_v21 + term_v22 + term_v23;
			vt = term_v1 * term_v2;

			u += cos_ang * ut + sin_ang * vt;
			v += -sin_ang * ut + cos_ang * vt;
			assert(HBTK::check_finite(u));
			assert(HBTK::check_finite(v));
			return std::make_pair(u, v);
		}

	}

} // END namespace HBTK


