#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <fstream>

class Image {
	private:
		uint16_t width; uint16_t height;
		sf::Uin8* pixels;
	public:
		Image(size_t startpos);
		inline ~Image() { delete[] pixels; }
		inline int getWidth() { return width; }
		inline int getHeight() { return heigh; }
		void pixelsToScreen(sf::Uint8* screen);
}

Image::Image(size_t startops) {
	std::ifstream readFile;
	readFile.open("assets.nlc", std::ios::binary);
	readFile.seekg(startpos);
	readFile.read(reinterpret_cast<char*>(&width), sizeof(uint16_t));
	readFile.read(reinterpret_cast<char*>(&height), sizeof(uint16_t));
	pixels = new sf::Uint8[width * height * 4];
	readFile.read(reinterpret_cast<char*>(pixels), sizeof(sf::Uint8) * (width * height * 4));
	readFile.close();
	readFile.clear();
}

void Image(sf::Uint8* screen, int x, int y, int screenWidth, int screenHeight) {
	bool transparent = false;
	bool alphaBlend = false;
	size_t startpos = (y * (screenWidth * 4)) + (x * 4);
	for (int a = 0; a < height; ++a) {
		size_t startpos2 = startpos + ((a * (screenWidth * 4)));
		size_t startpos3 = a * (width * 4);
		for (int b = 0; b < width * 4; ++b) {
			transparent = false;
			if ((b == 0 || b % 4 == 0) && pixels[startpos3 + b + 3] == 0) {
				transparent = true;
			}
			else if((b == 0 || b % 4 == 0) && (pixels[startpos3 + b + 3] > 0 && pixels[startpos3 + b + 3] < 255)) {
				alphaBlend = true;
			}
			if (!transparent && !alphaBlend)
				screen[startpos2 + b] = pixels[startpos3 + b];
			else {
				if(alphaBlend) {
					screen[startpos2 + b] = ((pixels[startpos3 + b + 3] * (pixels[startpos3 + b] - screen[startpos2 + b])) / 255) + screen[startpos2 + b];
					screen[startpos2 + b + 1] = ((pixels[startpos3 + b + 3] * (pixels[startpos3 + b + 1] - screen[startpos2 + b + 1])) / 255) + screen[startpos2 + b + 1];
					screen[startpos2 + b + 2] = ((pixels[startpos3 + b + 3] * (pixels[startpos3 + b + 2] - screen[startpos2 + b + 2])) / 255) + screen[startpos2 + b + 2];
				}
				b += 3;
			}
		}
	}
}

int main() {
	int screenWidth = 800; int screenHeight = 600;
	sf::Uint8* screen = new sf::Uint8*[width * height * 4];
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "nlcan launcher");
	sf::Texture texture;
	texture.create(screenWidth, screenHeight);
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}
		texture.update(pixels);
		texture.update(window);
		window.display();
	}
	return 0;
}

// https://www.sfml-dev.org/tutorials/2.4/graphics-draw.php
// https://en.sfml-dev.org/forums/index.php?topic=3543.0
// https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Image.php#a1c2b960ea12bdbb29e80934ce5268ebf
// https://www.sfml-dev.org/tutorials/2.4/graphics-sprite.php

/*#include <iostream>
#include <cstdint>

int main()
{
    uint8_t alpha = 25;
    uint8_t answer = (240 - (0.9 * 255)) / (float)(alpha / 255);
    std::cout << (int)answer << std::endl;
    return 0;
}*/

//https://stackoverflow.com/questions/746899/how-to-calculate-an-rgb-colour-by-specifying-an-alpha-blending-amount
