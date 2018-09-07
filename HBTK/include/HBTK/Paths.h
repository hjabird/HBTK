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

#include <ostream>
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

	class Path {
	public:
		// Construct an empty path.
		Path();
		// Construct a path from a string
		Path(const std::string & path);

		Path & operator=(const std::string & other);
		Path & operator=(const Path & other);

		// Obtain a string representation of the path
		std::string to_string() const;
		operator std::string() const;

		// Returns the absolute path. Essentually joins this path and
		// current working directory.
		Path absolute_path() const;

		// Returns the base name. Eg: a/file.exe -> file.exe,
		// a/ -> '', t/p/a -> a
		Path base_name() const;

		// Returns the name of the directory. Eg: a/b -> a
		// a/b/c -> b, a/b/c/ -> c
		std::string directory_name() const;

		//Checks if the path exists in the file system.
		bool exists();
		
		// Checks whether the path starts from '/'(linux)
		// or a drive letter (Windows)
		bool is_absolute_path();

		// Checks with operating system to see if the path
		// refers to a file.
		bool is_file();

		// Checks with OS to see if the path refers to a
		// normal directory.
		bool is_folder();
		
		// Removes unneeded parts from the path. 
		// Eg: a///c -> a/c, b/././c -> b/c, b/c/../d -> b/d
		void normalise();

		// Joins paths. Like Python.
		void join(const Path & other);

	
	protected:

		std::vector<std::string> m_path;
		static bool is_dir_separator(const std::string& str);
		void remove_repeated_slashes(void);
	};

	// Place into ostream.
	std::ostream& operator<<(std::ostream& os, const Path& path);
}
 