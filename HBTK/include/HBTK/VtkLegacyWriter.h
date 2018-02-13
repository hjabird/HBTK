#pragma once
/*////////////////////////////////////////////////////////////////////////////
VtkLegacyWriter.h

Write Vtk Legacy (non-Xml) files.

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

#include <memory>
#include <ostream>

#include "StructuredMeshBlock3D.h"
#include "StructuredValueBlockND.h"

namespace HBTK {
	namespace Vtk {
		class VtkWriter {
		public:
			VtkWriter();
			~VtkWriter();

			// bool write_binary;
			std::string file_description;

			void open_file(std::unique_ptr<std::ostream> ostream);
			std::unique_ptr<std::ostream> close_file();

			// Structured mesh:
			void write_mesh(StructuredMeshBlock3D & mesh);
			void append_structured_scalar_data(StructuredValueBlockND<3, double> & meshdata, std::string name);

		private:
			bool m_writing_binary;
			bool m_mesh_written;

			std::unique_ptr<std::ostream> m_ostream;



		};
	}
}