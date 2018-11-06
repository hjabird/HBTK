#include "BasicTokeniser.h"
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

#include <cassert>
#include <cctype>
#include <memory>
#include <stdexcept> 
#include <sstream>

HBTK::BasicTokeniser::BasicTokeniser(std::unique_ptr<std::istream> stream)
	: m_stream(std::move(stream)),
	m_stream_line_no(1),
	m_stream_char_no(0),
	m_position(0)
{
}

HBTK::BasicTokeniser::BasicTokeniser(const std::string& str)
	: m_stream(),
	m_stream_line_no(1),
	m_stream_char_no(0),
	m_position(0)
{
	std::unique_ptr<std::istringstream> strs =
		std::make_unique<std::istringstream>(std::istringstream(str));
	m_stream = std::move(strs);
}

const HBTK::Token & HBTK::BasicTokeniser::current()
{
	return peek(0);
}

const HBTK::Token & HBTK::BasicTokeniser::next()
{
	if ((int)m_tokens.size() > 0) {
		m_tokens.pop_front();
		++m_position;
	}
	return current();
}

const HBTK::Token& HBTK::BasicTokeniser::peek(int ahead) {
	assert(ahead >= 0);
	while ((int)m_tokens.size() > ahead + 1) {
		parse_another_token();
	}
	assert((int)m_tokens.size() >= ahead + 1);
	return m_tokens[ahead];
}

bool HBTK::BasicTokeniser::eof() const
{
	if (m_stream->get() == -1) {
		return true;
	}
	else {
		m_stream->unget();
		return m_stream->eof();
	}
}

int HBTK::BasicTokeniser::line_number()
{
	return peek(0).line();
}

int HBTK::BasicTokeniser::char_number()
{
	return peek(0).char_idx();
}

int HBTK::BasicTokeniser::position() {
	return m_position;
}

void HBTK::BasicTokeniser::parse_another_token() {
	Token working_token;

	char c = m_stream->get();
	m_stream_char_no += 1;
	working_token.m_value = c;
	working_token.m_line = m_stream_line_no;
	working_token.m_char = m_stream_char_no;
	// Whitespace
	if (std::isspace(c)) {
		working_token.m_token_type = Token::type::WHITE_SPACE;
		if (c == '\n') {
			m_stream_line_no++;
			m_stream_char_no = 0;
		}
	}
	// Punctuation except _, " and '
	else if (std::ispunct(c)) {
		working_token.m_token_type = Token::type::PUNCTUATION;
	}
	// If its a number
	else if (std::isdigit(c)) {
		working_token.m_token_type = Token::type::INTEGER;
		while (true) {
			c = m_stream->get();
			m_stream_char_no += 1;
			if (std::isdigit(c)) {
				working_token.m_value += c;
			}
			else {
				m_stream->unget();
				m_stream_char_no -= 1;
				break;
			}
		};
	}
	// Any remaining thing is taken as a variable name.
	else if (std::isprint(c)) {
		working_token.m_token_type = Token::type::WORD;
		c = m_stream->get();
		m_stream_char_no += 1;
		while (std::isalnum(c) || c == '_') {
			working_token.m_value += c;
			if (eof()) break;
			c = m_stream->get();
			m_stream_char_no += 1;
		}
		m_stream->unget();
		m_stream_char_no -= 1;
	}
	// Anything else (non-printable and not whitespace (think control codes)) is discarded.
	m_tokens.push_back(working_token);
	return;
}

