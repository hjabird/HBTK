#pragma once
/*////////////////////////////////////////////////////////////////////////////
Plot3DParser.h

Parse a Plot3D file.

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

#include <array>
#include <functional>
#include <vector>

#include "BasicParser.h"
#include "StructuredMeshBlock2D.h"
#include "StructuredMeshBlock3D.h"

namespace HBTK {
	namespace Plot3D {
		class Plot3DParser:
			public HBTK::BasicParser<Plot3DParser>
		{
		public:
			Plot3DParser();
			~Plot3DParser();

			bool single_block;
			bool parse_as_binary;
			int number_of_dimensions;

			void add_2D_block_function(std::function<bool(HBTK::StructuredMeshBlock2D)> func);
			void add_3D_block_function(std::function<bool(HBTK::StructuredMeshBlock3D)> func);


		private:
			friend class HBTK::BasicParser<Plot3DParser>;

			// Main parsing function.
			void main_parser(std::ifstream & input_stream, std::ostream & error_stream);
			void parse_2d(std::ifstream & input_stream, std::ostream & error_stream);
			void parse_3d(std::ifstream & input_stream, std::ostream & error_stream);

			void parse_ascii(std::ifstream & input_stream, std::ostream & error_stream, int dimensions);
			void parse_binary(std::ifstream & input_stream, std::ostream & error_stream, int dimensions);

			// The functions to apply to the mesh blocks once they're parsed.
			std::vector<std::function<bool(HBTK::StructuredMeshBlock2D)>> m_mesh_2d_functions;
			std::vector<std::function<bool(HBTK::StructuredMeshBlock3D)>> m_mesh_3d_functions;

			// Applies a function to the input stream, such that the function recieves 
			// the correct i, j, k (assuming in reads the correct amount from the stream)
			void apply_function_to_input_array(int i_ext, int j_ext, int k_ext,
				std::function<void(int, int, int, std::ifstream&)>, std::ifstream&);
		};
	}
}

