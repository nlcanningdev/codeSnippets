#pragma once

#include "frameImageData.h"

struct FrameData {
	FrameData() : canBeOverwritten(true), framePrepared(false), frameImageData(nullptr), frameImageDataNum(0) {}
	~FrameData() {
		if (this->frameImageData != nullptr)
			delete[] this->frameImageData;
	}
	int frameImageDataNum;
	FrameImageData* frameImageData;
	bool canBeOverwritten;
	bool framePrepared;
};