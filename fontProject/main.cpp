#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include "overhead.h"
#include "texAttribute.h"
#include "shader.h"
#include "texture.h"
#include <iostream>


int main(int argc, char* args[]) {
	Overhead overhead;
	setupOverhead(overhead);
	TTF_Init();
	TexAttribute texAttribute;
	setupTexAttribute(texAttribute);
	Shader shader(getVertexSource(), getFragmentSource());
	setupShader(shader);
	TTF_Font *font;
	char* letter = new char[1];
	letter[0] = 97;
	font = TTF_OpenFont("VarianeScript.ttf", 50);
	SDL_Surface* surface;
	SDL_Color color = { 255, 0, 0 };
	surface = TTF_RenderText_Solid(font, letter, color);
	SDL_SetSurfaceAlphaMod(surface, 255);
	int surfaceWidth = surface->w;
	int surfaceHeight = surface->h;
	Uint8 red, green, blue, alpha;
	unsigned char* textImage = new unsigned char[(surfaceWidth * surfaceHeight) * 4];
	int countText = 0;
	SDL_LockSurface(surface);
	Uint8* p = (Uint8*)surface->pixels;
	for (int y = 0; y < surfaceHeight; ++y) {
		for (int x = 0; x < (surfaceWidth); ++x) {
			Uint8 pixel = p[y * surface->pitch + x];
			SDL_GetRGBA(pixel, surface->format, &red, &green, &blue, &alpha);
			textImage[countText] = red;
			++countText;
			textImage[countText] = green;
			++countText;
			textImage[countText] = blue;
			++countText;
			textImage[countText] = alpha;
			++countText;
		}
	}
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
	GLuint texture;
	unsigned char* image;
	int width = 1000, height = 1000;
	int textX = width - (int)(width / 1.5);
	int textY = height - (int)(height / 1.5);
	//use new setupTexture function
	setupTexture(texture, shader, width, height, image, textImage, textX, textY, surfaceWidth, surfaceHeight);
	//setupTexture(texture, shader, width, height, image);
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//updateTexture(texture, shader, width, height, image);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(overhead.window);
	}
	delete[] image;
	delete[] letter;
	TTF_CloseFont(font);
	TTF_Quit();
	shutdown(overhead, texture, shader, texAttribute);
	return 0;
}
