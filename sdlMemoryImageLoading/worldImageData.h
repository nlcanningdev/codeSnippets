#pragma once

#include <cstdint>

struct WorldImageData {
	size_t subTextureIndex;
	size_t worldZoneX;
	size_t worldZoneY;
	size_t worldX;
	size_t worldY;
	uint32_t worldWidth;
	uint32_t worldHeight;
	//consider adding stuff like reference counting for images etc. that are intended to be temporary
};