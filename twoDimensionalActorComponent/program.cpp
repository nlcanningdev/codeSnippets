#include "program.h"
#include "frameData.h"
#include "worldImageData.h"
#include "frameImageData.h"
#include "loadRequestForm.h"
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <iostream>


Program::Program() {
	this->runProgram = true;
	this->setupDone = false;
	this->firstTimeRendering = true;
	this->currentRenderingFrame = 0;
	this->worldData.numZonesX = 1;
	this->worldData.numZonesY = 1;
	this->worldData.zoneDimension = 800;
	this->camera.cameraWidth = 800;
	this->camera.cameraHeight = 800;
	this->camera.currentZoneX = 0;
	this->camera.currentZoneY = 0;
	this->camera.x = 0;
	this->camera.y = 0;
	this->textureNum = 2;
	this->texture = new SDL_Texture*[this->textureNum];
	for (int a = 0; a < this->textureNum; ++a) {
		this->texture[a] = nullptr;
	}
	this->surfaceNum = 2;
	this->surface = new SDL_Surface*[this->surfaceNum];
	for (int a = 0; a < this->surfaceNum; ++a) {
		this->surface[a] = nullptr;
	}
	this->subTextureNum = 2;
	this->subTexture = new SubTexture[this->subTextureNum];
	this->subTexture[0].clipX = 0;
	this->subTexture[0].clipY = 0;
	this->subTexture[0].clipWidth = 800;
	this->subTexture[0].clipHeight = 800;
	this->subTexture[0].textureReady = false;
	this->subTexture[1].clipX = 0;
	this->subTexture[1].clipY = 0;
	this->subTexture[1].clipWidth = 500;
	this->subTexture[1].clipHeight = 500;
	this->subTexture[1].textureReady = false;
	this->currentWorldImageDataNum = 2;
	this->maxWorldImageDataNum = 2;
	this->worldImageData = new WorldImageData[this->maxWorldImageDataNum];
	this->worldImageData[0].subTextureIndex = 0;
	this->worldImageData[0].worldZoneX = 0;
	this->worldImageData[0].worldZoneY = 0;
	this->worldImageData[0].worldX = 0;
	this->worldImageData[0].worldY = 0;
	this->worldImageData[0].worldWidth = 800;
	this->worldImageData[0].worldHeight = 800;
	this->worldImageData[1].subTextureIndex = 1;
	this->worldImageData[1].worldZoneX = 0;
	this->worldImageData[1].worldZoneY = 0;
	this->worldImageData[1].worldX = 0;
	this->worldImageData[1].worldY = 0;
	this->worldImageData[1].worldWidth = 500;
	this->worldImageData[1].worldHeight = 500;
	this->frameDataNum = 3;
	this->frameData = new FrameData[this->frameDataNum];
	this->loadRequestFormNum = 2;
	this->loadRequestForm = new LoadRequestForm[this->loadRequestFormNum];
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_DisplayMode displayMode;
	SDL_GetDesktopDisplayMode(0, &displayMode);
	std::cout << "monitor width: " << displayMode.w << std::endl;
	std::cout << "monitor height: " << displayMode.h << std::endl;
	this->window = SDL_CreateWindow("test environment", 50, 50, 800, 800, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	int imageFlags = IMG_INIT_PNG;
	IMG_Init(imageFlags);
}

Program::~Program() {
	if (this->worldImageData != nullptr)
		delete[] this->worldImageData;
	if (this->subTexture != nullptr)
		delete[] this->subTexture;
	if (this->frameData != nullptr)
		delete[] this->frameData;
	for (int a = 0; a < this->textureNum; ++a) {
		if(this->texture[a] != nullptr)
			SDL_DestroyTexture(this->texture[a]);
	}
	delete[] this->texture;
	for (int a = 0; a < this->surfaceNum; ++a) {
		if (this->surface[a] != nullptr)
			SDL_FreeSurface(this->surface[a]);
	}
	delete[] this->surface;
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

void Program::createSurface(int loadRequestFormIndex) {
	uint8_t* image = new uint8_t[this->loadRequestForm[loadRequestFormIndex].resourceSize];
	std::ifstream readFile;
	readFile.open(this->loadRequestForm[loadRequestFormIndex].fileName.c_str(), std::ios::binary);
	readFile.seekg(this->loadRequestForm[loadRequestFormIndex].resourceStart);
	readFile.read((char*)image, this->loadRequestForm[loadRequestFormIndex].resourceSize);
	readFile.close();
	readFile.clear();
	SDL_RWops* rw = SDL_RWFromMem(image, this->loadRequestForm[loadRequestFormIndex].resourceSize);
	this->surface[this->loadRequestForm[loadRequestFormIndex].surfaceIndex] = IMG_Load_RW(rw, 0);
	SDL_RWclose(rw);
	delete[] image;
}

void Program::createTexture(int loadRequestFormIndex) {
	this->texture[this->loadRequestForm[loadRequestFormIndex].textureIndex] = SDL_CreateTextureFromSurface(this->renderer, this->surface[this->loadRequestForm[loadRequestFormIndex].surfaceIndex]);
	SDL_FreeSurface(this->surface[this->loadRequestForm[loadRequestFormIndex].surfaceIndex]);
	this->surface[this->loadRequestForm[loadRequestFormIndex].surfaceIndex] = nullptr;
}

void Program::programCore() {
	if (!this->setupDone) {
		loadRequestForm[0].canBeOverwritten = false;
		loadRequestForm[0].fileName = "C:\\Users\\Nick\\source\\repos\\testEnvironment\\x64\\Release\\img0.png";
		loadRequestForm[0].resourceSize = 40587;
		loadRequestForm[0].resourceStart = 0;
		loadRequestForm[0].surfaceLoadRequired = true;

		loadRequestForm[1].canBeOverwritten = false;
		loadRequestForm[1].fileName = "C:\\Users\\Nick\\source\\repos\\testEnvironment\\x64\\Release\\img1.png";
		loadRequestForm[1].resourceSize = 41976;
		loadRequestForm[1].resourceStart = 0;
		loadRequestForm[1].surfaceLoadRequired = true;
		this->setupDone = true;
	}

	for (int a = 0; a < this->frameDataNum; ++a) {
		size_t* worldImageDataToBeUsedIndex;
		size_t worldImageDataToBeUsedIndexCurrentIndex = 0;
		if (this->frameData[a].canBeOverwritten) {
			this->frameData[a].framePrepared = false;
			worldImageDataToBeUsedIndex = new size_t[this->maxWorldImageDataNum];
			int previousImageNum = this->frameData[a].frameImageDataNum;
			//in a real program would only test those images which have moved, or if the camera has moved
			for (size_t b = 0; b < this->currentWorldImageDataNum; ++b) {
				//this will obviously need to be changed for non 2d views
				if (this->worldImageData[b].worldZoneX == this->camera.currentZoneX) {
					if (this->worldImageData[b].worldZoneY == this->camera.currentZoneY) {
						if ((this->worldImageData[b].worldX + this->worldImageData[b].worldWidth) >= this->camera.x) {
							if (this->worldImageData[b].worldX <= (this->camera.x + this->camera.cameraWidth)) {
								if ((this->worldImageData[b].worldY + this->worldImageData[b].worldHeight) >= this->camera.y) {
									if (this->worldImageData[b].worldY <= (this->camera.y + this->camera.cameraHeight)) {
										if (this->subTexture[this->worldImageData[b].subTextureIndex].textureReady == false)
											--this->frameData[a].frameImageDataNum;
										else {
											worldImageDataToBeUsedIndex[worldImageDataToBeUsedIndexCurrentIndex] = b;
											++worldImageDataToBeUsedIndexCurrentIndex;
										}
									}
								}
							}
						}
					}
				}
			}
			this->frameData[a].frameImageDataNum = worldImageDataToBeUsedIndexCurrentIndex;
			if (this->frameData[a].frameImageDataNum != previousImageNum) {
				delete[] this->frameData[a].frameImageData;
				if (this->frameData[a].frameImageDataNum != 0)
					this->frameData[a].frameImageData = new FrameImageData[this->frameData[a].frameImageDataNum];
			}
			for (size_t b = 0; b < this->frameData[a].frameImageDataNum; ++b) {
				this->frameData[a].frameImageData[b].frameX = this->worldImageData[worldImageDataToBeUsedIndex[b]].worldX - this->camera.x;
				this->frameData[a].frameImageData[b].frameY = this->worldImageData[worldImageDataToBeUsedIndex[b]].worldY - this->camera.y;
				this->frameData[a].frameImageData[b].frameWidth = this->worldImageData[worldImageDataToBeUsedIndex[b]].worldWidth;
				this->frameData[a].frameImageData[b].frameHeight = this->worldImageData[worldImageDataToBeUsedIndex[b]].worldHeight;
				this->frameData[a].frameImageData[b].worldImageDataIndex = worldImageDataToBeUsedIndex[b];
			}

			delete[] worldImageDataToBeUsedIndex;

			this->frameData[a].canBeOverwritten = false;
			this->frameData[a].framePrepared = true;

			break;
		}
	}

	//in multithreaded version maybe try an event array to make sure events aren't lost and to account for multiple button presses
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			this->runProgram = false;
	}
}

void Program::loadResources() {
	//in multithreaded version, pause this thread for a bit if nothing to do
	for (int a = 0; a < this->loadRequestFormNum; ++a) {
		if (this->loadRequestForm[a].surfaceLoadRequired) {
			for (int b = 0; b < this->surfaceNum; ++b) {
				if (this->surface[b] == nullptr) {
					this->loadRequestForm[a].surfaceIndex = b;
					break;
				}
			}
			this->createSurface(a);
			this->loadRequestForm[a].surfaceLoadRequired = false;
			this->loadRequestForm[a].textureLoadRequired = true;
		}
	}
}

void Program::render() { //multithreaded version has to check for program quitting
	int numTexturesCreated = 0;

	for (int a = 0; a < this->loadRequestFormNum && numTexturesCreated < 5; ++a) {
		if (this->loadRequestForm[a].textureLoadRequired) {
			for (int b = 0; b < this->textureNum; ++b) {
				if (this->texture[b] == nullptr) {
					this->loadRequestForm[a].textureIndex = b;
					break;
				}
			}
			this->createTexture(a);
			//ordinarily would check image ids against texture ids here, but too complicated for test
			//check to see which subtextures require this texture here in full program, implementing a request system
			this->subTexture[a].textureIndex = this->loadRequestForm[a].textureIndex;
			this->subTexture[a].textureReady = true;
			this->loadRequestForm[a].textureLoadRequired = false;
			this->loadRequestForm[a].canBeOverwritten = true;
			++numTexturesCreated;
		}
	}

	if (this->firstTimeRendering) { //in multithreaded version this would be a while loop with a wait
		if (this->frameData[this->currentRenderingFrame].framePrepared) {
			SDL_RenderClear(this->renderer);
			for (int a = 0; a < this->frameData[this->currentRenderingFrame].frameImageDataNum; ++a) {
				SDL_Rect imageData = { 
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameX, 
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameY, 
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameWidth , 
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameHeight 
				};
				SDL_Rect clipData = { 
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipX, 
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipY, 
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipWidth, 
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipHeight 
				};
				SDL_RenderCopy(this->renderer, this->texture[this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].textureIndex], &clipData, &imageData);
			}
			SDL_RenderPresent(this->renderer);
			this->firstTimeRendering = false;
		}
		else
			return; //wait in multithreaded version
	}
	else { //this would be a separate while loop in the multithreaded version, intended to run for the rest of the duration
		int newRenderingFrame = this->currentRenderingFrame + 1;
		if (newRenderingFrame >= this->frameDataNum)
			newRenderingFrame = 0;
		if (this->frameData[newRenderingFrame].framePrepared) {
			SDL_RenderClear(this->renderer);
			for (int a = 0; a < this->frameData[this->currentRenderingFrame].frameImageDataNum; ++a) {
				SDL_Rect imageData = {
					this->frameData[newRenderingFrame].frameImageData[a].frameX,
					this->frameData[newRenderingFrame].frameImageData[a].frameY,
					this->frameData[newRenderingFrame].frameImageData[a].frameWidth ,
					this->frameData[newRenderingFrame].frameImageData[a].frameHeight
				};
				SDL_Rect clipData = {
					this->subTexture[this->worldImageData[this->frameData[newRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipX,
					this->subTexture[this->worldImageData[this->frameData[newRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipY,
					this->subTexture[this->worldImageData[this->frameData[newRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipWidth,
					this->subTexture[this->worldImageData[this->frameData[newRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipHeight
				};
				SDL_RenderCopy(this->renderer, this->texture[this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].textureIndex], &clipData, &imageData);
			}
			SDL_RenderPresent(this->renderer);
			this->frameData[this->currentRenderingFrame].canBeOverwritten = true;
			this->currentRenderingFrame = newRenderingFrame;
		}
		else {
			SDL_RenderClear(this->renderer);
			for (int a = 0; a < this->frameData[this->currentRenderingFrame].frameImageDataNum; ++a) {
				SDL_Rect imageData = {
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameX,
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameY,
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameWidth ,
					this->frameData[this->currentRenderingFrame].frameImageData[a].frameHeight
				};
				SDL_Rect clipData = {
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipX,
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipY,
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipWidth,
					this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].clipHeight
				};
				SDL_RenderCopy(this->renderer, this->texture[this->subTexture[this->worldImageData[this->frameData[this->currentRenderingFrame].frameImageData[a].worldImageDataIndex].subTextureIndex].textureIndex], &clipData, &imageData);
			}
			SDL_RenderPresent(this->renderer);
		}
	}
}

void Program::run() {
	while (this->runProgram) {
		this->programCore();
		this->loadResources();
		this->render();
	}
}