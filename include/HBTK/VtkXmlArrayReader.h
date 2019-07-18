#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkXmlArrayReader.h

Read arrays from VTK Xml files.

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

#include <string>
#include <unordered_map>
#include <vector>

#include "CartesianVector.h"
#include "XmlParser.h"

namespace HBTK {
	namespace Vtk {
		class VtkXmlArrayReader {
		public:
			enum dtype {
				SCALAR, INTEGER, VECTOR
			};


			// When a new data array is encountered, refer the input steam to function.
			// A integer is later used to match up read in arrays to location in file is returned.
			int new_array_tag(
				int expected_length, 
				Xml::XmlParser::key_val_pairs,
				Xml::XmlParser & parser);

			// For when the appended data tag is encountered.
			// Reads in appended data.
			// void parse_appended_data(std::string appended_data_tag, std::istream & stream, Xml::XmlParser & parser);

			// Get the type - ie. scalar, integer or vector - associated with an array integer tag.
			dtype retrieve_data_type(int array_tag);

			// For an integer tag, the data of an array is transfered to a target array, and the name
			// to a target string. If the tag refers to a different type of data (eg. scalar not vector)
			// it'll throw an argument exception.
			void retrieve_scalar_data(int tag, std::string & name_target, std::vector<double> & data_target);
			void retrieve_int_data(int tag, std::string & name_target, std::vector<int> & data_target);
			void retrieve_vector_data(int tag, std::string & name_target, std::vector<HBTK::CartesianVector3D> & data_target);

		protected:

			enum stype {
				INT8, INT16, INT32, INT64,
				UINT8, UINT16, UINT32, UINT64,
				FLOAT32, FLOAT64
			};

			// The data for once it has been read in:
			std::vector<std::string> m_data_names;
			std::unordered_map<int, std::vector<double>> m_scalar_data;
			std::unordered_map<int, std::vector<int>> m_int_data;
			std::unordered_map<int, std::vector<HBTK::CartesianVector3D>> m_vector_data;

			// Essential info for reading later:
			std::vector<dtype> m_data_types;
			std::vector<stype> m_storage_types;
			std::vector<int> m_num_values;
			std::unordered_map<int, int> m_offsets;

			// Convert at type description - eg. "Int32" - to the enum. 
			stype type_string_to_stype(std::string desc);

			// Read in an ASCII array
			void read_ascii_data(int id, Xml::XmlParser& xml_parser);
		};
	}
}