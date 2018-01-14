#include "stdafx.h"

#include <string>
#include <iostream>

#include <HBTK/Plot3DParser.h>
#include <HBTK/Plot3DWriter.h>


void print_mesh_info(std::vector<HBTK::StructuredMeshBlock2D> mesh2d,
	std::vector<HBTK::StructuredMeshBlock3D> mesh3d, bool three_dimensional) {
	int n_blocks = (three_dimensional ? (int)mesh3d.size() : (int)mesh2d.size());
	std::cout << "Mesh info:\n";
	std::cout << "\t3D mesh:\t" << (three_dimensional ? "True" : "False") << "\n";
	std::cout << "\tNumber of blocks:\t" << n_blocks << "\n";
	std::cout << "\tBlock\ti\tj\tk\n";
	for (int n = 0; n < n_blocks; n++) {
		int i, j, k;
		if (three_dimensional) std::tie(i, j, k) = mesh3d[n].extent();
		if (!three_dimensional) {
			std::tie(i, j) = mesh2d[n].extent();
			k = 1;
		}
		std::cout << "\t" << n << "\t" << i << "\t" << j << "\t" << k << "\n";
	}
	std::cout << "\n";
	for (int n = 0; (n < n_blocks) && three_dimensional; n++) {
		std::cout << "\tBlock " << n << "\n";
		double x, y, z;
		int ei, ej, ek;
		std::tie(ei, ej, ek) = mesh3d[n].extent();
		std::tie(x, y, z) = mesh3d[n].coord(0, 0, 0);
		std::cout << "\t\ti0,j0,k0:\t" << x << " " << y << " " << z << "\n";
		std::tie(x, y, z) = mesh3d[n].coord(ei-1, 0, 0);
		std::cout << "\t\tid,j0,k0:\t" << x << " " << y << " " << z << "\n";
		std::tie(x, y, z) = mesh3d[n].coord(0, ej-1, 0);
		std::cout << "\t\ti0,jd,k0:\t" << x << " " << y << " " << z << "\n";
		std::tie(x, y, z) = mesh3d[n].coord(0, 0, ek-1);
		std::cout << "\t\ti0,j0,kd:\t" << x << " " << y << " " << z << "\n";
		std::tie(x, y, z) = mesh3d[n].coord(ei-1, ej-1, ek-1);
		std::cout << "\t\tid,jd,kd:\t" << x << " " << y << " " << z << "\n\n";
	}
	std::cout << "\n";
	return;
}

void write_mesh_out_2d(std::vector<HBTK::StructuredMeshBlock2D> mesh2d, bool ascii,
	bool block_count, std::string path) {
	HBTK::Plot3D::Plot3DWriter writer;
	std::cout << "\nWriting to " << path << "\n";
	std::cout << "Writing 2D\n";
	std::cout << "Writing block count?\t" << block_count << "\n";
	std::cout << "ASCII?\t" << ascii << "\n";

	writer.three_dimensional = false;
	writer.write_binary = !ascii;
	writer.no_block_count = !block_count;
	for (auto & mesh : mesh2d) {
		writer.add_mesh_block2d(mesh);
	}
	writer.write(path);
}

void write_mesh_out_3d(std::vector<HBTK::StructuredMeshBlock3D> mesh3d, bool ascii,
	bool block_count, std::string path) {
	HBTK::Plot3D::Plot3DWriter writer;
	std::cout << "\nWriting to " << path << "\n";
	std::cout << "Writing 3D mesh.\n";
	std::cout << "Block count?\t" << (block_count ? "True" : "False") << "\n";
	std::cout << "ASCII?\t" << (ascii ? "True" : "False") << "\n";

	writer.three_dimensional = true;
	writer.write_binary = !ascii;
	writer.no_block_count = !block_count;
	for (auto & mesh : mesh3d) {
		writer.add_mesh_block3d(mesh);
	}
	writer.write(path);
}

void print_help() {
	std::cout << "Help:\n";
	std::cout << "This program reads in a Plot3D mesh, and can spit it out in a different format.\n";
	std::cout << "Usage: $PROGRAM inputfile.ext1 [optional outputfile.ext]\n";
	std::cout << "Flags:\n";
	std::cout << "\t-i\tindicates input file flag\n";
	std::cout << "\t-o\tindicates output file flat\n";
	std::cout << "\t-*a\tASCII file\n";
	std::cout << "\t-*b\tBinary file\n";
	std::cout << "\t-i3\t3D mesh (input file only)\n";
	std::cout << "\t-i2\t2D mesh (input file only)\n";
	std::cout << "\t-*n\tNo mesh block count\n";
	std::cout << "\t-oe\tExtrude a 2d input mesh to 3d (z=0, 1)\n";
	std::cout << "\t-sx\tSwitch the j,k local coordinates in mesh blocks in output files.\n";
	std::cout << "\t-sy\tSwitch the i,k local coordinates in mesh blocks in output files.\n";
	std::cout << "\t-sz\tSwitch the i,j local coordinates in mesh blocks in output files.\n";
	std::cout << "\n";
	return;
}


int parse_command_line(int argc, char *argv[], bool &ascii_in, bool &three_dimensional_in, bool &no_block_in,
 std::string &path_in,
	bool &ascii_out, bool &no_block_out, bool &extrude, std::string &path_out, int & swap_axis) {

	bool path_in_set = false;
	std::string arg; // For debugging...
	if (argc == 1) { print_help(); }
	for (int i = 1; i < argc; i++) {
		arg = argv[i];
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'i') {
				switch (argv[i][2]) {
				case 'a':
					ascii_in = true;
					continue;
				case 'b':
					ascii_in = false;
					continue;
				case '3':
					three_dimensional_in = true;
					continue;
				case '2':
					three_dimensional_in = false;
					continue;
				case 'n':
					no_block_in = true;
					continue;
				default:
					return i;
				}
				continue;
			}
			else if (argv[i][1] == 'o') {
				switch (argv[i][2]) {
				case 'a':
					ascii_out = true;
					continue;
				case 'b':
					ascii_out = false;
					continue;
				case 'n':
					no_block_out = true;
					continue;
				case 'e':
					extrude = true;
					continue;
				default:
					return i;
				}
				continue;
			}
			else if (argv[i][1] == 's') {
				switch (argv[i][2]) {
				case 'x':
					swap_axis = 0;
					continue;
				case 'y':
					swap_axis = 1;
					continue;
				case 'z':
					swap_axis = 2;
					continue;
				default:
					return i;
				}
			}
			return i;
		}
		else {
			if (!path_in_set) {
				path_in = argv[i];
				path_in_set = true;
			}
			else {
				path_out = argv[i];
			}
		}
	}


	return 0;
}

int main(int argc, char *argv[])
{
	std::cout << "Plot3D demo\nHJA Bird 2018\n";

	std::string input_path, output_path;
	int swap_axis = -1;
	bool three_dimensional, ascii_in, no_block_count_in;
	bool extrude, ascii_out, no_bc_out;
	HBTK::Plot3D::Plot3DParser parser;
	std::vector<HBTK::StructuredMeshBlock2D> meshes_2d;
	std::vector<HBTK::StructuredMeshBlock3D> meshes_3d;
	ascii_in = ascii_out = three_dimensional = true;
	no_block_count_in = no_bc_out = extrude = false;

	if (int error_arg = parse_command_line(argc, argv, ascii_in, three_dimensional, no_block_count_in,
 input_path,
		ascii_out, no_bc_out, extrude, output_path, swap_axis)) {
		std::cout << "Error at arg " << error_arg << ".\n";
		std::cout << "\t>\t" << argv[error_arg] << "\n";
		print_help();
		return 1;
	}
	if (three_dimensional && extrude) {
		std::cout << "Input mesh is 3D - cannot be extruded.\n"; return 1;
	}

	parser.add_2D_block_function(
		[&](HBTK::StructuredMeshBlock2D mesh) { meshes_2d.emplace_back(mesh); return true; }
	);
	parser.add_3D_block_function(
		[&](HBTK::StructuredMeshBlock3D mesh) { meshes_3d.emplace_back(mesh); return true; }
	);

	parser.number_of_dimensions = (three_dimensional ? 3 : 2);
	parser.parse_as_binary = !ascii_in;
	parser.single_block = no_block_count_in;
	std::cout << "Input:\n" << input_path << "\n";

	try {
		parser.parse(input_path);
		print_mesh_info(meshes_2d, meshes_3d, three_dimensional);
	}
	catch (int i) {
		std::cout << "FAILED!\nDid you get the input flags right? Are you sure this file is good?\n";
		if (i > 0) {
			std::cout << "Error possibly around line " << i << "\n";
		}
		else {
			std::cout << "Error opening:\t" << input_path << "\n";
		}
		return -1;
	}
	catch (...) {
		std::cout << "FAILED for unknown reason. Did you get the input format flags right\n"
			"and are you sure the file is a good one?\n";
		return -1;
	}
	if (output_path != "") {
		if (extrude) {
			for (int n = 0; n < (int)meshes_2d.size(); n++) {
				meshes_3d.emplace_back(meshes_2d[n].extrude_to_3D({ 0, 1 }));
			}
		}
		if (swap_axis > -1) {
			for (int i = 0; i < (int)meshes_3d.size(); i++) {
				auto &mesh = meshes_3d[i];
				switch (swap_axis) {
				case 0:
					std::cout << "Switching j,k internal coordinates of block " << i << ".\n";
					mesh.swap_internal_coordinates_jk();
					continue;
				case 1:
					std::cout << "Switching i,k internal coordinates of block " << i << ".\n";
					mesh.swap_internal_coordinates_ik();
					continue;
				case 2:
					std::cout << "Switching i,j internal coordinates of block " << i << ".\n";
					mesh.swap_internal_coordinates_ij();
					continue;
				}
			}
		}


		if (three_dimensional || extrude) {
			write_mesh_out_3d(meshes_3d, ascii_out, !no_bc_out, output_path);
		}
		else {
			write_mesh_out_2d(meshes_2d, ascii_out, !no_bc_out, output_path);
		}
	}

    return 0;
}

