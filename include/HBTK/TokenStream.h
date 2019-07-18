#pragma once
/*////////////////////////////////////////////////////////////////////////////
TokenStream.h

An pure abstract interface for objects modifying a stream of tokens.

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

#include "Token.h"

namespace HBTK {
	class TokenStream {
	public:
		virtual ~TokenStream() = default;

		// Access the current token
		virtual const Token& current() = 0;

		// Load the next token
		virtual const Token& next() = 0;

		// Returns true if end of stream
		virtual bool eof() const = 0;

		// Line number of current token
		virtual int line_number() = 0;

		// Char number of current token
		virtual int char_number() = 0;

		// Peek at forthcoming tokens without consuming them
		// peek(0) is equivalent to current.
		virtual const Token& peek(int) = 0;

		// Returns position of current token in stream.
		// Used to verify if parent streams have been read
		// from elsewhere and therefore caches invalidated.
		virtual int position() = 0;
	};
}
