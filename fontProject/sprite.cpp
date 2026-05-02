#include <math.h>
#include "sprite.h"

#define PI 3.14159265

void setupSprite(Sprite &sprite, int xo, int yo, int ang, bool rot, int lay) {
	sprite.angle = (double)ang;
	sprite.layer = lay;
	sprite.origin.x = xo;
	sprite.origin.y = yo;
	sprite.rotate = rot;
	//temp code, will get data from hard drive later and store image separately
	sprite.width = 800;
	sprite.height = 600;
	sprite.rgba = new float*[sprite.width * sprite.height];
	for (int a = 0; a < sprite.width; ++a) {
		sprite.rgba[a] = new float[4];
		for (int b = 0; b < 4; ) {
			sprite.rgba[a][b] = 0.5f;
			++b;
			sprite.rgba[a][b] = 0.7f;
			++b;
			sprite.rgba[a][b] = 0.1f;
			++b;
			sprite.rgba[a][b] = 1.0f;
		}
	}
	if (sprite.rotate) {
		sprite.positionSpan = (int)sqrt((sprite.width * sprite.width) + (sprite.height * sprite.height));
		sprite.rOrigin.x = sprite.width / 2; sprite.rOrigin.y = sprite.height / 2;
		sprite.position = new Point*[sprite.width];
		for (int a = 0; a < sprite.width; ++a) {
			sprite.position[a] = new Point[sprite.height];
		}
		sprite.positionOrigin.x = sprite.origin.x - ((sprite.positionSpan - sprite.width) / 2);
		sprite.positionOrigin.y = sprite.origin.y - ((sprite.positionSpan - sprite.height) / 2);
		//calculate rotated position of every pixel in rgba and place them in position
		rotateSprite(sprite);
	}
}

void rotateSprite(Sprite &sprite) {
	double sideA, sideB, sideC, angle;
	for (int a = 0; a < sprite.width; ++a) { //thru x axis of sprite
		for (int b = 0; b < sprite.height; ++b) { //thru y axis of sprite
			//get hypotenuse
			sideC = sqrt(((-sprite.rOrigin.x + a) * (-sprite.rOrigin.x + a)) + ((-sprite.rOrigin.y + b) * (-sprite.rOrigin.y + b)));
			//get angle of point from origin at centre of sprite
			angle = asin((-sprite.rOrigin.y + b) / sideC) * (180 / PI);
			if (angle < 0) { angle *= -1; } //block-start:make angle positive and <= 90
			if (a <= sprite.rOrigin.x) {
				if (b <= sprite.rOrigin.y)//sprite.angle modifies the original angle of the point
					angle -= sprite.angle;
				else if (b > sprite.rOrigin.y)
					angle += sprite.angle;
			}
			else if (a > sprite.rOrigin.x) {
				if (b <= sprite.rOrigin.y)
					angle += sprite.angle;
				else if (b > sprite.rOrigin.y)
					angle -= sprite.angle;
			}
			if (angle < 0) { angle *= -1; }
			if (angle > 90) { angle -= 90; }//block-end
			sideB = sideC * (sin(angle) * (180 / PI)); //get y of rotated point
			if (sideB < 0 && b > sprite.rOrigin.y)
				sideB *= -1;
			else if (sideB > 0 && b > sprite.rOrigin.y)
				sideB *= -1;
			sideA = sideC * (cos(angle) * (180 * PI)); //get x of rotated point
			sideB += (double)sprite.rOrigin.y;
			sideA += (double)sprite.rOrigin.x;
			sprite.position[a][b].x = ((int)sideA) + sprite.rOrigin.x;
			sprite.position[a][b].y = ((int)sideB) + sprite.rOrigin.y;
		}
	}
}
