#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkParser.h

Read Vtk files. Incomplete.

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

#include <stack>
#include <unordered_map>

#include "BasicParser.h"
#include "VtkXmlArrayReader.h"
#include "XmlParser.h"

namespace HBTK {
	namespace Vtk {
		class VtkParser 
			: BasicParser<VtkParser>
		{
		public:
			VtkParser();

			// Inherits from BasicParser:
			/*
			// Parse file at path.
			void parse(std::string file_path) {
				if (file_path.empty()) { throw - 1; }
				std::ifstream inpt_stream(file_path.c_str(), std::ios::binary);
				parse(inpt_stream, std::cerr);
			}

			// Parse Ifstream
			void parse(std::ifstream & input_stream) {
				parse(input_stream, std::cerr);
			}

			// Parse based on both input fstream and output stream
			void parse(std::ifstream & input_stream, std::ostream & error_stream) {
				if (!input_stream) { throw - 1; }
				if (!error_stream) { throw - 1; }
				static_cast<TParentClass *>(this)->main_parser(input_stream, error_stream);
			}
			*/

		protected:
			friend class BasicParser<VtkParser>;	
			using key_val_pairs = Xml::XmlParser::key_val_pairs;

			void main_parser(std::ifstream & input_stream, std::ostream & error_stream);

			std::istream *input_stream;

			// Meta info
			double m_version;

			// For handling all the xml:
			Xml::XmlParser m_xml_parser;

			// The set of functions to call for the subtags of the working tag
			typedef std::unordered_map<std::string, std::function<void(const key_val_pairs &, std::istream &)>>
				function_map;

			// And a stack of these bad boys.
			std::stack<function_map> m_fmap_stack;

			// To handle the reading of the array bits for us:
			VtkXmlArrayReader m_array_reader;

			// Functions for the all your xml needs:
			void on_tag_open(std::string tag_name,  key_val_pairs key_vals);
			void on_tag_close(std::string tag_name);

			void vtk_file_tag_handler(const key_val_pairs & params,
				std::istream & stream);
			void data_array_tag_handler(const key_val_pairs & params,
				std::istream & stream);
			void unstructured_cells_tag_handler(const key_val_pairs & params,
				std::istream & stream);
			void unstructured_points_tag_handler(const key_val_pairs & params,
				std::istream & stream);
			void unstructured_cell_data_tag_handler(const key_val_pairs & params,
				std::istream & stream);
			void unstructured_point_data_tag_handler(const key_val_pairs & params,
				std::istream & stream);
		};
	}
}