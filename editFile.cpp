#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include <cstdlib>

//receives a file path, a width and a height
//width and height are stored as uint16_t
//the image at the path is stored in a 2d array of uint8_t

int main(int argc, char *argv[]) {
	std::string path = argv[1];
	std::string input;
	int integer = 0;
	uint16_t w, h;
	input = argv[2];
	integer = std::atoi(input.c_str());
	std::cout << integer << std::endl;
	w = (uint16_t)integer;
	input = argv[3];
	integer = std::atoi(input.c_str());
	std::cout << integer << std::endl;
	h = (uint16_t)integer;
	uint8_t** img;
	int full = w*h;
	img = new uint8_t* [full];
	for(int a = 0; a < full; ++a) {
		img[a] = new uint8_t [4];
	}
	std::ifstream file;
	file.open(path.c_str());
	for(int a = 0; a < full; ++a) {
		for(int b = 0; b < 4; ++b) {
			file >> input;
			integer = std::atoi(input.c_str());
			img[a][b] = (uint8_t)integer;
		}
	}
	file.close();
	std::ofstream file2;
	file2.open(path.c_str(), std::ios::out | std::ios::binary);
	file2.write((char*)&w, sizeof(uint16_t));
	file2.write((char*)&h, sizeof(uint16_t));
	for(int a = 0; a < full; ++a) {
		for(int b = 0; b < 4; ++b) {
			file2.write((char*)&img[a][b], sizeof(uint8_t));
		}
	}
	file2.close();
	file2.clear();
	for(int a = 0; a < full; ++a) {
		delete[] img[a];
	}
	delete[] img;
	return 0;
}