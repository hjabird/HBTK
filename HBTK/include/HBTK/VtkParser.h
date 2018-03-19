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

#include "BasicParser.h"
#include "XmlParser.h"

namespace HBTK {
	namespace Vtk {
		class VtkParser 
			: BasicParser<VtkParser>
		{
		public:
			VtkParser();
			~VtkParser();

			// Possible types of vkt file. Parallel unsupported.
			enum VtkFileType {
				UnknownFile,
				ImageDataFile,
				PolyDataFile,
				RectilinearGridFile,
				StructuredGridFile,
				UnstructuredGridFile
			};
			enum ByteOrder {
				LittleEndian,
				BigEndian
			};
		private:
			friend class BasicParser<VtkParser>;	

			// Possible vtk tags.
			enum vtk_tags {
				UnknownTag,
				CellDataTag,
				CoordinatesTag,
				DataArrayTag,
				ImageDataTag,
				PieceTag,
				PointDataTag,
				PointsTag,
				PolysTag,
				RectilinearGridTag,
				StripsTag,
				StructuredGridTag,
				UnstructuredGridTag,
				VertsTag,
				VTKFileTag
			};

			void main_parser(std::ifstream & input_stream, std::ostream & error_stream);

			// Meta info
			double m_version;
			VtkFileType m_file_type;
			ByteOrder m_byte_order;

			// For handling all the xml:
			Xml::XmlParser m_xml_parser;

			typedef std::vector<std::pair<std::string, std::string>> key_val_pairs;
			// Functions for the all your xml needs:
			void on_tag_open(std::string tag_name,  key_val_pairs key_vals);
			void on_tag_close(std::string tag_name);
			vtk_tags string_to_tag(std::string tag_str);
			
			void on_cell_data_tag(key_val_pairs key_vals);
			void on_piece_tag(key_val_pairs key_vals);
			void on_point_data_tag(key_val_pairs key_vals);
			void on_points_tag(key_val_pairs key_vals);
			void on_structured_grid_tag(key_val_pairs key_vals);
			void on_unstructured_grid_tag(key_val_pairs key_vals);
			void on_vtkfile_tag(key_val_pairs key_vals);
			
			void set_vtk_file_type(std::string str);
			void set_vtk_file_version(std::string str);

			std::stack<vtk_tags> m_tag_stack;
		};
	}
}