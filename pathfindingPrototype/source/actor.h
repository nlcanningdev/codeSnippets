#pragma once

#include <cstdint>

class Actor {
public:
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	void setCoordinates(float x, float y);
	float getWidth();
	float getHeight();
	void setDimensions(float width, float height);
	size_t getTextureIndex();
	void setTextureIndex(size_t textureIndex);
	float getMovementPerSecond();
	void setMovementPerSecond(float movementPerSecond);
	float getMaxMovementPerFramePositive();
	float getMaxMovementPerFrameNegative();
	float getHorizontalMovement();
	void setHorizontalMovement(float horizontalMovement);
	float getVerticalMovement();
	void setVerticalMovement(float verticalMovement);
private:
	float x;
	float y;
	float width;
	float height;
	size_t currentAreaIndex;
	size_t currentTileIndexX;
	size_t currentTileIndexY;
	size_t textureIndex;
	float movementPerSecond;
	float maxMovementPerFramePositive;
	float maxMovementPerFrameNegative;
	float horizontalMovement;
	float verticalMovement;
};