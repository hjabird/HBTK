#pragma once
/*////////////////////////////////////////////////////////////////////////////
StructuredValueBlockND.h

An iterator for StructuredValueBlockND. Not for direct use.

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

#include <iterator>

namespace HBTK {
	template<int TNumDimensions, typename TType>
	class StructuredValueBlockND;

	template<
		int TNumDimensions,
		typename TType
	>
	class StructuredValueBlockNDIterator {
	public:
		using iterator = StructuredValueBlockNDIterator<TNumDimensions, TType>;
		using iterator_catagory = std::bidirectional_iterator_tag;
		using pointer = TType * ;
		using reference = TType&;
		using value_type = TType;

		StructuredValueBlockNDIterator<TNumDimensions, TType>() = default;
		explicit StructuredValueBlockNDIterator<TNumDimensions, TType>(TType* array_value);
		~StructuredValueBlockNDIterator<TNumDimensions, TType>() = default;

		reference operator*() const;
		reference operator->() const;

		StructuredValueBlockNDIterator<TNumDimensions, TType>& operator++();
		StructuredValueBlockNDIterator<TNumDimensions, TType> operator++(int);

		StructuredValueBlockNDIterator<TNumDimensions, TType>& operator--();
		StructuredValueBlockNDIterator<TNumDimensions, TType> operator--(int);

		bool operator==(const iterator & other) const;
		bool operator!=(const iterator & other) const;
	private:
		pointer current;
	};

	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockNDIterator<TNumDimensions, TType>::StructuredValueBlockNDIterator(TType * array_value)
		: current(array_value)
	{
	}

	template<int TNumDimensions, typename TType>
	inline TType& StructuredValueBlockNDIterator<TNumDimensions, TType>::operator*() const
	{
		return *current;
	}

	template<int TNumDimensions, typename TType>
	inline TType& StructuredValueBlockNDIterator<TNumDimensions, TType>::operator->() const
	{
		return *current;
	}

	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockNDIterator<TNumDimensions, TType>& StructuredValueBlockNDIterator<TNumDimensions, TType>::operator++()
	{
		current += 1;
		return *this;
	}

	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockNDIterator<TNumDimensions, TType> StructuredValueBlockNDIterator<TNumDimensions, TType>::operator++(int)
	{
		++current;
		return *this;
	}

	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockNDIterator<TNumDimensions, TType>& StructuredValueBlockNDIterator<TNumDimensions, TType>::operator--()
	{
		++current;
		return *this;
	}

	template<int TNumDimensions, typename TType>
	inline StructuredValueBlockNDIterator<TNumDimensions, TType> StructuredValueBlockNDIterator<TNumDimensions, TType>::operator--(int)
	{
		--current;
		return *this;
	}

	template<int TNumDimensions, typename TType>
	inline bool StructuredValueBlockNDIterator<TNumDimensions, TType>::operator==(const iterator & other) const
	{
		return current == other.current;
	}

	template<int TNumDimensions, typename TType>
	inline bool StructuredValueBlockNDIterator<TNumDimensions, TType>::operator!=(const iterator & other) const
	{
		return ! operator==(other);
	}
}