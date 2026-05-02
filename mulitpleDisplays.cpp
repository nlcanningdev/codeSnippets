#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

struct SDL_Settings {
	bool fullscreen;
	bool vsync;
	int targetTimeBetweenFrames; //microseconds, ie. 1/1000th ofa  millisecond, which is 1/1000th of a second
	bool minimiseOnTab;
	bool limitFrameRate;
};

void writeError(std::string error) {
	std::ofstream writeFile("C:\\Users\\Nick\\source\\repos\\testEnvironment\\Debug\\debugFile.txt");
	writeFile << error;
	writeFile.close();
	writeFile.clear();
}

class FramesPerSecondCounter {
public:
	FramesPerSecondCounter(SDL_Renderer* renderer, int startX, int startY) {
		//this->rendererPointer = rendererPointer;
		this->texture = new SDL_Texture*[11];
		for (int a = 0; a < 11; ++a) {
			this->texture[a] = nullptr;
		}
		this->width = new int[11];
		this->height = new int[11];
		this->font = TTF_OpenFont("C:\\Users\\Nick\\source\\repos\\testEnvironment\\Debug\\Roboto-Black.ttf", 28);
		if (this->font == NULL)
			writeError("font not loaded!");
		this->startX = startX;
		this->startY = startY;
		this->setTexture(0, ".", renderer);
		this->setTexture(1, "0", renderer);
		this->setTexture(2, "1", renderer);
		this->setTexture(3, "2", renderer);
		this->setTexture(4, "3", renderer);
		this->setTexture(5, "4", renderer);
		this->setTexture(6, "5", renderer);
		this->setTexture(7, "6", renderer);
		this->setTexture(8, "7", renderer);
		this->setTexture(9, "8", renderer);
		this->setTexture(10, "9", renderer);
		this->firstFrameStart = std::chrono::steady_clock::now();
		this->text = nullptr;
		this->firstRenderDebug = true;
		this->countdownToRenderDebug = 1000;
	}
	~FramesPerSecondCounter() {
		delete[] this->texture;
		delete[] this->width;
		delete[] this->height;
		delete[] this->text;
	}

	void removeTextures() {
		for (int a = 0; a < 11; ++a) {
			if (this->texture[a] != nullptr /*&& this->rendererPointer != nullptr*/) {
				std::string error = "deleted texture #";
				error += std::to_string(a);
				//writeError(error);
				SDL_DestroyTexture(this->texture[a]);
			}
			else {
				std::string error = "texture #" + std::to_string(a) + " was invalid";
				writeError(error);
			}
		}
		TTF_CloseFont(this->font);
	}

	void setStartPosition(int startX, int startY) {
		this->startX = startX;
		this->startY = startY;
	}

	void renderText(SDL_Renderer* renderer, SDL_Settings& sdl_Settings) {
		std::chrono::steady_clock::time_point secondFrameStart = std::chrono::steady_clock::now();
		int time = (std::chrono::duration_cast<std::chrono::microseconds>(secondFrameStart - this->firstFrameStart)).count();
		int timeVsTarget = sdl_Settings.targetTimeBetweenFrames - time;
		if ((timeVsTarget > 0) && time > 0 && sdl_Settings.limitFrameRate) {
			std::this_thread::sleep_for(std::chrono::microseconds(timeVsTarget));
			time += timeVsTarget;
		}
		if (this->firstRenderDebug && this->countdownToRenderDebug == 0) {
			writeError(std::to_string(time));
			this->firstRenderDebug = false;
		}
		else if (this->countdownToRenderDebug > 0)
			--this->countdownToRenderDebug;
		float fps;
		if (time == 0)
			fps = 0.0f;
		else
			fps = 1000000.f / time;
		std::string textString = std::to_string(fps);
		if (this->text != nullptr)
			delete[] this->text;
		this->textSize = textString.length();
		this->text = new int[this->textSize];
		int* currentWidth = new int[this->textSize]{ 0 };
		int* currentHeight = new int[this->textSize]{ 0 };
		for (size_t a = 0; a < this->textSize; ++a) {
			switch (textString[a]) {
			case '.' :
				this->text[a] = 0;
				currentWidth[a] = this->width[0];
				currentHeight[a] = this->height[0];
				break;
			case '0' :
				this->text[a] = 1;
				currentWidth[a] = this->width[1];
				currentHeight[a] = this->height[1];
				break;
			case '1' :
				this->text[a] = 2;
				currentWidth[a] = this->width[2];
				currentHeight[a] = this->height[2];
				break;
			case '2' :
				this->text[a] = 3;
				currentWidth[a] = this->width[3];
				currentHeight[a] = this->height[3];
				break;
			case '3' :
				this->text[a] = 4;
				currentWidth[a] = this->width[4];
				currentHeight[a] = this->height[4];
				break;
			case '4':
				this->text[a] = 5;
				currentWidth[a] = this->width[5];
				currentHeight[a] = this->height[5];
				break;
			case '5':
				this->text[a] = 6;
				currentWidth[a] = this->width[6];
				currentHeight[a] = this->height[6];
				break;
			case '6':
				this->text[a] = 7;
				currentWidth[a] = this->width[7];
				currentHeight[a] = this->height[7];
				break;
			case '7':
				this->text[a] = 8;
				currentWidth[a] = this->width[8];
				currentHeight[a] = this->height[8];
				break;
			case '8':
				this->text[a] = 9;
				currentWidth[a] = this->width[9];
				currentHeight[a] = this->height[9];
				break;
			case '9':
				this->text[a] = 10;
				currentWidth[a] = this->width[10];
				currentHeight[a] = this->height[10];
				break;
			}
		}
		int currentStartX = this->startX;
		for (size_t a = 0; a < this->textSize; ++a) {
			SDL_Rect textureData = { currentStartX, this->startY, currentWidth[a], currentHeight[a] };
			if (SDL_RenderCopy(renderer, this->texture[this->text[a]], NULL, &textureData) == -1) {
				writeError("render error texture # " + a);
			}
			currentStartX += currentWidth[a];
		}
		this->firstFrameStart = secondFrameStart;
		delete[] currentWidth;
		delete[] currentHeight;
	}
protected:
	void setTexture(int textureIndex, const char* character, SDL_Renderer* renderer) {
		SDL_Surface* surface = TTF_RenderText_Solid(this->font, character, SDL_Color{125, 125, 125, 255});
		this->width[textureIndex] = surface->w;
		this->height[textureIndex] = surface->h;
		this->texture[textureIndex] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
private:
	std::chrono::steady_clock::time_point firstFrameStart;
	SDL_Texture** texture;
	int* text; //array pointing to the textures in the number, of size this->textSize
	int textSize;
	int* width;
	int* height;
	int startX;
	int startY;
	TTF_Font* font;
	SDL_Renderer* rendererPointer;
	bool firstRenderDebug;
	int countdownToRenderDebug;
};

int main(int argc, char** argv) {
	SDL_Settings sdl_Settings{ true, true, 33333, false, false };
	bool lostFocus = false;
	bool isMinimised = false;
	std::string error = "";
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		error += "SDL_Init failed";
		error += "\n";
		writeError(error);
		return 0;
	}
	else {
		error += "sDL_Init worked";
		error += "\n";
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		error += "SDL_setHint failed, no linear filtering.";
		error += "\n";
		writeError(error);
		return 0;
	}
	else {
		error += "SDL_SetHint worked.  linear filtering enabled";
		error += "\n";
	}
	int numDisplays = SDL_GetNumVideoDisplays();
	if(numDisplays > 1)
		SDL_SetHint("SDL_VIDEO_MINIMIZE_ON_FOCUS_LOSS", "0");
	int* displayWidth = new int[numDisplays];
	int* displayHeight = new int[numDisplays];
	int windowX = 0;
	int windowY = 0;
	int windowWidth = 0;
	int windowHeight = 0;
	for (int a = 0; a < numDisplays; ++a) {
		SDL_Rect bounds;
		SDL_GetDisplayBounds(a, &bounds);
		displayWidth[a] = bounds.w;
		displayHeight[a] = bounds.h;
		if(a == (numDisplays - 1)) {
			windowWidth = displayWidth[a];
			windowHeight = displayHeight[a];
			windowX = bounds.x;
		}
	}
	error += "windowX before being replaced by test value: ";
	error += std::to_string(windowX);
	error += "\n";
	error += "windowY before being replaced by test value: ";
	error += std::to_string(windowY);
	error += "\n";
	error += "windowWidth before being replaced by test value: ";
	error += std::to_string(windowWidth);
	error += "\n";
	error += "windowHeight before being replaced by test value: ";
	error += std::to_string(windowHeight);
	error += "\n";
	SDL_Window* window;
	//testing code follow
	/*windowX = 0;
	windowY = 0;
	windowWidth = 1000;
	windowHeight = 700;*/
	//end test code
	Uint32 windowFlags;
	if (sdl_Settings.fullscreen == true)
		windowFlags = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_INPUT_GRABBED;
	else if (sdl_Settings.fullscreen == false)
		windowFlags = SDL_WINDOW_INPUT_GRABBED;
	//window = SDL_CreateWindow("test environment", windowX, windowY, windowWidth, windowHeight, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_INPUT_GRABBED);
	window = SDL_CreateWindow("test environment", windowX, windowY, 800, 800, windowFlags);
	if (window == NULL) {
		error += "window is NULL";
		error += "\n";
		error += "numDisplays: ";
		error += std::to_string(numDisplays);
		error += "\n";
		writeError(error);
		return 0;
	}
	else {
		error += "window was successfully created";
		error += "\n";
		error += "numDisplays: ";
		error += std::to_string(numDisplays);
		error += "\n";
	}
	//SDL_SetWindowGrab(window, SDL_TRUE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		error += "renderer is NULL";
		error += "\n";
		writeError(error);
		return 0;
	}
	else {
		error += "renderer was successfully created";
		error += "\n";
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		error += "IMG_Init failed";
		error += "\n";
		writeError(error);
		return 0;
	}
	else {
		error += "IMG_Init succeeded";
		error += "\n";
	}
	if (TTF_Init() == -1) {
		error += "TTF_Init failed";
		error += "\n";
	}
	else {
		error += "TTF_Init succeeded";
		error += "\n";
	}
	writeError(error);
	SDL_Surface* surface = IMG_Load("C:\\Users\\Nick\\source\\repos\\testEnvironment\\Debug\\test0.png");
	SDL_Texture** texture = new SDL_Texture*[2];
	texture[0] = SDL_CreateTextureFromSurface(renderer, surface);
	int buttonX = 0;
	int buttonY = 0;
	int buttonWidth = 500;
	int buttonHeight = 500;
	SDL_FreeSurface(surface);
	surface = IMG_Load("C:\\Users\\Nick\\source\\repos\\testEnvironment\\Debug\\test1.png");
	texture[1] = SDL_CreateTextureFromSurface(renderer, surface);
	int image2X = 500;
	int image2Y = 10;
	int image2Width = 200;
	int image2Height = 200;
	SDL_FreeSurface(surface);
	FramesPerSecondCounter framesPerSecondCounter(renderer, 100, 100);
	bool quit = false;
	SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				if ((event.button.x >= buttonX && event.button.x < (buttonX + buttonWidth)) && (event.button.y >= buttonY && event.button.y < (buttonY + buttonHeight)))
					quit = true;
				else
					image2X += 5;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_w)
					image2X += 5;
				else if (event.key.keysym.sym == SDLK_s)
					image2X -= 5;
			}
			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST && lostFocus == false) {
					lostFocus = true;
					if (numDisplays == 1 && isMinimised == false && (sdl_Settings.fullscreen == true && numDisplays == 1)) {
						SDL_MinimizeWindow(window);
						isMinimised = true;
					}
				}
				else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED && lostFocus == true) {
					if (isMinimised == true) {
						isMinimised = false;
					}
					lostFocus = false;
				}
				else if (event.type == SDL_WINDOWEVENT_MINIMIZED) {
					lostFocus = true;
					isMinimised = true;
				}
			}
		}
		if (!isMinimised) {
			SDL_RenderClear(renderer);
			SDL_Rect textureData = { buttonX, buttonY, buttonWidth, buttonHeight };
			SDL_RenderCopy(renderer, texture[0], NULL, &textureData);
			textureData = { image2X, image2Y, image2Width, image2Height };
			SDL_RenderCopy(renderer, texture[1], NULL, &textureData);
			framesPerSecondCounter.renderText(renderer, sdl_Settings);
			SDL_RenderPresent(renderer);
		}
	}
	delete[] displayWidth;
	delete[] displayHeight;
	SDL_DestroyTexture(texture[0]);
	SDL_DestroyTexture(texture[1]);
	delete[] texture;
	framesPerSecondCounter.removeTextures();
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	//writeError("made it to the end!");
	return 0;
}