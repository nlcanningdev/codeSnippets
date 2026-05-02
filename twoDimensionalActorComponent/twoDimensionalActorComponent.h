#pragma once

#include "worldData.h"

//create a child class for sprites
//require all textures to be square and power of 2, and all sprites
//there is no need for a setCoordinatesScaled function because that only requires metric, except for rendering
//maybe put the relative functions and the scaled function into sprite child class
//separate child class for camera because it knows its new width already
//also remove stuff for dimensions, since those work differently for both

class TwoDimensionalActorComponent {
public:
	TwoDimensionalActorComponent(float xMetric, float yMetric, WorldData* worldData) {
		this->worldData = worldData;
		this->setCoordinatesMetric(xMetric, yMetric);
	}
	float getXMetric() { return this->xMetric; }
	float getYMetric() { return this->yMetric; }
	void setXMetric(float xMetric) { this->xMetric = xMetric; }
	void setYMetric(float yMetric) { this->yMetric = yMetric; }
	void setCoordinatesMetric(float xMetric, float yMetric) {
		this->setXMetric(xMetric);
		this->setYMetric(yMetric);
	}
protected:
	float xMetric;
	float yMetric;
	WorldData* worldData;
};