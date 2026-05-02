#pragma once

#include <cstdint>

//in full program, use values in program to create SubTextures instead of storing data for them all

struct SubTexture {
	uint32_t clipX;
	uint32_t clipY;
	uint32_t clipWidth;
	uint32_t clipHeight;
	bool textureReady;
	size_t textureIndex;
};