#include "font.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "charset.h"
#include "character.h"

void Font::setupFont(std::string* fontPath, SDL_Color* colour, int charsetNum, int* charSize) {
	this->charsetNum = charsetNum;
	charset = new Charset[this->charsetNum];
	for (int a = 0; a < this->charsetNum; ++a) {
		charset[a].charNum = 95;
		charset[a].charSize = charSize[a];
		charset[a].character = new Character[charset[a].charNum];
		TTF_Font* newFont;
		newFont = TTF_OpenFont(fontPath[a].c_str(), charset[a].charNum);
		for (int b = 0; b < charset[a].charNum; ++b) {
			SDL_Surface* surface;
			char letter[1];
			letter[0] = b + 32;
			surface = TTF_RenderText_Solid(newFont, letter, colour[a]);
			SDL_SetSurfaceAlphaMod(surface, 255);
			charset[a].character[b].width = surface->w;
			charset[a].character[b].height = surface->h;
			charset[a].character[b].pixels = new unsigned char[(surface->w * surface->h) * 4];
			int count = 0;
			Uint8 red, green, blue, alpha;
			SDL_LockSurface(surface);
			Uint8* p = (Uint8*)surface->pixels;
			for (int y = 0; y < surface->h; ++y) {
				for (int x = 0; x < surface->w; ++x) {
					Uint8 pixel = p[(y * surface->pitch) + x];
					SDL_GetRGBA(pixel, surface->format, &red, &green, &blue, &alpha);
					charset[a].character[b].pixels[count] = red;
					++count;
					charset[a].character[b].pixels[count] = green;
					++count;
					charset[a].character[b].pixels[count] = blue;
					++count;
					charset[a].character[b].pixels[count] = alpha;
					++count;
				}
			}
			SDL_UnlockSurface(surface);
			SDL_FreeSurface(surface);
		}
		TTF_CloseFont(newFont);
	}
}

SDL_Rect Font::getCharacterAttributes(int set, int charNum) {
	SDL_Rect attributes;
	attributes.w = charset[set].character[charNum].width;
	attributes.h = charset[set].character[charNum].height;
	return attributes;
}

void Font::closeFont() {
	for(int a = 0; a < charsetNum; ++a) {
		for(int b = 0; b < 95; ++b) {
			delete[] charset[a].character[b].pixels;
		}
		delete[] charset[a].character;
	}
	delete[] charset;
}