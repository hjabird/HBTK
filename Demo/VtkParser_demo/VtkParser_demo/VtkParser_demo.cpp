
#include <iostream>

#include <HBTK/Paths.h>
#include <HBTK/XmlParser.h>


int main(int argc, char* argv[]) {
	std::cout << "VtkParser demo. (C) HJA Bird 2018\n";
	std::cout << "Exe path: " << HBTK::Paths::executable_path() << "\n";
	std::cout << "Current working directory: " << HBTK::Paths::current_working_directory() << "\n";

	int indent = 0;

	HBTK::Xml::XmlParser parser;
	auto on_author =
		[](std::istream & stream) {
		while (stream.good()) {
			char c;
			stream.read(&c, 1);
			if (c == '<') break;
			std::cout << c;
		}
		stream.seekg((int)stream.tellg() - 1);
	};

	parser.on_element_open = 
		[&](std::string name, std::vector<std::pair<std::string, std::string>> key_vals) {
		std::cout << "# " << "NEW ELEMENT: ";
		std::cout << name << "\n";
		for (auto key_val : key_vals) {
			std::cout << "   " << key_val.first << "=" << key_val.second << "\n";
		}
		if (name == "author") { on_author(parser.xml_input_stream()); std::cout << "\n"; }
		indent += 1;
	};
	parser.on_element_close = 
		[&](std::string name) {
		std::cout << "# " << "CLOSED: " << name << "\n";
		indent -= 1;
	};

	parser.parse("sample_xml.xml");

	return 0;
}