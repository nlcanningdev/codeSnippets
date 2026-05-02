#include "program.h"
#include <cstdint>
#include <fstream>
#include <atomic>
#include <chrono>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

Program::Program() : window(nullptr), renderer(nullptr), surface(nullptr), texture(nullptr) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	this->window = SDL_CreateWindow("test program", 100, 100, 1000, 1000, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	this->surfaceNum = 2;
	this->surface = new SDL_Surface*[this->surfaceNum];
	this->textureNum = 2;
	this->texture = new SDL_Texture*[this->textureNum];
	for (size_t a = 0; a < this->surfaceNum; ++a)
		this->surface[a] = nullptr;
	for (size_t a = 0; a < this->textureNum; ++a)
		this->texture[a] = nullptr;
	this->runProgram = true;
	this->runProgramFlag.clear();
}

Program::~Program() {
	if (this->surface != nullptr) {
		for (int a = 0; a < this->surfaceNum; ++a) {
			if (this->surface[a] != nullptr) {
				SDL_FreeSurface(this->surface[a]);
				this->surface[a] = nullptr;
			}
		}
		delete[] this->surface;
		this->surface = nullptr;
	}
	if (this->texture != nullptr) {
		for (int a = 0; a < this->textureNum; ++a) {
			if (this->texture[a] != nullptr) {
				SDL_DestroyTexture(this->texture[a]);
				this->texture[a] = nullptr;
			}
		}
		delete[] this->texture;
		this->texture = nullptr;
	}
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

void Program::runLoadingThread() {
	uint8_t* image = new uint8_t[40587];
	std::ifstream readFile;
	readFile.open("img0.png", std::ios::binary);
	readFile.read((char*)image, 40587);
	readFile.close();
	readFile.clear();
	SDL_RWops* rw = SDL_RWFromMem(image, 40587);
	this->surface[0] = IMG_Load_RW(rw, 0);
	SDL_RWclose(rw);
	delete[] image;
	image = new uint8_t[41976];
	readFile.open("img1.png", std::ios::binary);
	readFile.read((char*)image, 41976);
	readFile.close();
	readFile.clear();
	rw = SDL_RWFromMem(image, 41976);
	this->surface[1] = IMG_Load_RW(rw, 0);
	SDL_RWclose(rw);
	delete[] image;
}

void Program::runInputThread() {
	bool runThread = true;
	bool gotAccessToRunProgram = false;
	auto startTime = std::chrono::steady_clock::now();
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::microseconds duration(16667);
	bool timerInUse = false;
	char threadInput = '.';
	bool gotAccessToInput = false;
	while (runThread) {
		if (timerInUse == false) {
			threadInput = this->getInput(gotAccessToInput);
			if (gotAccessToInput && threadInput == '.') {
				timerInUse = true;
				startTime = std::chrono::steady_clock::now();
				currentTime = std::chrono::steady_clock::now();
				gotAccessToInput = false;
			}
			else if (threadInput == 'x')
				runThread = false;
		}
		else if (timerInUse == true) {
			currentTime = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed = currentTime - startTime;
			if (elapsed >= duration)
				timerInUse = false;
		}
	}
	while (!runThread && !gotAccessToRunProgram) {
		this->setRunProgram(gotAccessToRunProgram, runThread);
	}
}

void Program::runRenderingThread() {
	this->texture[0] = SDL_CreateTextureFromSurface(this->renderer, this->surface[0]);
	this->texture[1] = SDL_CreateTextureFromSurface(this->renderer, this->surface[1]);
	bool runThread = true;
	bool gotAccessToRunProgram = false;
	char inputThread = '.';
	bool gotAccessToInput = false;
	auto startTime = std::chrono::steady_clock::now();
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::microseconds duration(16667);
	bool timerInUse = false;
	SDL_Event event;
	while (runThread) {
		SDL_RenderClear(this->renderer);
		SDL_Rect imageData = {
			0, 0, 800, 800
		};
		SDL_Rect clipData = {
			0, 0, 800, 800
		};
		SDL_RenderCopy(this->renderer, this->texture[0], &clipData, &imageData);
		imageData = {
			200, 200, 500, 500
		};
		clipData = {
			0, 0, 500, 500
		};
		SDL_RenderCopy(this->renderer, this->texture[1], &clipData, &imageData);
		SDL_RenderPresent(this->renderer);

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_x)
					inputThread = 'x';
			}
		}

		if (inputThread == 'x') {
			this->setInput(gotAccessToInput, inputThread);
			if (gotAccessToInput) {
				inputThread = '.';
				gotAccessToInput = false;
			}
		}

		if (timerInUse == false) {
			runThread = this->getRunProgram(gotAccessToRunProgram);
			if (gotAccessToRunProgram && runThread) {
				timerInUse = true;
				startTime = std::chrono::steady_clock::now();
				currentTime = std::chrono::steady_clock::now();
				gotAccessToRunProgram = false;
			}
		}
		else if (timerInUse == true) {
			currentTime = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed = currentTime - startTime;
			if (elapsed >= duration)
				timerInUse = false;
		}
	}
}

bool Program::getRunProgram(bool& gotAccessToRunProgram) {
	bool returnValue = true;
	if (this->runProgramFlag.test_and_set(std::memory_order_acquire)) {
		gotAccessToRunProgram = true;
		returnValue = this->runProgram;
		this->runProgramFlag.clear(std::memory_order_release);
	}
	return returnValue;
}

void Program::setRunProgram(bool& gotAccessToRunProgram, bool runThread) {
	if (this->runProgramFlag.test_and_set(std::memory_order_acquire)) {
		gotAccessToRunProgram = true;
		this->runProgram = runThread;
		this->runProgramFlag.clear(std::memory_order_release);
	}
}

char Program::getInput(bool& gotAccessToInput) {
	char returnValue = '.';
	if (this->inputFlag.test_and_set(std::memory_order_acquire)) {
		gotAccessToInput = true;
		returnValue = this->input;
		this->inputFlag.clear(std::memory_order_release);
	}
	return returnValue;
}

void Program::setInput(bool& gotAccessToInput, char inputThread) {
	if (this->inputFlag.test_and_set(std::memory_order_acquire)) {
		gotAccessToInput = true;
		this->input = inputThread;
		this->inputFlag.clear(std::memory_order_release);
	}
}