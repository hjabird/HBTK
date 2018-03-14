#pragma once
/*////////////////////////////////////////////////////////////////////////////
Paths.h

Very simple utilities for working with paths (for where we don't get 
C++17's filesystem header)

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
#include <vector>

namespace HBTK {
	namespace Paths {
		// Return the current working directory of the program.
		std::string current_working_directory();

		// Return the location of the compiled executable.
		std::string executable_path();

		// Get a list of files in the current directory
		std::vector<std::string> files_in_current_working_directory();
		std::vector<std::string> files_in_current_working_directory(std::string extension);

		// Get a list of files in a path
		std::vector<std::string> files_in_directory(std::string path);
		std::vector<std::string> files_in_directory(std::string path, std::string file_extension);
	}
}