#include "TokenModifiers.h"
/*////////////////////////////////////////////////////////////////////////////
TokenModifiers.cpp

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

#include <numeric>
#include <cassert>
#include <cctype>

HBTK::NumberTokenModifier::NumberTokenModifier(std::shared_ptr<TokenStream> stream)
	: m_stream(stream),
	m_tokens(), 
	m_last_update_pos(0)
{
}

const HBTK::Token & HBTK::NumberTokenModifier::current()
{
	return peek(0);
}

const HBTK::Token & HBTK::NumberTokenModifier::next()
{
	if (m_last_update_pos != m_stream->position()) {
		m_tokens.clear();
	}
	if ((int)m_tokens.size() > 0) {
		m_tokens.pop_front();
	}
	return peek(0);
}

const HBTK::Token & HBTK::NumberTokenModifier::peek(int ahead)
{
	assert(ahead >= 0);
	while ((int)m_tokens.size() < ahead + 1) {
		load_next_token();
	}
	return m_tokens[ahead];
}

bool HBTK::NumberTokenModifier::eof() const
{
	return m_stream->eof();
}

int HBTK::NumberTokenModifier::line_number()
{
	return peek(0).line();
}

int HBTK::NumberTokenModifier::char_number()
{
	return peek(0).char_idx();
}

// Recognise 0., 0.0, .0, 1.2e4, 1.3E4, 3.e8, 9.E9
void HBTK::NumberTokenModifier::load_next_token()
{
	bool num_started = false;
	int peek_offset = std::accumulate(m_token_sizes.begin(), 
		m_token_sizes.end(), 0);
	Token working_token;
	working_token = m_stream->peek(peek_offset);
	// Situations that might be a floating point number: 
	if (working_token.isinteger()) {
		if (m_stream->peek(peek_offset + 1).value() == ".") {
			working_token.m_value += ".";
			peek_offset++;
			num_started = true;
		}
		else {
			assert(!m_stream->peek(peek_offset + 1).isinteger());
		}
	}
	else if (working_token.value() == ".") {
		Token nxt = m_stream->peek(peek_offset + 1); // Effectively &&...
		if (nxt.isinteger()) {
			num_started = true;
		}
	}
	// We think we have a floating point number.
	// peek_offset is looking at our point.
	if (num_started) {
		peek_offset++;
		working_token.m_token_type = Token::FLOAT;
		Token nxt = peek(peek_offset);
		if (nxt.isinteger()) {
			working_token.m_value += nxt.value();
			peek_offset++;
		}
		// Now if there is the E2, or whatever.
		nxt = m_stream->peek(peek_offset);
		if (nxt.value() == "E" || nxt.value() == "e") {
			Token nxtnxt = m_stream->peek(peek_offset + 1);
			if (nxtnxt.isinteger()) {
				working_token.m_value += nxt.value();
				working_token.m_value += nxtnxt.value();
			}
		}
	}
	m_tokens.push_back(working_token);
}
