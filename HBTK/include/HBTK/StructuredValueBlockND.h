#pragma once
/*////////////////////////////////////////////////////////////////////////////
StructuredValueBlockND.h

A class to represent a value field in a structured mesh.

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

#include <array>
#include <cassert>
#include <cmath>
#include <iterator>
#include <vector>

#include "StructuredBlockIndexerND.h"


namespace HBTK {
	template<int TNumDimensions, typename TType>
	class StructuredValueBlockND
	{
	public:
		StructuredValueBlockND();
		~StructuredValueBlockND();

		// Set the extent(dimensions) of the structured block
		void extent(std::array<int, TNumDimensions> extents);
		// Get the extent(dimensions) of the structured block;
		std::array<int, TNumDimensions> extent();

		// Get a reference to the value for a coordinate in the 
		// mesh block.
		TType& value(std::array<int, TNumDimensions> coordinate);

		// Swap local coordinates around
		void swap(int first_dim, int second_dim);

	private:
		std::array<int, TNumDimensions> m_extents;
		std::vector<TType> m_value;

		static int generate_linear_index(std::array<int, TNumDimensions> extent,
			std::array<int, TNumDimensions> index);

		static std::array<int, TNumDimensions> generate_coordinate_index(
			std::array<int, TNumDimensions> extent, int linear_index
		);
		
		static int number_of_elements(std::array<int, TNumDimensions> extent);

		void assert_valid_extents();
		void assert_valid_indices(std::array<int, TNumDimensions> indexes);
		static void assert_valid_extents(std::array<int, TNumDimensions> extents);
		static void assert_valid_indices(std::array<int, TNumDimensions> extent,
			std::array<int, TNumDimensions> index);
	};




	// DEFINITIONS

	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockND<TNumDimensions, TType>::StructuredValueBlockND()
		: m_extents()
	{
		for (int &extent : m_extents) { extent = 0; }
		return;
	}


	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockND<TNumDimensions, TType>::~StructuredValueBlockND()
	{
		// INTENTIONALLY BLANK
	}

	template<int TNumDimensions, typename TType>
	inline void StructuredValueBlockND<TNumDimensions, TType>::extent(std::array<int, TNumDimensions> extents)
	{
		assert_valid_extents(extents);
		m_extents = extents;
		m_value.resize(number_of_elements(extents));
		return;
	}

	template<int TNumDimensions, typename TType>
	inline std::array<int, TNumDimensions> StructuredValueBlockND<TNumDimensions, TType>::extent()
	{
		return m_extents;
	}

	template<int TNumDimensions, typename TType>
	inline TType & StructuredValueBlockND<TNumDimensions, TType>::value(std::array<int, TNumDimensions> coordinate)
	{
		assert_valid_extents();
		assert_valid_indices(coordinate);
		int linear_index = generate_linear_index(m_extents, coordinate);
		return m_value[linear_index];
	}

	template<int TNumDimensions, typename TType>
	inline void StructuredValueBlockND<TNumDimensions, TType>::swap(int first_dim, int second_dim)
	{
		assert(first_dim < TNumDimensions);
		assert(second_dim < TNumDimensions);
		assert(first_dim >= 0);
		assert(second_dim >= 0);

		if (first_dim == second_dim) { return; }
		else {
			std::vector<TType> new_values;
			new_values.resize(number_of_elements(m_extents));
			std::array<int, TNumDimensions> coordinate;
			std::array<int, TNumDimensions> new_extent;
			new_extent = m_extents;
			std::swap(new_extent[first_dim], new_extent[second_dim]);

			int size = number_of_elements(m_extents);
			for (int i = 0; i < size; i++) {
				coordinate = generate_coordinate_index(m_extents, i);
				std::swap(coordinate[first_dim], coordinate[second_dim]);
				int new_linear_index = generate_linear_index(new_extent, coordinate);
				// We would't want to ruin any right hand rule observing data.
				coordinate[second_dim] = m_extents[second_dim] - coordinate[second_dim] - 1;
				new_values[new_linear_index] = m_value[i];
			}
			m_value = new_values;
			m_extents = new_extent;
			return;
		}

	}


	template<int TNumDimensions, typename TType>
	inline int StructuredValueBlockND<TNumDimensions, TType>::generate_linear_index(std::array<int, TNumDimensions> extent,
		std::array<int, TNumDimensions> index)
	{
		assert_valid_extents(extent);
		HBTK::StructuredBlockIndexerND<TNumDimensions> indexer(extent);
		return indexer.coordinate_index(index);
	}

	template<int TNumDimensions, typename TType>
	inline std::array<int, TNumDimensions> StructuredValueBlockND<TNumDimensions, TType>::generate_coordinate_index(
		std::array<int, TNumDimensions> extent, int linear_index)
	{
		assert_valid_extents(extent);
		
		HBTK::StructuredBlockIndexerND<TNumDimensions> indexer(extent);
		return indexer.linear_index(linear_index);
	}

	template<int TNumDimensions, typename TType>
	inline int StructuredValueBlockND<TNumDimensions, TType>::number_of_elements(std::array<int, TNumDimensions> extent)
	{
		assert_valid_extents(extent);
		int size(1);
		for (int ext : extent) { size *= ext; }
		return size;
	}


	template<int TNumDimensions, typename TType >
	inline void StructuredValueBlockND<TNumDimensions, TType>::assert_valid_extents()
	{
		assert_valid_extents(m_extents);
	}

	template<int TNumDimensions, typename TType>
	inline void StructuredValueBlockND<TNumDimensions, TType>::assert_valid_indices(std::array<int, TNumDimensions> indexes)
	{
		assert_valid_indices(m_extents, indexes);
		return;
	}


	template<int TNumDimensions, typename TType>
	inline void StructuredValueBlockND<TNumDimensions, TType>::assert_valid_extents(std::array<int, TNumDimensions> extents)
	{
		for (auto &extent : extents) {
			assert(extent > 0);
		}
		return;
	}


	template<int TNumDimensions, typename TType>
	inline void StructuredValueBlockND<TNumDimensions, TType>::assert_valid_indices(std::array<int, TNumDimensions> extent,
		std::array<int, TNumDimensions> index)
	{
		for (int i = 0; i < TNumDimensions; i++) {
			assert(index[i] >= 0);
			assert(index[i] < extent[i]);
		}
		return;
	}
}


