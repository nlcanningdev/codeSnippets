#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include <compressapi.h>
#include <string>

void decompressor() {
	DECOMPRESSOR_HANDLE Decompressor = NULL;
	CreateDecompressor(COMPRESS_ALGORITHM_XPRESS_HUFF, NULL, &Decompressor);
	char * memblock;
	char * dememblock;
	SIZE_T totalSize, afterSize, endSize;
	std::string container;
	long long container2;
	std::ifstream in("archivedata.txt", std::ios::in | std::ios::binary | std::ios::beg);
	std::getline(in, container);
	container2 = std::stol(container);
	totalSize = container2;
	in.close();
	in.clear();
	memblock = new char[totalSize];
	in.open("nl.can", std::ios::in | std::ios::binary | std::ios::beg);
	in.read(memblock, totalSize);
	in.close();
	in.clear();
	Decompress(Decompressor, memblock, totalSize, NULL, 0, &afterSize);
	dememblock = new char[afterSize];
	Decompress(Decompressor, memblock, totalSize, dememblock, afterSize, &endSize);
	std::ofstream out("nl.can", std::ios::out | std::ios::binary | std::ios::beg);
	out.write(dememblock, endSize);
	out.close();
	out.clear();
	delete[] memblock;
	delete[] dememblock;
}

int main() {
	decompressor();
	return 0;
}