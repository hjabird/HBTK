#pragma once

#include <fstream>

#include "StructuredMeshBlock2D.h"
#include "StructuredMeshBlock3D.h"

namespace HBTK {
	namespace Plot3D {
		class Plot3DWriter
		{
		public:
			Plot3DWriter();
			~Plot3DWriter();

			bool write_binary;
			bool three_dimensional;

			void add_mesh_block2d(HBTK::StructuredMeshBlock2D mesh);
			void add_mesh_block3d(HBTK::StructuredMeshBlock3D mesh);

			// Write out file to path:
			bool write(std::string path);
			bool write(std::ofstream & output_stream);

		private:
			void write_block_extent(int block, std::ofstream & output_stream);
			void write_nodes(int block, std::ofstream & output_stream);

			std::vector<HBTK::StructuredMeshBlock2D> m_meshes_2d;
			std::vector<HBTK::StructuredMeshBlock3D> m_meshes_3d;
		};
	}
}

