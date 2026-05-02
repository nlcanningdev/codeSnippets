#include "sprite.h"

void Sprite::setupSprite(int x, int y, int imageIndex, bool display, int layer) {
	this->x = x;
	this->y = y;
	this->imageIndex = imageIndex;
	this->display = display;
	this->layer = layer;
}
