#include "stdafx.h"
#include "VtkLegacyWriter.h"
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

#include "StructuredBlockIndexerND.h"

HBTK::Vtk::VtkLegacyWriter::VtkLegacyWriter()
	: file_description("A_VTK_FILE: Set HBTK::Vtk::VtkLegacyWriter.file_description for custom description.")
{
}

HBTK::Vtk::VtkLegacyWriter::~VtkLegacyWriter()
{
}

void HBTK::Vtk::VtkLegacyWriter::open_file(std::ostream * ostream)
{
	*ostream << "# vtk DataFile Version 2.0\n";
	*ostream << file_description.c_str() << "\n";
	bool write_binary = false;
	*ostream << (write_binary ? "BINARY\n" : "ASCII\n");
	m_writing_binary = write_binary;
	m_ostream = ostream;
	return;
}

void HBTK::Vtk::VtkLegacyWriter::write_mesh(StructuredMeshBlock3D & mesh)
{
	if (m_mesh_written) { throw - 1; }
	*m_ostream << "DATASET STRUCTURED_GRID\n";
	std::array<int, 3> extent = mesh.extent();
	*m_ostream << "DIMENSIONS " << extent[0] << " " << extent[1] << " " << extent[2] << "\n";
	*m_ostream << "POINTS " << extent[0] * extent[1] * extent[2] << " float\n";

	StructuredBlockIndexerND<3> index(extent);
	int size = index.size();
	for (int i = 0; i < size; i++) {
		std::array<double, 3> coord = mesh.coord(index.linear_index(i));
		*m_ostream << coord[0] << " " << coord[1] << " " << coord[2] << "\n";
	}
	return;
}

void HBTK::Vtk::VtkLegacyWriter::append_structured_scalar_data(StructuredValueBlockND<3, double>& meshdata, std::string name)
{
	*m_ostream << "SCALARS " << name.c_str() << " float\n";
	*m_ostream << "LOOKUP_TABLE default\n";
	
	StructuredBlockIndexerND<3> index(meshdata.extent());	
	int size = index.size();
	for (int i = 0; i < size; i++) {
		*m_ostream << meshdata.value(index.linear_index(i)) << "\n";
	}
	return;
}

