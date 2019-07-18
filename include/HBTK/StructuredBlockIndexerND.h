#pragma once
/*////////////////////////////////////////////////////////////////////////////
StructuredBlockIndexerND.h

Generated indexes for multiple dimensionsal structured block.

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

#include <algorithm>
#include <array>
#include <cassert>

namespace HBTK {

	template<int TNumDimensions>
	class StructuredBlockIndexerND 
	{
	public:
		StructuredBlockIndexerND(std::array<int, TNumDimensions> extent);
		StructuredBlockIndexerND(std::array<int, TNumDimensions> extent,
			std::array<int, TNumDimensions> indexing_order);
		~StructuredBlockIndexerND();

		// Directly access an index.
		std::array<int, TNumDimensions> linear_index(int idx);
		int coordinate_index(std::array<int, TNumDimensions> coordinate);
		int size();

		// Dereference iterator.
		std::array<int, TNumDimensions> operator()();
		std::array<int, TNumDimensions> extents();

		constexpr StructuredBlockIndexerND<TNumDimensions> begin();
		StructuredBlockIndexerND<TNumDimensions> end();
		StructuredBlockIndexerND<TNumDimensions>& operator++();
		StructuredBlockIndexerND<TNumDimensions>& operator--();

		constexpr bool operator==(const StructuredBlockIndexerND<TNumDimensions> &);
		constexpr bool operator!=(const StructuredBlockIndexerND<TNumDimensions> &);
		constexpr bool operator>(const StructuredBlockIndexerND<TNumDimensions> &);
		constexpr bool operator<(const StructuredBlockIndexerND<TNumDimensions> &);
		constexpr bool operator>=(const StructuredBlockIndexerND<TNumDimensions> &);
		constexpr bool operator<=(const StructuredBlockIndexerND<TNumDimensions> &);

	private:
		// The extents of the block that this iterator is for.
		std::array<int, TNumDimensions> m_extents;

		// The current index.
		std::array<int, TNumDimensions> m_index;

		// The indexing order
		std::array<int, TNumDimensions> m_indexing_order;
	};


	// DEFINITIONS

	template<int TNumDimensions>
	inline StructuredBlockIndexerND<TNumDimensions>::StructuredBlockIndexerND(
		std::array<int, TNumDimensions> extent )
		: m_extents(extent),
		m_index(),
		m_indexing_order()
	{
		for (int &i : m_index) i = 0;
		for (int &i : m_extents) assert(i >= 0);
		for (int i = 0; i < (int)m_indexing_order.size(); i++) { m_indexing_order[i] = i; }
	}

	template<int TNumDimensions>
	inline StructuredBlockIndexerND<TNumDimensions>::StructuredBlockIndexerND(
		std::array<int, TNumDimensions> extent, std::array<int, TNumDimensions> indexing_order)
		: m_extents(extent),
		m_index()
	{
		for (int &i : m_index) i = 0;
		for (int &i : m_extents) assert(i >= 0);
		m_indexing_order = indexing_order;
		for (int &i : indexing_order) assert(i >= 0);
		// Check no repeated indexes.
		std::sort(indexing_order.begin(), indexing_order.end());
		auto non_unique = std::unique(indexing_order.begin(), indexing_order.end());
		assert(non_unique == indexing_order.end());
		return;
	}

	template<int TNumDimensions>
	inline StructuredBlockIndexerND<TNumDimensions>::~StructuredBlockIndexerND()
	{
		// Intentionally black.
	}

	template<int TNumDimensions>
	inline std::array<int, TNumDimensions> StructuredBlockIndexerND<TNumDimensions>::linear_index(int idx)
	{
		assert(idx >= 0);
		assert(idx < size());
		
		std::array<int, TNumDimensions> coordinate;
		int mutable_idx = idx;
		for (int i : m_indexing_order) {
			coordinate[i] = mutable_idx % m_extents[i];
			mutable_idx -= coordinate[i];
			mutable_idx /= m_extents[i];
		}
		
		return coordinate;
	}

	template<int TNumDimensions>
	inline int StructuredBlockIndexerND<TNumDimensions>::coordinate_index(std::array<int, TNumDimensions> coordinate)
	{
		for (int i = 0; i < (int)coordinate.size(); i++) {
			assert(coordinate[i] >= 0);
			assert(coordinate[i] < m_extents[i]);
		}
		int index = 0;
		int stride = 1;
		for (int i : m_indexing_order) {
			index += coordinate[i] * stride;
			stride *= m_extents[i];
		}
		return index;
	}

	template<int TNumDimensions>
	inline int StructuredBlockIndexerND<TNumDimensions>::size()
	{
		int size = 1;
		for (int &i : m_extents) { size *= i; }
		return size;
	}

	template<int TNumDimensions>
	inline std::array<int, TNumDimensions> StructuredBlockIndexerND<TNumDimensions>::operator()()
	{
		return m_index;
	}

	template<int TNumDimensions>
	inline std::array<int, TNumDimensions> StructuredBlockIndexerND<TNumDimensions>::extents()
	{
		return m_extents;
	}

	template<int TNumDimensions>
	inline constexpr StructuredBlockIndexerND<TNumDimensions> StructuredBlockIndexerND<TNumDimensions>::begin()
	{
		std::array<int, TNumDimensions> a;
		for (int &i : a) { i = 0; }
		return StructuredBlockIndexerND<TNumDimensions>(a);
	}

	template<int TNumDimensions>
	inline StructuredBlockIndexerND<TNumDimensions> StructuredBlockIndexerND<TNumDimensions>::end()
	{
		StructuredBlockIndexerND<TNumDimensions> returnable(m_extents, m_indexing_order);
		returnable.m_index = m_index;
		return returnable;
	}

	template<int TNumDimensions>
	inline StructuredBlockIndexerND<TNumDimensions>& StructuredBlockIndexerND<TNumDimensions>::operator++()
	{
		for (int &i : m_indexing_order) {
			m_index[i]++;
			if (m_index[i] < m_extents[i]) break;
			m_index[i] = 0;
		}
		return *(this);
	}

	template<int TNumDimensions>
	inline StructuredBlockIndexerND<TNumDimensions>& StructuredBlockIndexerND<TNumDimensions>::operator--()
	{
		for (int &i : m_indexing_order) {
			m_index[i]--;
			if (m_index[i] > 0) break;
			m_index[i] = 0;
		}
		return *this;
	}

	template<int TNumDimensions>
	inline constexpr bool StructuredBlockIndexerND<TNumDimensions>::operator==(const StructuredBlockIndexerND<TNumDimensions>& other)
	{
		assert(this->m_extents == other.m_extents);
		return m_index == other.m_index;
	}

	template<int TNumDimensions>
	inline constexpr bool StructuredBlockIndexerND<TNumDimensions>::operator!=(const StructuredBlockIndexerND<TNumDimensions>& other)
	{
		return !(*this == other);
	}

	template<int TNumDimensions>
	inline constexpr bool StructuredBlockIndexerND<TNumDimensions>::operator>(const StructuredBlockIndexerND<TNumDimensions>& other)
	{
		assert(extents() == other.extents());
		int pos_this, pos_other;
		pos_this = coordinate_index(m_index);
		pos_other = other.coordinate_index(other());
		return pos_this > pos_other;
	}

	template<int TNumDimensions>
	inline constexpr bool StructuredBlockIndexerND<TNumDimensions>::operator<(const StructuredBlockIndexerND<TNumDimensions>& other)
	{
		assert(extents() == other.extents());
		int pos_this, pos_other;
		pos_this = coordinate_index(m_index);
		pos_other = other.coordinate_index(other());
		return pos_this < pos_other;
	}

	template<int TNumDimensions>
	inline constexpr bool StructuredBlockIndexerND<TNumDimensions>::operator>=(const StructuredBlockIndexerND<TNumDimensions>& other)
	{
		return !(this->operator<(other));
	}

	template<int TNumDimensions>
	inline constexpr bool StructuredBlockIndexerND<TNumDimensions>::operator<=(const StructuredBlockIndexerND<TNumDimensions>& other)
	{
		return !(this->operator>(other));
	}


} // End namespace HBTK

