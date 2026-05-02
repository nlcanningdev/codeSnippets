#include "x64event.h"
#include <SDL.h>
#include "network.h"

void event(Network &network, int &playerVelocity, int &aiVelocity, char &input, bool &game) {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			game = false;
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				if (network.getHost() == 'y') {
					if (playerVelocity == 0)
						playerVelocity = -30;
				}
				else {
					if (aiVelocity == 0)
						aiVelocity = -30;
				}
				break;
			case SDLK_s:
				if (network.getHost() == 'y') {
					if (playerVelocity == 0)
						playerVelocity = 30;
				}
				else {
					if (aiVelocity == 0)
						aiVelocity = 30;
				}
				break;
			case SDLK_y:
				input = 'y';
				break;
			case SDLK_n:
				input = 'n';
				break;
			}
		}
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				if (network.getHost() == 'y') {
					if (playerVelocity == -30)
						playerVelocity = 0;
				}
				else {
					if (aiVelocity == -30)
						aiVelocity = 0;
				}
				break;
			case SDLK_s:
				if (network.getHost() == 'y') {
					if (playerVelocity == 30)
						playerVelocity = 0;
				}
				else {
					if (aiVelocity == 30)
						aiVelocity = 0;
				}
				break;
			}
		}
	}
}