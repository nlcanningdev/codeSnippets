/*
asks if tilesetInfo.data exists
asks to overwrite file
if tilesetInfo.data does not exist, it opens it for writing
if yes, it opens it for reading

read:
get imageNum as std::size_t
create array imageData of type ImageData of size imageNum
store existing imageName, positionX, positionY, width, and height data therein
close tilesetInfo.data, reopen for writing

write:
create object newImageData of type imageData
get imageName, positionX, positionY, width and height from user
one by one, storing them in newImageData
write imageNum + 1 to tilesetInfo.data
write imageData array to tilesetInfo.data
write newImageData to tilesetInfo.data
close tilesetInfo.data
end program
*/

#include <fstream>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

struct ImageData {
	std::string imageName;
	std::size_t positionX, positionY, width, height;
};

int main(int argc, char* args[]) {
	/*char fileExists = 'n';
	char fileOverwrite = 'n';
	char fileModifyOrAppend = '0';
	std::size_t newImageDataNum = 0;
	std::size_t imageNum = 0;
	std::size_t imageModifyNum = 0;
	ImageData* imageData;
	ImageData newImageData;
	std::ifstream readFile;
	std::ofstream writeFile;
	std::string fileName = "pixiAssets/img/tilesetInfo.data";
	std::cout << "does " << fileName << " exist(y/n): ";
	std::cin >> fileExists;
	if (fileExists == 'y') {
		std::cout << "overwrite " << fileName << "(y/n): ";
		std::cin >> fileOverwrite;
		if (fileOverwrite == 'n') {
			std::cout << "modify or append(0/1): ";
			std::cin >> fileModifyOrAppend;
			if (fileModifyOrAppend == '1') {
				std::cout << "number of images to append: ";

			}
			readFile.open(fileName.c_str(), std::ios::binary);
			readFile.read(reinterpret_cast<char*>(&imageNum), sizeof(std::size_t));
			imageData = new ImageData[imageNum];
			for (std::size_t a = 0; a < imageNum; ++a) {
				readFile.read(reinterpret_cast<char*>(&imageData[a].imageName), sizeof(std::string));
				readFile.read(reinterpret_cast<char*>(&imageData[a].positionX), sizeof(std::size_t));
				readFile.read(reinterpret_cast<char*>(&imageData[a].positionY), sizeof(std::size_t));
				readFile.read(reinterpret_cast<char*>(&imageData[a].width), sizeof(std::size_t));
				readFile.read(reinterpret_cast<char*>(&imageData[a].height), sizeof(std::size_t));
			}
			readFile.close();
			readFile.clear();
		}
	}
	writeFile.open(fileName.c_str(), std::ios::binary);

	return 0;*/

	/*
	std::ofstream writeFile;
	writeFile.open("pixiAssets/img/test.data", std::ios::binary);
	std::string test1 = "test1";
	std::string test2 = "test2";
	for (std::size_t a = 0; a < test1.length(); ++a) {
		writeFile.write((char*)&test1[a], sizeof(char));
	}
	for (std::size_t a = 0; a < test2.length(); ++a) {
		writeFile.write((char*)&test2[a], sizeof(char));
	}
	writeFile.close();
	writeFile.clear();
	return 0;*/

	int width = 800;
	int height = 600;
	std::string fileName = "tileset.png";

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("tilesetPacker",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	int imageFlag = IMG_INIT_PNG;
	IMG_Init(imageFlag);
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	SDL_LockSurface(surface);
	std::ofstream writeFile;
	int32_t surfaceWidth = surface->w;
	int32_t surfaceHeight = surface->h;
	std::cout << "surfaceWidth: " << surfaceWidth << std::endl;
	std::cout << "surfaceHeight: " << surfaceHeight << std::endl;
	char test;
	std::cin >> test;
	uint8_t** pixels;
	int bytesPerPixel = surface->format->BytesPerPixel;
	if (bytesPerPixel == 4) {
		pixels = new uint8_t*[surfaceWidth * surfaceHeight];
		writeFile.open("tileset.data", std::ios::binary | std::ios::trunc);
		writeFile.write((char*)&surfaceWidth, sizeof(int32_t));
		writeFile.write((char*)&surfaceHeight, sizeof(int32_t));
		size_t y = 0;
		size_t x = 0;
		for (size_t a = 0; a < (surfaceWidth * surfaceHeight); ++a) {
			pixels[a] = new uint8_t[4];
			SDL_GetRGBA(*(Uint32*)surface->pixels + y * surface->pitch + x * bytesPerPixel, surface->format, &pixels[a][0], &pixels[a][1], &pixels[a][2], &pixels[a][3]);
			for (int b = 0; b < 4; ++b) {
				writeFile.write((char*)&pixels[a][b], sizeof(uint8_t));
			}
			++x;
			if (x >= surfaceWidth) {
				x = 0;
				++y;
			}
		}
		writeFile.close();
		writeFile.clear();
		for (size_t a = 0; a < (surfaceWidth * surfaceHeight); ++a) {
			delete[] pixels[a];
		}
		delete[] pixels;
	}
	SDL_UnlockSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}
