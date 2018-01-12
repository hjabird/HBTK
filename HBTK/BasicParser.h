#pragma once
/*////////////////////////////////////////////////////////////////////////////
BasicParser.cpp

A base class for parsers to inherit from.

Copyright 2017 HJA Bird

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
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

// This namespace is liable to be problematic.
#ifdef _MSC_VER
namespace fs = std::experimental::filesystem::v1;
#else
namespace fs = std::filesystem;
#endif


namespace HBTK {
	template <typename TParentClass>
	class BasicParser
	{
	public:
		// DECLARATIONS

		// Parse file at path.
		void parse(fs::path file_path) {
			if (file_path.empty()) { throw - 1; }
			std::ifstream inpt_stream(file_path, std::ios::binary);
			std::ofstream out_stream(stderr);
			parse(inpt_stream, out_stream);
		}

		// Parse Ifstream
		void parse(std::ifstream & input_stream) {
			std::ofstream err_stream(stderr);
			parse(input_stream, err_stream);
		}

		// Parse based on both input fstream and output fstream
		void parse(std::ifstream & input_stream, std::ofstream & error_stream) {
			if (!input_stream) { throw - 1; }
			if (!error_stream) { throw - 1; }
			static_cast<TParentClass *>(this)->main_parser(input_stream, error_stream);
		}


	protected:
		// Unpack chars to a Packed (!) structure
		template<typename Tstruct>
		inline void unpack_binary_to_struct(std::ifstream & input_stream, Tstruct & structure)
		{
			std::array<char, (int)sizeof(Tstruct)> buffer;
			if (!input_stream.read(buffer.data(), buffer.size())) {
				throw - 1;
			}
			structure = *reinterpret_cast<Tstruct *>(buffer.data());
			return;
		}

		// Separate a string into substrings by whitespace.
		std::vector<std::string> tokenise(const std::string & input_string)
		{
			std::vector<std::string> tokens;
			int token_end, idx, string_length, token_begin = -1;
			bool in_word = false;

			string_length = input_string.length();
			for (idx = 0; idx != string_length; idx++) {
				if (isspace(input_string[idx])) {
					if (in_word) {
						token_end = idx;
						tokens.emplace_back(input_string.substr(token_begin, token_end - token_begin));
						in_word = false;
					}
				}
				else if (!in_word) {
					token_begin = idx;
					in_word = true;
				}
			}
			if (in_word) {
				tokens.emplace_back(input_string.substr(token_begin, string_length));
			}
			return tokens;
		}

	};
}
	


