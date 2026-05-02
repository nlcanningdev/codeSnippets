/*#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Overhead {
private:
	sf::RenderWindow* window;
	sf::Texture texture;
	int screenWidth, screenHeight;
public:
	Overhead(int screenWidth, int screenHeight, std::string programName, uint8_t* screen);
	~Overhead();
	void render(uint8_t* screen);
};*/