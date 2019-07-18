#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkWriter.h

Write new, xml VTK data files. Does not have all the bells and whistles of
the complete file type, but who cares?

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

#include <ostream>
#include <string>
#include <vector>

#include "VtkUnstructuredDataset.h"
#include "VtkUnstructuredMeshHolder.h"
#include "XmlWriter.h"

namespace HBTK {
	namespace Vtk {

		class VtkWriter {
		public:
			VtkWriter();

			enum vtk_file_type {
				None,
				UnstructuredGrid
			};

			// Call before writing anything.
			void open_file(std::ostream & stream, vtk_file_type file_type);
			
			// Write out a single 'piece' of the dataset.
			void write_piece(std::ostream & stream, const VtkUnstructuredDataset & data);

			// Close the VTK file. Needed otherwise it'll be incomplete!
			void close_file(std::ostream & stream);

			// Set to true if you want human readable data.
			bool ascii;	// Write data as ascii. Default False

			// Set to true if you want the data to be appended at the end of the file
			// instead of where it is declared by the xml.
			bool appended; // Write data as appended. Default true

			// Write precision
			int write_precision;


		protected:
			// xml writer object
			Xml::XmlWriter m_xml_writer;

			// True once the <? ... ?> header has been written.
			bool m_written_xml_header;
			// True once some of the VTK file type etc has been written.
			vtk_file_type m_file_type;

			// The data which will be written in the appended section.
			std::vector<std::vector<unsigned char>> m_appended_data;

			void xml_header(std::ostream & ostream);
			void vtk_unstructured_file_header(std::ostream & ostream);
			void vtk_unstructed_grid_header(std::ostream & ostream);
			void vtk_unstructured_piece(std::ostream & ostream, int num_points, int num_cells);
			void vtk_unstructured_mesh(std::ostream & ostream, const VtkUnstructuredMeshHolder & mesh);
			void vtk_unstructured_cells(std::ostream & ostream, const VtkUnstructuredMeshHolder & mesh);
			void vtk_unstructured_point_data(std::ostream & ostream, const VtkUnstructuredDataset & data);
			void vtk_unstructured_cell_data(std::ostream & ostream, const VtkUnstructuredDataset & data);

			void vtk_data_array(std::ostream & ostream, std::string name, const std::vector<double> & scalars);
			void vtk_data_array(std::ostream & ostream, std::string name, const std::vector<int> & ints);
			void vtk_data_array(std::ostream & ostream, std::string name, const std::vector<HBTK::CartesianVector3D> & vectors);
			void vtk_data_array(std::ostream & ostream, std::string name, const std::vector<HBTK::CartesianPoint3D> & point);
			std::vector<unsigned char> vtk_data_array_generate_buffer(const std::vector<double> & scalars);
			std::vector<unsigned char> vtk_data_array_generate_buffer(const std::vector<int> & ints);
			std::vector<unsigned char> vtk_data_array_generate_buffer(const std::vector<HBTK::CartesianVector3D> & vectors);
			std::vector<unsigned char> vtk_data_array_generate_buffer(const std::vector<HBTK::CartesianPoint3D> & point);
			std::vector<std::pair<std::string, std::string>> vtk_data_array_format_options() const;

			int appended_data_bytelength() const;

		};
	}
}

