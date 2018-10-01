#pragma once
/*////////////////////////////////////////////////////////////////////////////
TokenModifiers.h

Modify a token stream in some way.

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

#include <memory>
#include <deque>

#include "TokenStream.h"

namespace HBTK {
	// Identifies tokes that make a number and group into single token.
	class NumberTokenModifier: TokenStream
	{
	public:
		NumberTokenModifier(std::shared_ptr<TokenStream>);
		virtual const Token& current() override;
		virtual const Token& next() override;
		virtual const Token& peek(int) override;
		virtual bool eof() const override;
		virtual int line_number() override;
		virtual int char_number() override;
	protected:
		std::deque<Token> m_tokens;
		std::deque<int> m_token_sizes;
		std::shared_ptr<TokenStream> m_stream;
		int m_last_update_pos;
		void load_next_token();
	};
}
