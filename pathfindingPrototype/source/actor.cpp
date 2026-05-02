#include "actor.h"
#include <cstdint>

float Actor::getX() {
	return this->x;
}

void Actor::setX(float x) {
	this->x = x;
}

float Actor::getY() {
	return this->y;
}

void Actor::setY(float y) {
	this->y = y;
}

void Actor::setCoordinates(float x, float y) {
	this->x = x;
	this->y = y;
}

float Actor::getWidth() {
	return this->width;
}

float Actor::getHeight() {
	return this->height;
}

void Actor::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;
}

size_t Actor::getTextureIndex() {
	return this->textureIndex;
}

void Actor::setTextureIndex(size_t textureIndex) {
	this->textureIndex = textureIndex;
}

float Actor::getMovementPerSecond() {
	return this->movementPerSecond;
}

void Actor::setMovementPerSecond(float movementPerSecond) {
	this->movementPerSecond = movementPerSecond;
	this->maxMovementPerFramePositive = this->movementPerSecond / 30.0f;
	this->maxMovementPerFrameNegative = this->maxMovementPerFramePositive * -1.0f;
}

float Actor::getMaxMovementPerFramePositive() {
	return this->maxMovementPerFramePositive;
}

float Actor::getMaxMovementPerFrameNegative() {
	return this->maxMovementPerFrameNegative;
}

float Actor::getHorizontalMovement() {
	return this->horizontalMovement;
}

void Actor::setHorizontalMovement(float horizontalMovement) {
	this->horizontalMovement = horizontalMovement;
}

float Actor::getVerticalMovement() {
	return this->verticalMovement;
}

void Actor::setVerticalMovement(float verticalMovement) {
	this->verticalMovement = verticalMovement;
}