#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <fstream>
#include <string>
#include <cstdint>
#include "texAttribute.h"
#include "shader.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
	std::string programName = "Testing.exe"; //change for every program created
	int screenWidth = 800; int screenHeight = 600;
	SDL_GLContext context;
  	SDL_Window* window;
	TexAttribute texAttribute;
	GLuint texture;
	uint8_t* screen = new uint8_t[screenWidth * screenHeight * 4];
	//temp code
	for(int a = 0; a < (screenWidth * screenHeight * 4); ++a) {
		screen[a] = 255;
	}
	//end temp code
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  	window = SDL_CreateWindow("nlcan launcher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	glewInit();
	SDL_GL_SetSwapInterval(1);
	TTF_Init();
	texAttribute.setupTexAttribute();
	Shader* shader = new Shader(getVertexSource(), getFragmentSource());
	shader->setupShader();
	//setup everything else here
	//make the launcher a scene with the sdk, and make it a ui element
	//have all x and y values set with percentages in the scene creator, instead of hard values, for scaling
	//have ui elements set in relation to parent ui elements.  ie. a button that is a child of a ui object can have text
	//as its child in turn.  also visible or invisible
	//make a class for all of these to inherit from since there are a lot of common variables
	//end other setup
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, screen);
	shader->uniformFunction();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	bool quit = false;
	SDL_Event event;
	while(!quit) {
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT)
				quit = true;
		}
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screenWidth, screenHeight, GL_RGBA, GL_UNSIGNED_BYTE, screen);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window);
	}
	displayNum = SDL_GetNumVideoDisplays();
	glDeleteTextures(1, &texture);
	delete[] screen;
	shader->shutdown();
	delete shader;
	texAttribute.shutdown();
	SDL_DestroyWindow(window);
	window = NULL;
	TTF_Quit();
	SDL_Quit();
	std::string fullPath = "";
	for (int a = 0; ; ++a) {
		if (argv[0][a] == '\0') {
			for (int b = a - 1; argv[0][b] != '/' && argv[0][b] != '\\'; --b) {
				fullPath.pop_back();
			}
			break;
		}
		else
			fullPath += argv[0][a];
	}
	fullPath += programName;
	LPCTSTR path = fullPath.c_str();
	std::string argument = "screenWidth screenHeight screenType"; //change this later of course
	LPCTSTR arg = argument.c_str();
	ShellExecute(NULL, "open", path, arg, NULL, SW_SHOWNORMAL);
	return 0;
}
