#pragma once

#include "worldImageData.h"
#include <cstdint>

//this will be different in finished program, because it will have Actors
struct FrameImageData {
	FrameImageData() {}
	FrameImageData(uint32_t frameX, uint32_t frameY, uint32_t frameWidth, uint32_t frameHeight, size_t worldImageDataIndex) : frameX(frameX), frameY(frameY), frameWidth(frameWidth), frameHeight(frameHeight), worldImageDataIndex(worldImageDataIndex) {}
	void set(uint32_t frameX, uint32_t frameY, uint32_t frameWidth, uint32_t frameHeight, size_t worldImageDataIndex) {
		this->frameX = frameX;
		this->frameY = frameY;
		this->frameWidth = frameWidth;
		this->frameHeight = frameHeight;
		this->worldImageDataIndex = worldImageDataIndex;
	}
	uint32_t frameX;
	uint32_t frameY;
	uint32_t frameWidth;
	uint32_t frameHeight;
	size_t worldImageDataIndex;
};