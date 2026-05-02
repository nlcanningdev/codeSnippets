#include "dependencies/SDL2/include/SDL.h"
#include <iostream>

//always returns true when window is selected.  ie. alt tabbing doesn't change anything
//when you re-select the window input is grabbed again.  as you'd expect
//this behaviour should depend on the type of program, no user choice

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("test grab", 25, 25, 500, 500, SDL_WINDOW_INPUT_GRABBED);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	bool programRunning = true;
	SDL_Event event;
	while (programRunning) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				programRunning = false;
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_0) {
					if (SDL_GetWindowGrab(window) == true)
						std::cout << "window grabbed" << std::endl;
					else if (SDL_GetWindowGrab(window) == false)
						std::cout << "window not grabbed" << std::endl;
				}
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
