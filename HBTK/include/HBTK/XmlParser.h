#pragma once
/*////////////////////////////////////////////////////////////////////////////
XmlParser.h

Parse an XML file (SAX). What? Writing your own XML parser is silly? Pah.
This'll probably be deadly slow.

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

#include <functional>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

#include "BasicParser.h"


namespace HBTK {
	namespace Xml {
		class XmlParser
			: public HBTK::BasicParser<XmlParser>
		{
		public:
			XmlParser();
			~XmlParser();

			// Define a function to call when an element is opened.
			// The function should take two arguments:
			// A string defining the element's NAME ie: <NAME param1="1" ...>
			// A vector of parameters: pairs of param name and value
			// ie <NAME Pair1st="Pair2nd"
			std::function<void(std::string, std::vector<std::pair<std::string, std::string>>)> on_element_open;

			// A function to call when and element is closed.
			// Takes element name as argument:
			// from tag <\NAME>
			std::function<void(std::string)> on_element_close;

			// Get the input stream for reading the data associated with the element.
			std::istream& xml_input_stream();

		private:
			void main_parser(std::ifstream & input_stream, std::ostream & error_stream);

			// String encoding.
			enum encoding {
				ASCII,
				UTF8,
				UTF16
			};

			// FLAGS
			bool m_reading_file;
			encoding m_encoding;
			// The currently used input stream - invalid if a file isn't being read.
			std::ifstream *m_input_stream;
			// Stack of elements for checking nexting and open/close correctness.
			std::stack<std::string> m_element_stack;

			// Parse the xml file descriptor.
			void parse_prologue();
			// Parse element opening. Call user function.
			void parse_element_open();
			// Parse closing of the element. Check correctness. Call user function.
			void parse_element_close();
			// Parse instructions to the parser rather than data.
			void parse_parser_event();
			// Move to the curser to just inside the next xml tag.
			void seek_next_xml_event();
			// Returns the number of characters inside the tag. Curser stays in same position.
			int element_descriptor_length(); 
			// Runs the correct xml function when called with curser just inside xml tag.
			void act_on_xml_event();

			// Read the next character from the input stream. Normalised to char from different
			// encodings.
			char normalised_next_char();
		};
	} // End Xml
} // End HBTK
