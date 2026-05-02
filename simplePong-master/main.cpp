#define x64SYSTEM //set to x86SYSTEM when wanted

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <cstdlib>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <direct.h>
#include <atomic>
#include <thread>
#include <functional>
#include <future>
#include "image.h"
#include "sprite.h"
#include "initData.h"
#include "network.h"
#include "sound.h"
#ifdef x64SYSTEM
#include "x64Overhead.h"
#include "x64event.h"
#endif
#ifdef x86SYSTEM
#include "x86Overhead.h"
#include "x86event.h"
#endif

int main(int argc, char *argv[]) {
	int sceneNum = 1; //total number of scenes, network doesn't count for now
	bool sceneLoaded = false;
	_chdir("bin\\");
	Network network;
	network.setupNetwork();
	sf::Music music;
	music.openFromFile("..\\assets\\pongBGM.ogg");
	music.setLoop(true);
	music.setVolume(70);
	Sound* sound = new Sound[2];
	sound[0].setupSound("..\\assets\\pointScore.ogg");
	sound[1].setupSound("..\\assets\\paddleHit.ogg");
	int maxLayers = 2;
	char input = '\0';
	int screenWidth = 1500; int screenHeight = 1000; 
	size_t screenSize = screenWidth * screenHeight * 4;
	int imageNum = 16; int spriteNum = 8;
	std::string* filePath = new std::string[imageNum];
	int* spriteX = new int[spriteNum];
	int* spriteY = new int[spriteNum];
	int* spriteIndex = new int[spriteNum];
	bool* spriteDisplay = new bool[spriteNum];
	int* spriteLayer = new int[spriteNum];
	getData(filePath, imageNum, spriteX, spriteY, spriteIndex, spriteDisplay, spriteLayer, spriteNum);
	uint8_t* screen = new uint8_t[screenSize];
	Image* image = new Image[imageNum];
	for (int a = 0; a < imageNum; ++a) {
		image[a].setupImage(filePath[a]);
	}
	Sprite* sprite = new Sprite[spriteNum];
	for (int a = 0; a < spriteNum; ++a) {
		sprite[a].setupSprite(spriteX[a], spriteY[a], spriteIndex[a], spriteDisplay[a], spriteLayer[a]);
	}
	delete[] filePath;
	delete[] spriteX;
	delete[] spriteY;
	delete[] spriteIndex;
	delete[] spriteDisplay;
	delete[] spriteLayer;
	Overhead overhead(screenWidth, screenHeight, "pong", screen);
	srand((unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	std::chrono::microseconds duration(16667);
	bool game = true;
	bool gameComplete = false;
	bool roundComplete = false;
	int playerScore = 0;
	int aiScore = 0;
	int ballY = 0; //for the ball
	int ballX = rand() % 2; //for the ball
	if (ballX == 0)
		ballX = -10;
	else
		ballX = 10;
	int playerVelocity = 0;
	int aiVelocity = 0;
	music.play();
	auto start_time = std::chrono::steady_clock::now();
	auto current_time = std::chrono::steady_clock::now();
	while (game) {
		event(network, playerVelocity, aiVelocity, input, game);
		if (gameComplete) {
			sprite[2].setDisplay(false);
			sprite[5].setDisplay(true);
			sprite[6].setDisplay(true);
			if (aiScore == 10) {
				if (network.getHost() == 'y')
					sprite[5].setImageIndex(12);
				else
					sprite[5].setImageIndex(13);
			}
			else if (playerScore == 10) {
				if (network.getHost() == 'y')
					sprite[5].setImageIndex(13);
				else
					sprite[5].setImageIndex(12);
			}
			if (input == 'y') {
				gameComplete = false;
				playerScore = 0;
				aiScore = 0;
				sprite[5].setDisplay(false);
				sprite[6].setDisplay(false);
				sprite[0].setY(499);
				sprite[1].setY(499);
				sprite[3].setImageIndex(2);
				sprite[4].setImageIndex(2);
				sprite[2].setDisplay(true);
			}
			else if (input == 'n')
				game = false;
		}
		if (!gameComplete) {
			if (!roundComplete) {
				int moveDirection = 0; //0 = not moving, 1 = moving down, 2 = moving up, for player
				std::chrono::duration<double> elapsed = current_time - start_time;
				if (elapsed >= duration) {
					if (network.getMode() == 'y') {
						if (network.getHost() == 'n') {
							playerVelocity = network.receivePacket();
							network.sendPacket(aiVelocity);
						}
						else {
							network.sendPacket(playerVelocity);
							aiVelocity = network.receivePacket();
						}
					}
					sprite[2].setY(sprite[2].getY() + ballY);
					sprite[2].setX(sprite[2].getX() + ballX);
					if(sprite[2].getY() <= 35) {
						sprite[2].setY(36);
						ballY *= -1;
					}
					else if(sprite[2].getY() + image[sprite[2].getImageIndex()].getHeight() >= screenHeight) {
						sprite[2].setY(screenHeight - image[sprite[2].getImageIndex()].getHeight() - 1);
						ballY *= -1;
					}
					if(sprite[2].getX() <= sprite[0].getX() + image[sprite[0].getImageIndex()].getWidth()) {
						if(sprite[2].getY() < sprite[0].getY() + image[sprite[0].getImageIndex()].getHeight() && sprite[2].getY() + image[sprite[2].getImageIndex()].getHeight() > sprite[0].getY()) {
							sound[1].playSound();
							ballX *= -1;
							ballY += playerVelocity;
							ballX += 3;
							sprite[2].setX(sprite[0].getX() + image[sprite[0].getImageIndex()].getWidth() + 1);
						}
					}
					else if(sprite[2].getX() + image[sprite[2].getImageIndex()].getWidth() >= sprite[1].getX()) {
						if(sprite[2].getY() < sprite[1].getY() + image[sprite[1].getImageIndex()].getHeight() && sprite[2].getY() + image[sprite[2].getImageIndex()].getHeight() > sprite[1].getY()) {
							sound[1].playSound();
							ballX *= -1;
							ballY += aiVelocity;
							ballX -= 3;
							sprite[2].setX(sprite[1].getX() - 1 - image[sprite[2].getImageIndex()].getWidth());
						}
					}
					if(sprite[2].getX() < 0) {
						sound[0].playSound();
						++aiScore;
						if(aiScore < 10)
							sprite[4].setImageIndex(sprite[4].getImageIndex() + 1);
						roundComplete = true;
					}
					else if(sprite[2].getX() > screenWidth) {
						sound[0].playSound();
						++playerScore;
						if(playerScore < 10)
							sprite[3].setImageIndex(sprite[3].getImageIndex() + 1);
						roundComplete = true;
					}
					sprite[0].setY(sprite[0].getY() + playerVelocity);
					if (network.getMode() == 'n') {
						if (sprite[2].getY() > sprite[1].getY()) {
							aiVelocity = 20;
						}
						else if (sprite[2].getY() < sprite[1].getY()) {
							aiVelocity = -20;
						}
					}
					sprite[1].setY(sprite[1].getY() + aiVelocity);
					for(int a = 0; a < 2; ++a) {
						if (sprite[a].getY() <= 35)
							sprite[a].setY(36);
						if (sprite[a].getY() + image[sprite[a].getImageIndex()].getHeight() >= screenHeight)
							sprite[a].setY(screenHeight - image[sprite[a].getImageIndex()].getHeight() - 1);
					}
					start_time = std::chrono::steady_clock::now();
				}
				current_time = std::chrono::steady_clock::now();
				elapsed = current_time - start_time;
			}
			else if(roundComplete) {
				ballY = 0;
				ballX = rand() % 2;
				if (ballX == 0)
					ballX = -10;
				else
					ballX = 10;
				if(aiScore == 10 || playerScore == 10)
					gameComplete = true;
				roundComplete = false;
				input = '\0';
				sprite[2].setX(749);
				sprite[2].setY(500);
			}
		}
		for (int a = 0; a < screenSize; ) {
			screen[a] = 0;
			++a;
			screen[a] = 0;
			++a;
			screen[a] = 0;
			++a;
			screen[a] = 255;
			++a;
		}
		for (int a = 0; a < maxLayers; ++a) {
			for (int b = 0; b < spriteNum; ++b) {
				if (sprite[b].getLayer() == a) {
					if (sprite[b].getDisplay())
						image[sprite[b].getImageIndex()].writePixels(screen, sprite[b].getX(), sprite[b].getY(), screenWidth, screenHeight);
				}
			}
		}
		overhead.render(screen);
	}
	music.stop();
	delete[] sound;
	delete[] image;
	delete[] sprite;
	return 0;
}
