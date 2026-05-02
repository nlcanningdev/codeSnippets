#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <compressapi.h>

//drop files onto the exe to archive them

/*writes all files to a single file
requires cabinet library, sfml library, fstream, vector, string, algorithm, iostream, Windows.h, stdio.h, compressapi.h, various files*/
void archiveWriter(std::vector<std::string> &filename) {
	COMPRESSOR_HANDLE Compressor = NULL;
	CreateCompressor(COMPRESS_ALGORITHM_XPRESS_HUFF, NULL, &Compressor);
	char * memblock;
	char * compMemblock;
	SIZE_T csize, finalSize;
	std::streampos total = 0;
	std::streampos increment = 0;
	std::vector<char *> memblocks;
	std::vector<std::streampos> size;
	std::ifstream in;
	std::ofstream out;
	for (int a = 0; a < filename.size(); ++a) {
		in.open(filename[a], std::ios::in | std::ios::binary | std::ios::ate);
		size.push_back(in.tellg());
		in.seekg(0);
		memblocks.push_back(memblock);
		memblocks[a] = new char[size[a]];
		in.read(memblocks[a], size[a]);
		in.close();
		in.clear();
	}
	for (int a = 0; a < size.size(); ++a) {
		total += size[a];
	}
	memblock = new char[total];
	for (int a = 0; a < memblocks.size(); ++a) {
		for (int b = 0; b < size[a]; b++) {
			memblock[b + increment] = memblocks[a][b];
		}
		increment += size[a];
	}
	out.open("nl.can", std::ios::out | std::ios::binary | std::ios::beg);
	Compress(Compressor, memblock, total, NULL, 0, &csize);
	compMemblock = new char[csize];
	Compress(Compressor, memblock, total, compMemblock, csize, &finalSize);
	out.write(compMemblock, finalSize);
	for (int a = 0; a < memblocks.size(); ++a) {
		delete[] memblocks[a];
	}
	delete[] memblock;
	out.close();
	out.clear();
	out.open("archivedata.txt", std::ios::out);
	out << finalSize << std::endl;
	for (int a = 0; a < size.size(); ++a) {
		out << size[a] << std::endl;
	}
	out.close();
	out.clear();
}

int main(int argc, char* argv[]) {
	std::vector<std::string> filename;
	//argv[0] is the program's path
	for (int i = 1; i < argc; ++i) {
		std::string file(argv[i]);
		filename.push_back(file);
	}
	std::sort(filename.begin(), filename.end());
	if (filename.size() > 0) {
		archiveWriter(filename);
		for (int a = 0; a < filename.size(); a++) {
			std::cout << "Copied " << filename[a] << std::endl;
		}
	}
	else
		std::cout << "Error: drag files onto exe or use command line" << std::endl;
	char a;
	std::cin >> a;
	return 0;
}