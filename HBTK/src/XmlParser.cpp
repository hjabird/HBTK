#include "XmlParser.h"
/*////////////////////////////////////////////////////////////////////////////
XmlParser.cpp

Parse an XML file (SAX). What? Writing your own XML parser is silly? Pah.
This'll probably be deadly slow.

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

#include <cassert>

HBTK::Xml::XmlParser::XmlParser()
	: m_reading_file(false),
	m_encoding(UTF8),
	m_input_stream(NULL),
	m_element_stack()
{
	// Intentionally blank.
}

HBTK::Xml::XmlParser::~XmlParser()
{
	// Intentionally blank.
}

std::istream & HBTK::Xml::XmlParser::xml_input_stream()
{
	assert(m_input_stream != NULL);
	return *m_input_stream;
}

void HBTK::Xml::XmlParser::main_parser(std::ifstream & input_stream, std::ostream & error_stream)
{
	m_input_stream = &input_stream;
	m_reading_file = true;
	parse_prologue();
	while (m_input_stream->good()) {
		seek_next_xml_event();
		act_on_xml_event();
	}
	m_reading_file = false;
	m_input_stream = NULL;
	return;
}

void HBTK::Xml::XmlParser::parse_prologue()
{
	return;
}

void HBTK::Xml::XmlParser::parse_element_open()
{
	int tag_length = element_descriptor_length();
	std::string tag_string;
	for (int i = 0; i < tag_length; i++) {
		tag_string += normalised_next_char();
	}
	auto str_vector = tokenise(tag_string);
	std::string element_name = str_vector[0];
	// Reassemble strings with spaces.
	std::vector<std::pair<std::string, std::string>> parameters;
	for (int i = 1; i < (int)str_vector.size(); i++) {
		int eq_pos = str_vector[i].find('=', 0);
		if (eq_pos == (int)str_vector[i].size()) { throw - 2; };
		std::string name, value;
		name = str_vector[i].substr(0, eq_pos);
		if (str_vector[i][eq_pos + 1] != '\'') { throw - 3; }
		value = str_vector[i].substr(eq_pos + 1, str_vector[i].size() - eq_pos - 1);
		while (value.back() != '\'') {
			i++;
			if (i >= (int)str_vector.size()) throw - 4;
			value += str_vector[i];
		}
		value = value.substr(1, value.size() - 2);
		parameters.push_back({ name, value });
	}
	m_element_stack.push(element_name);
	on_element_open(element_name, parameters);
	return;
}

void HBTK::Xml::XmlParser::parse_element_close()
{
	int tag_length = element_descriptor_length();
	std::string tag_string;
	for (int i = 0; i < tag_length; i++) {
		tag_string += normalised_next_char();
	}
	if (tag_string == m_element_stack.top()) {
		m_element_stack.pop();
	}
	else {
		throw - 5;
	}
	on_element_close(tag_string);
	return;
}

void HBTK::Xml::XmlParser::parse_parser_event()
{
	return;
}

void HBTK::Xml::XmlParser::seek_next_xml_event()
{
	// Keep going until we find an xml tag opening.
	assert(m_input_stream != NULL);
	char next_character;
	do {
		next_character = normalised_next_char();
	} while ((next_character != '<') && m_input_stream->good());
}

int HBTK::Xml::XmlParser::element_descriptor_length()
{
	assert(m_reading_file);
	assert(m_input_stream != NULL);
	auto position = m_input_stream->tellg();
	int counter = 0;
	char next_char;
	do {
		counter++;
		next_char = normalised_next_char();
	} while ((m_input_stream->good()) && next_char != '>');
	m_input_stream->seekg(position);
	return counter;
}

void HBTK::Xml::XmlParser::act_on_xml_event()
{
	// Identify the type of XML event based on the next character.
	auto position = m_input_stream->tellg();
	char next_char = normalised_next_char();
	switch( next_char ){
	case ' ':
		throw -1;
		break;
	case '?':
		parse_parser_event();
		break;
	case '/':
		parse_element_close();
		break;
	default:
		parse_element_open();
		m_input_stream->seekg(position);
		break;
	}
	return;
}

char HBTK::Xml::XmlParser::normalised_next_char()
{
	assert(m_input_stream != NULL);
	assert(m_encoding == UTF8);
	char buffer;
	m_input_stream->read(&buffer, sizeof(buffer));
	return buffer;
}

