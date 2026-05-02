#pragma once

#include <cstdint>
#include <atomic>
#include <SDL.h>
#include <SDL_image.h>

class Program {
public:
	Program();
	~Program();
	void runLoadingThread();
	void runInputThread();
	void runRenderingThread();
	bool getRunProgram(bool& gotAccessToRunProgram);
	void setRunProgram(bool& gotAcessToRunProgram, bool runThread);
	char getInput(bool& gotAccessToInput);
	void setInput(bool& gotAccessToInput, char inputThread);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface** surface;
	size_t surfaceNum;
	SDL_Texture** texture;
	size_t textureNum;
	bool runProgram;
	std::atomic_flag runProgramFlag;
	char input;
	std::atomic_flag inputFlag;
};