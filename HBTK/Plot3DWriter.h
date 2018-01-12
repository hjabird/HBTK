#pragma once
/*////////////////////////////////////////////////////////////////////////////
Plot3DWriter.h

Write a Plot3D file.

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
			bool no_block_count;
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

