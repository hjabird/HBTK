#pragma once
/*////////////////////////////////////////////////////////////////////////////
BasicTokeniser.h

A simple lexer that separates out a text stream into Tokens. Separates tokens
by whitespace, punctuation and into groups of numbers (so +ve integers)
and groups of letters (words). These can be pieced back together according
to linguistic rules.

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

#include <deque>
#include <istream>

#include "Token.h"
#include "TokenStream.h"

namespace HBTK {
	class BasicTokeniser :
		TokenStream
	{
	public:
		BasicTokeniser(std::unique_ptr<std::istream>);
		BasicTokeniser(const std::string& str);

		virtual const Token& current() override;
		virtual const Token& next() override;
		virtual const Token& peek(int) override;

		virtual bool eof() const override;
		virtual int line_number() override;
		virtual int char_number() override;
		virtual int position() override;

	protected:
		// The collection of tokens used for lookahead purposes
		std::deque<Token> m_tokens;

		// Associated with the starting position of the current token.
		int m_stream_line_no;
		int m_stream_char_no;

		void parse_another_token();

		int m_position;

		std::unique_ptr<std::istream> m_stream;
	};
}