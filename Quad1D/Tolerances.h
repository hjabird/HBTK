#pragma once

namespace Quad1D {

	/// \brief returns the tolerance of a type Ty.
	///
	/// Useage:
	/// \code Ty tol = Quad1D::tolerance<double>() \endcode
	template < typename Ty >
	constexpr Ty tolerance(void);

	/// \brief returns the tolerance of double (10^-15)
	/// \code double tol = Quad1D::tolerance<double>() \endcode
	template <>
	constexpr double tolerance<double>(void) 
	{
		return 1e-15;
	}


	/// \brief returns the tolerance of double (10^-7)
	/// \code float tol = Quad1D::tolerance<float>() \endcode
	template <>
	constexpr float tolerance<float>(void)
	{
#pragma warning(suppress: 4305)
		return 1e-7;
	}



}