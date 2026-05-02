#pragma once

#include <SDL.h>
#include <cstdint>

//in full program, use values in program to create SubTextures instead of storing data for them all

struct SubTexture {
	float clipX;
	float clipY;
	float clipWidth;
	float clipHeight;
	bool textureReady;
	size_t textureIndex;
	int textureCategory; //use defines for this
	SDL_Texture* texturePointer;
};