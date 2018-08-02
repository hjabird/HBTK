#include <HBTK/Token.h>
#include <HBTK/Tokeniser.h>
#include <catch2/catch.hpp>
/*////////////////////////////////////////////////////////////////////////////
TestTokeniser.cpp

Test Tokeniser and Tokens.

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

#include <sstream>
#include <vector>

TEST_CASE("Tokeniser & Tokens") {
	SECTION("All whitespace & token count") {
		std::istringstream str(" \t\n");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 3);
		for (auto & i : tokens) {
			REQUIRE(i.isspace());
		}
		REQUIRE(tokens[0].value() == " ");
		REQUIRE(tokens[1].value() == "\t");
		REQUIRE(tokens[2].value() == "\n");
	}

	SECTION("Read a string - double quoted") {
		std::istringstream str("\"Hello world\"");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 1);
		REQUIRE(tokens[0].isstr());
		REQUIRE(tokens[0].value() == "Hello world");
	}

	SECTION("Read a string - single quoted") {
		std::istringstream str("\'Hello world\'");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 1);
		REQUIRE(tokens[0].isstr());
		REQUIRE(tokens[0].value() == "Hello world");
	}

	SECTION("Read a string - single quotes in double quotes") {
		std::istringstream str("\"Hello\' world\"");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 1);
		REQUIRE(tokens[0].isstr());
		REQUIRE(tokens[0].value() == "Hello\' world");
	}

	SECTION("Identify a number") {
		std::istringstream str("1.35");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 1);
		REQUIRE(tokens[0].isnum());
		REQUIRE(tokens[0].value() == "1.35");
	}

	SECTION("Identify a variable name") {
		std::istringstream str("foo");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 1);
		REQUIRE(tokens[0].isvar());
		REQUIRE(tokens[0].value() == "foo");
	}

	SECTION("Identify variables mixed with punctuation") {
		std::istringstream str("foo+bar=foobar");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 5);
		REQUIRE(tokens[0].isvar());
		REQUIRE(tokens[0].value() == "foo");
		REQUIRE(tokens[2].isvar());
		REQUIRE(tokens[2].value() == "bar");
		REQUIRE(tokens[4].isvar());
		REQUIRE(tokens[4].value() == "foobar");
		REQUIRE(tokens[1].ispunct());
		REQUIRE(tokens[1].value() == "+");
		REQUIRE(tokens[3].ispunct());
		REQUIRE(tokens[3].value() == "=");
	}


	SECTION("Correct line numbering") {
		std::istringstream str("a\nb\nc\n");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens[0].line() == 1);
		REQUIRE(tokens[2].line() == 2);
		REQUIRE(tokens[4].line() == 3);
	}


	SECTION("String ends in file") {
		std::istringstream str("a\nb\n\"\nabcd\'\n\n");
		std::vector<HBTK::Token> tokens;
		HBTK::Tokeniser tokeniser(&str);
		bool caught = false;
		try {
			while (!tokeniser.eof()) {
				tokens.push_back(tokeniser.next());
			}
		}
		catch (...) {
			caught = true;
		}
		REQUIRE(caught == true);
		REQUIRE(tokeniser.line_number() == 6);
	}
}