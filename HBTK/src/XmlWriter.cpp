#include "XmlWriter.h"
/*////////////////////////////////////////////////////////////////////////////
XmlWriter.cpp

A class to help writing Xml files.

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

HBTK::Xml::XmlWriter::XmlWriter()
{
}

void HBTK::Xml::XmlWriter::open_tag(std::ostream & stream, const std::string & tag_name, std::vector<std::pair<std::string, std::string>> parameters)
{
	stream << "<";
	stream << tag_name;
	for (auto & param: parameters) {
		stream << " ";
		stream << param.first;
		stream << "=";
		stream << "\"" << param.second << "\"";
	}
	stream << ">\n";
	m_tag_stack.push(tag_name);
	return;
}

void HBTK::Xml::XmlWriter::close_tag(std::ostream & stream)
{
	stream << "</";
	stream << m_tag_stack.top();
	m_tag_stack.pop();
	stream << ">\n";
	return;
}

void HBTK::Xml::XmlWriter::header(std::ostream & stream, std::string version, std::string encoding)
{
	stream << "<?xml version=\"" << version << "\" encoding=\"" << encoding << "\"?>\n";
	return;
}

int HBTK::Xml::XmlWriter::tag_depth() const
{
	return m_tag_stack.size();
}
