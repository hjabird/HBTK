#include <HBTK/Token.h>
#include <HBTK/BasicTokeniser.h>
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
		std::string str(" \t\n");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 3);
		for (auto & i : tokens) {
			REQUIRE(i.iswhitespace());
		}
		REQUIRE(tokens[0].value() == " ");
		REQUIRE(tokens[1].value() == "\t");
		REQUIRE(tokens[2].value() == "\n");
	}

	SECTION("Identify a number") {
		std::string str("1.35");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 3);
		REQUIRE(tokens[0].isnum());
		REQUIRE(tokens[0].value() == "1");
		REQUIRE(tokens[2].isnum());
		REQUIRE(tokens[2].value() == "35");
	}

	SECTION("Identify a word") {
		std::string str("foo");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 1);
		REQUIRE(tokens[0].value() == "foo");
	}

	SECTION("Identify brackets") {
		std::string str("{}()[]!.");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens[0].isbracket());
		REQUIRE(tokens[1].isbracket());
		REQUIRE(tokens[2].isbracket());
		REQUIRE(tokens[3].isbracket());
		REQUIRE(tokens[4].isbracket());
		REQUIRE(tokens[5].isbracket());
		REQUIRE(!tokens[6].isbracket());
		REQUIRE(!tokens[7].isbracket());
		REQUIRE(tokens[0].isopenbracket());
		REQUIRE(!tokens[1].isopenbracket());
		REQUIRE(tokens[2].isopenbracket());
		REQUIRE(!tokens[3].isopenbracket());
		REQUIRE(tokens[4].isopenbracket());
		REQUIRE(!tokens[5].isopenbracket());
		REQUIRE(!tokens[6].isopenbracket());
		REQUIRE(!tokens[7].isopenbracket());
		REQUIRE(!tokens[0].isclosebracket());
		REQUIRE(tokens[1].isclosebracket());
		REQUIRE(!tokens[2].isclosebracket());
		REQUIRE(tokens[3].isclosebracket());
		REQUIRE(!tokens[4].isclosebracket());
		REQUIRE(tokens[5].isclosebracket());
		REQUIRE(!tokens[6].isclosebracket());
		REQUIRE(!tokens[7].isclosebracket());
	}

	SECTION("Identify variables mixed with punctuation") {
		std::string str("foo+bar=foobar");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 5);
		REQUIRE(tokens[0].isword());
		REQUIRE(tokens[0].value() == "foo");
		REQUIRE(tokens[2].isword());
		REQUIRE(tokens[2].value() == "bar");
		REQUIRE(tokens[4].isword());
		REQUIRE(tokens[4].value() == "foobar");
		REQUIRE(tokens[1].ispunct());
		REQUIRE(tokens[1].value() == "+");
		REQUIRE(tokens[3].ispunct());
		REQUIRE(tokens[3].value() == "=");
	}


	SECTION("Correct line numbering") {
		std::string str("a\nb\nc\n");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens[0].line() == 1);
		REQUIRE(tokens[2].line() == 2);
		REQUIRE(tokens[4].line() == 3);
	}


	SECTION("char numbering without newline") {
		std::string str("foo+bar=foobar");
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens.size() == 5);
		REQUIRE(tokens[0].char_idx() == 1);
		REQUIRE(tokens[2].char_idx() == 5);
		REQUIRE(tokens[4].char_idx() == 9);
		REQUIRE(tokens[1].char_idx() == 4);
		REQUIRE(tokens[3].char_idx() == 8);
	}


	SECTION("char numbering with newline - no strings") {
		std::string str(
			"She is the fairies midwife, and she comes\n"
			"In shape no bigger than an agate stone\n"
			"On the forefinger of an alderman,\n"
			"Drawn with a team of little atomi\n"
			"Over mens noses as they lie asleep.\n"
		);
		std::vector<HBTK::Token> tokens;
		HBTK::BasicTokeniser tokeniser(str);
		while (!tokeniser.eof()) {
			tokens.push_back(tokeniser.next());
		}
		REQUIRE(tokens[0].value() == "She");
		REQUIRE(tokens[0].line() == 1);
		REQUIRE(tokens[0].char_idx() == 1);
		REQUIRE(tokens[37].value() == "forefinger");
		REQUIRE(tokens[37].line() == 3);
		REQUIRE(tokens[37].char_idx() == 8);
	}
}
