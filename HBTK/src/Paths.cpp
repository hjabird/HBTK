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

#include <algorithm>
#include <cstdio>  // For FILENAME_MAX
#include <exception>
#include <istream>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#define GetCurrentDir _getcwd	// For current_working_directory()
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#define GetCurrentDir getcwd	// For current_working_directory()
#endif

#include "Token.h"
#include "Tokeniser.h"

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
	char exe_path[FILENAME_MAX];
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = std::min((int)readlink(szTmp, exe_path, FILENAME_MAX), FILENAME_MAX - 1);
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
	DIR *dir_pointer;
	struct dirent *epdf;
	dir_pointer = opendir(path.c_str());
	if (dir_pointer != NULL) {
		while (epdf = readdir(dir_pointer)) {
			files.push_back(epdf->d_name);
		}
	}
	closedir(dir_pointer);
#endif
	return files;
}

HBTK::Path::Path()
	: m_path()
{
}

HBTK::Path::Path(const std::string & path)
	: m_path()
{
	*this = path;
	return;
}

HBTK::Path & HBTK::Path::operator=(const std::string & other) 
{
	std::istringstream str(other);
	Tokeniser tokeniser(&str);
	std::vector<Token> toks;
	while (!tokeniser.eof()) {
		toks.push_back(tokeniser.next());
	}

	std::string tmp;
	for (auto & t : toks) {
		if (t.iswhitespace()) {
			throw std::invalid_argument("Whitespace in path " + other + " is not acceptable. "
				__FILE__ " : " + std::to_string(__LINE__));
		}

		if (!is_dir_separator(t.value())) {
			tmp += t.value();
		}
		else {
			if (!tmp.empty()) { m_path.push_back(tmp); }
#ifdef _WIN32
			m_path.push_back("\\");
#else
			m_path.push_back("/");
#endif
			tmp.clear();
		}
	}
	if (!tmp.empty()) {
		m_path.push_back(tmp);
	}
	return *this;
}

HBTK::Path & HBTK::Path::operator=(const Path & other) 
{
	m_path = other.m_path;
	return *this;
}


std::string HBTK::Path::to_string() const 
{
	std::string tmp;
	for (auto & t : m_path) {
		tmp += t;
	}
	return tmp;
}

HBTK::Path::operator std::string() const
{
	return to_string();
}

HBTK::Path HBTK::Path::absolute_path() const {
	auto tmp = *this;
	tmp.normalise();
#ifdef _WIN32
	if ((int)tmp.m_path[0].size() != 2 || tmp.m_path[0][1] != ':') 
	{
		std::string dir = Paths::current_working_directory();
		Path tmp2(dir);
		tmp2.join(tmp);
		tmp = tmp2;
	}
#else
	if (tmp.m_path[0] != "/") {
		std::string dir = Paths::current_working_directory();
		Path tmp2(dir);
		tmp2.join(tmp);
		tmp = tmp2;
	}
#endif
	return tmp;
}

HBTK::Path HBTK::Path::base_name() const 
{
	// We want to extract the last bit of the path. Eg:
	// a/b/c.exe -> c.exe
	// a/b -> b
	// a/b/c.exe/ -> '' 
	// Aim is to be identical to os.path.basename in Python
	std::string name;
	if ((int)m_path.size() == 0) { name = ""; }
	else if (!is_dir_separator(m_path.back())) {
		name = m_path.back();
	}
	else {
		int i = 1;
		int len = (int)m_path.size();
		while (i < len) {
			if (!is_dir_separator(m_path[len - i])) {
				name = m_path[len - i];
			}
			++i;
		}
	}
	return name;
}


std::string HBTK::Path::directory_name() const
{
	int len = (int)m_path.size();
	std::string dir;
	switch (len) {
	case 0:
		dir = "";
		break;
	case 1:
		if (m_path[0] != "/" && m_path[0] != "\\") {
			dir = "";
		}
		else {
			dir = m_path[0];
		}
		break;
	default:
		if (m_path.back() != "/" && m_path.back() != "\\") {
			dir = m_path[len - 3];
		}
		else
		{
			dir = m_path[len - 2];
		}
		break;
	}
	return dir;
}

bool HBTK::Path::exists()
{
	// If this looks like Stackoverflow answers...
	std::string as_str = to_string();
#ifdef _WIN32
		DWORD dwAttrib = GetFileAttributes(as_str.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES);
#else
	// https://stackoverflow.com/questions/12774207/
	struct stat buffer;
	return (stat(as_str.c_str(), &buffer) == 0);
#endif
}

bool HBTK::Path::is_absolute_path()
{

	if ((int)m_path.size() == 0) { return false; }
	std::string& str = m_path[0];
#ifdef _WIN32
	if (str.size() <= 1) return false;
	if (isupper(str[0]) && str[1] == ':') return true;
	else return false;
#else
	if (str[0] == "/") return true;
	else return false;
#endif
}

bool HBTK::Path::is_file() {
	std::string as_str = to_string();
#ifdef _WIN32
	DWORD dwAttrib = GetFileAttributes(as_str.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
	struct stat buffer;
	return (stat(as_str.c_str(), &buffer) == 0);
#endif
}

bool HBTK::Path::is_folder()
{
	std::string as_str = to_string();
#ifdef _WIN32
	DWORD dwAttrib = GetFileAttributes(as_str.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
	struct stat buffer;
	return (stat(as_str.c_str(), &buffer) == 0);
#endif
}

void HBTK::Path::normalise()
{
	remove_repeated_slashes();
	for (int i = 0; i < (int)m_path.size() - 1; ++i) {
		if (m_path[i] == "." && is_dir_separator(m_path[i + 1])) {
			m_path.erase(m_path.begin() + i, m_path.begin() + i + 2);
			--i;
			remove_repeated_slashes();
		}
		if (is_dir_separator(m_path[i]) && m_path[i + 1] == "..") {
			m_path.erase(m_path.begin() + i - 1, m_path.begin() + i + 3);
			--i; --i;
			remove_repeated_slashes();
			if (i - 1 > 0) {
				--i;
			}
		}
	}
	return;
}

void HBTK::Path::join(const Path & other)
{
	if (!is_dir_separator(m_path.back())
		&& !is_dir_separator(other.m_path.front())
		&& (int) other.m_path.size() > 0){
#ifdef _WIN32
		m_path.push_back("\\");
#else
		m_path.push_back("/");
#endif
	}
	for (auto & a : other.m_path) {
		m_path.push_back(a);
	}
	return;
}

bool HBTK::Path::is_dir_separator(const std::string & str)
{
	if(str == "\\" || str == "/") return true;
	else return false;
}


void HBTK::Path::remove_repeated_slashes(void) 
{
	int s = (int)m_path.size();
	for (int i = 0; i < s - 1; ++i) {
		if (is_dir_separator(m_path[i]) && is_dir_separator(m_path[i + 1])) {
			m_path.erase(m_path.begin() + i);
			s -= 1; --i;
		}
	}
	return;
}

std::ostream & HBTK::operator<<(std::ostream & os, const Path & path)
{
	os << path.to_string();
	return os;
}
