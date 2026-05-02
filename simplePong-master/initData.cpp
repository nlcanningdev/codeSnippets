#include "initData.h"
#include <string>
#include <cstdlib>
#include <fstream>

void initData(Image*& image,Sprite*& sprite, Sound*& sound, sf::Music*& music, int& imageNum, int& spriteNum, int& musicNum, int& spriteNum) {
	std::string input;
	std::string* filePath;
	std::ifstream readFile;
	readFile.open("..\\assets\\program.data");
	std::getline(readFile, input);
	imageNum = atoi(input.c_str());
	std::getline(readFile, input);
	soundNum = atoi(input.c_str());
	std::getline(readFile, input);
	musicNum = atoi(input.c_str());
	filePath = new std::string[imageNum];
	for (int a = 0; a < imageNum; ++a) {
		std::getline(readFile, filePath[a]);
	}
	for (int a = 0; a < spriteNum; ++a) {
		int integer;
		std::getline(readFile, input);
		spriteX[a] = atoi(input.c_str());
		std::getline(readFile, input);
		spriteY[a] = atoi(input.c_str());
		std::getline(readFile, input);
		spriteIndex[a] = atoi(input.c_str());
		std::getline(readFile, input);
		integer = atoi(input.c_str());
		spriteDisplay[a] = integer;
		std::getline(readFile, input);
		integer = atoi(input.c_str());
		spriteLayer[a] = integer;
	}
	readFile.close();
	readFile.clear();
}
