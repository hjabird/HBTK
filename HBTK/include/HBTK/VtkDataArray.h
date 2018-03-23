#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkDataArray.h

An analogue of the DataArray part of a VTK file.

Copyright 2018 HJA Bird

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

#include <string>
#include <vector>

#include "CartesianVector.h"

namespace HBTK {
	namespace Vtk {
		class VtkDataArrayTypeless {
		public:
			virtual ~VtkDataArrayTypeless() = 0;

			// Name of the data eg. Temperature
			std::string name;

			// Number of pieces of data:
			virtual int size() = delete;
			// Number of components to each piece of data:
			virtual int number_of_components();

			// Get data out of an index.
			// The following will try to cast to correct types. A exception will
			// be thrown if the number of components is wrong.
			virtual double get_double(int idx) = 0;
			virtual int get_int(int idx) = 0;
			virtual HBTK::CartesianVector3D get_vector(int idx) = 0;
		protected:
			VtkDataArrayTypeless();
			VtkDataArrayTypeless(int number_of_components);
			int m_number_of_components;
		};


		template<typename Tnumeric_type>
		class VtkDataArray 
			: public VtkDataArrayTypeless
		{
		public:
			VtkDataArray();
			VtkDataArray(int number_of_components);
			~VtkDataArray() override;

			// The type contained:
			typedef Tnumeric_type data_type;

			// Data array
			std::vector<Tnumeric_type> raw_data;

			// The following will try to cast to correct types. A exception will
			// be thrown if the number of components is wrong.
			double get_double(int idx) override;
			int get_int(int idx) override;
			HBTK::CartesianVector3D get_vector(int idx) override;
		};

		template<typename Tnumeric_type>
		inline VtkDataArray<Tnumeric_type>::VtkDataArray()
			: VtkDataArrayTypeless(1)
		{
		}

		template<typename Tnumeric_type>
		inline VtkDataArray<Tnumeric_type>::VtkDataArray(int number_of_components)
			: VtkDataArrayTypeless(number_of_components)
		{
		}

		template<typename Tnumeric_type>
		inline VtkDataArray<Tnumeric_type>::~VtkDataArray()
		{
		}

		template<typename Tnumeric_type>
		inline double VtkDataArray<Tnumeric_type>::get_double(int idx)
		{
			if (m_number_of_components != 1) { throw; };
			return (double) raw_data[idx];
		}

		template<typename Tnumeric_type>
		inline int VtkDataArray<Tnumeric_type>::get_int(int idx)
		{
			if (m_number_of_components != 1) { throw; };
			return (int)raw_data[idx];
		}

		template<typename Tnumeric_type>
		inline HBTK::CartesianVector3D VtkDataArray<Tnumeric_type>::get_vector(int idx)
		{
			if (m_number_of_components != 3) { throw; };
			HBTK::CartesianVector3D vect;
			idx *= 3;
			vect.x() = (double)raw_data[idx];
			vect.y() = (double)raw_data[idx + 1];
			vect.z() = (double)raw_data[idx + 2];
			return vect;
		}

	}
}


