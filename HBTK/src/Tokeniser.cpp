#include "Tokeniser.h"
/*////////////////////////////////////////////////////////////////////////////
Tokeniser.cpp

A simple lexer.

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

#include <cctype>
#include <stdexcept>

HBTK::Tokeniser::Tokeniser(std::istream * stream)
	: m_stream(*stream),
	multiline_strings(true),
	m_char_number(0),
	m_line_number(1)
{
}

const HBTK::Token & HBTK::Tokeniser::current() const
{
	return m_working_token;
}

const HBTK::Token & HBTK::Tokeniser::next()
{
	char c = m_stream.get();
	m_char_number += 1;
	m_working_token.m_value = c;
	m_working_token.m_line = m_line_number;
	m_working_token.m_char = m_char_number;
	// Whitespace
	if (std::isspace(c)) {
		m_working_token.m_token_type = Token::type::WHITE_SPACE;
		if (c == '\n') {
			m_line_number++;
			m_char_number = 0;
		}
		return m_working_token;
	}
	// Punctuation except _, " and '
	else if (std::ispunct(c) && (c != '_') && (c != '\'') && (c != '\"')) {
		m_working_token.m_token_type = Token::type::PUNCTUATION;
		return m_working_token;
	} 
	else if (std::isdigit(c)) {
		m_working_token.m_token_type = Token::type::NUMBER;
		bool point = false;
		while(true) {
			c = m_stream.get();
			m_char_number += 1;
			if (std::isdigit(c)) {
				m_working_token.m_value += c;
			}
			else {
				if (c == '.') {
					if (point) {
						m_stream.unget();
						m_char_number -= 1;
						break;
					}
					else {
						point = true;
						m_working_token.m_value += c;
					}
				}
				else {
					m_stream.unget();
					m_char_number -= 1;
					break;
				}
			}
		};
	}
	// Strings - anything starting with " or '
	else if (c == '\"' || c == '\'') {
		m_working_token.m_value = "";
		m_working_token.m_token_type = Token::type::STRING;
		bool sq = c == '\''; // Is the string started with single quote or double quote?
		c = m_stream.get();
		m_char_number += 1;
		while (sq ? c != '\'' : c != '\"') {
			if (c == '\n') {
				if (!multiline_strings) {
					throw std::invalid_argument(
						"String on line " + std::to_string(m_line_number) +
						" does not finish by end of line."
					);
				}
				m_line_number++;
				m_char_number = 0;
			}
			m_working_token.m_value += c;
			if (m_stream.eof()) {
				throw std::invalid_argument(
					"String starting on line " + std::to_string(m_line_number) +
					" terminated by end of file."
				);
				break;
			}
			else {
				c = m_stream.get();
				m_char_number += 1;
			}
		}
	}
	// Any remaining thing is taken as a variable name. Includes underscore in names.
	else if (std::isprint(c)) {
		m_working_token.m_token_type = Token::type::VARIABLE;
		c = m_stream.get();
		m_char_number += 1;
		while (std::isalnum(c) || c == '_') {
			m_working_token.m_value += c;
			if (eof()) break;
			c = m_stream.get();
			m_char_number += 1;
		}
		m_stream.unget();
		m_char_number -= 1;
	}
	// Anything else (non-printable and not whitespace (think control codes)) is discarded.
	return m_working_token;
}

bool HBTK::Tokeniser::eof() const
{
	if (m_stream.get() == -1) {
		return true;
	}
	else {
		m_stream.unget();
		return m_stream.eof();
	}
}

int HBTK::Tokeniser::line_number() const
{
	return m_line_number;
}

int HBTK::Tokeniser::char_number() const
{
	return m_char_number;
}
