#include "Paths.h"
/*////////////////////////////////////////////////////////////////////////////
Paths.cpp

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

#include <cstdio>  // For FILENAME_MAX
#include <exception>
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#define GetCurrentDir _getcwd	// For current_working_directory()
#else
#include <unistd.h>
#define GetCurrentDir getcwd	// For current_working_directory()
#endif

std::string HBTK::Paths::current_working_directory()
{
	// Shamelessly stolen from StackOverflow
	char current_path[FILENAME_MAX];
	if (!GetCurrentDir(current_path, sizeof(current_path)))
	{
		throw std::runtime_error(
			"Could not get current working directory. " __FILE__
			" : " + std::to_string(__LINE__)
			);
	}
	return std::string(current_path);
}


std::string HBTK::Paths::executable_path()
{
#ifdef _WIN32
	char exe_path[FILENAME_MAX];
	int written = GetModuleFileName(NULL, exe_path, sizeof(exe_path));
	if (!written) {
		throw std::runtime_error(
			"Could not get current executable directory. " __FILE__
			" : " + std::to_string(__LINE__)
		);
	}
#else
	char exe_path[FILENAME_MAX]
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = MIN(readlink(szTmp, exe_path, FILENAME_MAX), FILENAME_MAX - 1);
	if (bytes >= 0)
		exe_path[bytes] = '\0';
#endif
	return std::string(exe_path);
}

std::vector<std::string> HBTK::Paths::files_in_current_working_directory()
{
	return files_in_current_working_directory("*");
}

std::vector<std::string> HBTK::Paths::files_in_current_working_directory(std::string extension)
{
	return files_in_directory(current_working_directory(), extension);
}

std::vector<std::string> HBTK::Paths::files_in_directory(std::string path)
{
	return files_in_directory(path, "*");
}

std::vector<std::string> HBTK::Paths::files_in_directory(std::string path, std::string file_extension)
{
	std::vector<std::string> files;
#ifdef _WIN32
	std::string search_path = path + "/*." + file_extension;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				files.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
#else
	// Linux code here. To do.
#endif
	return files;
}



