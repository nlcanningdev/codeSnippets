#pragma once

class Sprite {
private:
	int x, y, imageIndex, layer;
	bool display;
public:
	void setupSprite(int x, int y, int imageIndex, bool display, int layer);
	inline int getX() { return x; }
	inline void setX(int x) { this->x = x; }
	inline int getY() { return y; }
	inline void setY(int y) { this->y = y; }
	inline int getImageIndex() { return imageIndex; }
	inline void setImageIndex(int imageIndex) { this->imageIndex = imageIndex; }
	inline void setDisplay(bool display) { this->display = display; }
	inline bool getDisplay() { return display; }
	inline void setLayer(int layer) { this->layer = layer; }
	inline int getLayer() { return layer; }
};
