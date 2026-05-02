#pragma once

#include "frameData.h"
#include "loadRequestForm.h"
#include "subTexture.h"
#include "worldImageData.h"
#include "frameImageData.h"
#include "camera.h"
#include "worldData.h"
#include <SDL.h>
#include <cstddef>
#include <string>

class Program {
public:
	Program();
	~Program();
	void createSurface(int loadRequestFormIndex);
	void createTexture(int loadRequestFormIndex);
	void programCore();
	void render();
	void loadResources();
	void run(); //will not exist in multithreaded version
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int textureNum;
	int surfaceNum;
	SDL_Texture** texture;
	SDL_Surface** surface;
	Camera camera;
	WorldData worldData;
	int subTextureNum;
	SubTexture* subTexture;
	int currentWorldImageDataNum;
	int maxWorldImageDataNum;
	WorldImageData* worldImageData;
	FrameData* frameData;
	int frameDataNum;
	LoadRequestForm* loadRequestForm;
	int loadRequestFormNum;
	bool runProgram;
	bool setupDone; //only for testing
	int currentRenderingFrame;
	bool firstTimeRendering;
};