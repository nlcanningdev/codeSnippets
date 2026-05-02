#pragma once

#include <cstdint>

//developer means the original resolution used to create the program

struct WorldData {
	float widthMetric;
	float heightMetric;
	float pixelsToOneMetre;
	float developerCameraWidthPixels;
	float developerCameraHeightPixels;
};