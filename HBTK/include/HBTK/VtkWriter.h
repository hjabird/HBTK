#pragma once

#include <ostream>

#include "VtkUnstructuredDataset.h"
#include "VtkUnstructuredMeshHolder.h"
#include "XmlWriter.h"

namespace HBTK {
	namespace Vtk {

		class VtkWriter {
		public:
			VtkWriter();

			void write(std::ostream & stream, const VtkUnstructuredDataset & data);


		protected:
			Xml::XmlWriter m_xml_writer;
			bool written_xml_header;

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

		};
	}
}

