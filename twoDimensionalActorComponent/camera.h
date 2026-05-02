#pragma once

#include "twoDimensionalActorComponent.h"
#include "worldData.h"
#include <cstdint>

class Camera : public TwoDimensionalActorComponent {
public:
	Camera(float widthPixels, float heightResolutionPixels, float widthDeveloperPixels, float heightDeveloperPixels, float xMetric, float yMetric, WorldData* worldData) : TwoDimensionalActorComponent(xMetric, yMetric, worldData) {
		this->setDimensions(widthPixels, heightResolutionPixels, widthDeveloperPixels, heightDeveloperPixels)
	}
	void setDimensions(float widthPixels, float heightResolutionPixels, float widthDeveloperPixels, float heightDeveloperPixels) {
		this->widthPixels = widthPixels;
		this->heightPixels = heightResolutionPixels * (heightDeveloperPixels / widthDeveloperPixels);
		this->widthMetric = this->widthPixels / this->worldData->pixelsToOneMetre;
		this->heightMetric = this->heightPixels / this->worldData->pixelsToOneMetre;
	}
	float getWidthMetric() { return this->widthMetric; }
	float getHeightMetric() { return this->heightMetric; }
	float getWidthPixels() { return this->widthPixels; }
	float getHeightPixels() { return this->heightPixels; }
private:
	float widthMetric;
	float heightMetric;
	float widthPixels;
	float heightPixels;
};