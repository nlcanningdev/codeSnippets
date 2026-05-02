#pragma once

#include "twoDimensionalActorComponent.h"
#include "worldData.h"
#include <cstdint>

//developer and camera dimensions should always be width

class Sprite : public TwoDimensionalActorComponent {
public:
	Sprite(float dimensionDeveloperPixels, float dimensionCameraPixels, float xMetric, float yMetric, WorldData* worldData) : TwoDimensionalActorComponent(xMetric, yMetric, worldData) {
		this->setDimensionsScaled(dimensionDeveloperPixels, dimensionCameraPixels);
	}
	float getDimensionMetric() { return this->dimensionMetric; }
	float getDimensionPixels() { return this->dimensionPixels; }
	float getXPixelsRelativeToCamera(float cameraXMetric) {
		return (this->xMetric - cameraXMetric) * this->worldData->pixelsToOneMetre;
	}
	float getYPixelsRelativeToCamera(float cameraYMetric) {
		return (this->yMetric - cameraYMetric) * this->worldData->pixelsToOneMetre;
	}
	void setDimensionsScaled(float developerDimensionPixels, float cameraDimensionPixels) {
		this->dimensionPixels = developerDimensionPixels - (developerDimensionPixels * ((this->worldData->developerCameraWidthPixels - cameraDimensionPixels) / worldData->developerCameraWidthPixels));
		this->dimensionMetric = this->dimensionPixels / this->worldData->pixelsToOneMetre;
	}
private:
	float dimensionMetric;
	float dimensionPixels;
	size_t subtextureIndex;
};