#pragma once

#include "worldImageData.h"
#include <cstdint>

//this will be different in finished program, because it will have Actors
struct FrameImageData {
	FrameImageData() {}
	FrameImageData(int32_t frameX, int32_t frameY, uint32_t frameWidth, uint32_t frameHeight, size_t worldImageDataIndex) : frameX(frameX), frameY(frameY), frameWidth(frameWidth), frameHeight(frameHeight), worldImageDataIndex(worldImageDataIndex) {}
	void set(int32_t frameX, int32_t frameY, uint32_t frameWidth, uint32_t frameHeight, size_t worldImageDataIndex) {
		this->frameX = frameX;
		this->frameY = frameY;
		this->frameWidth = frameWidth;
		this->frameHeight = frameHeight;
		this->worldImageDataIndex = worldImageDataIndex;
	}
	int32_t frameX;
	int32_t frameY;
	uint32_t frameWidth;
	uint32_t frameHeight;
	size_t worldImageDataIndex;
};