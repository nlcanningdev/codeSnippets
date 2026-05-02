#include "program.h"
#include "inputState.h"
#include "pathfindingData.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cstdint>
#include <fstream>
#include <chrono>

Program::Program() : pathfindingData(256) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	this->window = SDL_CreateWindow("pathfinding prototype", 100, 100, 1600, 960, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);

	this->backgroundNum = 1600;
	this->background = new Actor[this->backgroundNum];
	this->obstacleNum = 250; //156 edge tiles
	this->obstacle = new Actor[this->obstacleNum];
	this->characterNum = 2;
	this->character = new Actor[this->characterNum];
	this->textureNum = 4;
	this->texture = new SDL_Texture*[this->textureNum];

	std::string file[4] = { "background.png", "obstacle.png", "character0.png", "character1.png" };
	SDL_Surface* surface;
	uint8_t* image;
	std::ifstream readFile;

	for (size_t a = 0; a < this->textureNum; ++a) {
		readFile.open(file[a].c_str(), std::ios::binary | std::ios::ate);
		size_t imageSize = readFile.tellg();
		image = new uint8_t[imageSize];
		readFile.seekg(0);
		readFile.read((char*)image, imageSize);
		readFile.close();
		readFile.clear();
		SDL_RWops* rw = SDL_RWFromMem(image, imageSize);
		surface = IMG_Load_RW(rw, 0);
		SDL_RWclose(rw);
		delete[] image;
		this->texture[a] = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	float backgroundX = 0.0f;
	float backgroundY = 0.0f;

	for (size_t a = 0; a < this->backgroundNum; ++a) {
		this->background[a].setDimensions(64.0f, 64.0f);
		this->background[a].setTextureIndex(0);
		this->background[a].setCoordinates(backgroundX, backgroundY);
		backgroundX += 64.0f;
		if (backgroundX == 2560.0f) {
			backgroundX = 0.0f;
			backgroundY += 64.0f;
		}
	}

	float obstacleCoordinates[250][2] = {
		{128.0f, 448.0f},
		{128.0f, 512.0f},
		{128.0f, 576.0f},
		{192.0f, 576.0f},
		{256.0f, 576.0f}, //5
		{256.0f, 128.0f},
		{512.0f, 640.0f},
		{576.0f, 640.0f},
		{640.0f, 640.0f},
		{128.0f, 64.0f}, //10
		{192.0f, 64.0f},
		{256.0f, 65.0f},
		{960.0f, 64.0f},
		{960.0f, 512.0f},
		{960.0f, 128.0f}, //15
		{960.0f, 256.0f},
		{960.0f, 320.0f},
		{960.0f, 448.0f},
		{960.0f, 512.0f},
		{960.0f, 576.0f}, //20
		{960.0f, 640.0f},
		{64.0f, 896.0f},
		{128.0f, 896.0f},
		{192.0f, 896.0f},
		{256.0f, 896.0f}, //25
		{1216.0f, 256.0f},
		{1216.0f, 320.0f},
		{1216.0f, 384.0f},
		{1216.0f, 448.0f},
		{1216.0f, 512.0f}, //30
		{1344.0f, 128.0f},
		{1344.0f, 192.0f},
		{1344.0f, 256.0f},
		{1344.0f, 320.0f},
		{1344.0f, 384.0f}, //35
		{128.0f, 1344.0f},
		{192.0f, 1344.0f},
		{256.0f, 1344.0f},
		{320.0f, 1344.0f},
		{384.0f, 1344.0f}, //40
		{1664.0f, 1792.0f},
		{1728.0f, 1792.0f},
		{1792.0f, 1792.0f},
		{1856.0f, 1792.0f},
		{1920.0f, 1792.0f}, //45
		{1792.0f, 1664.0f},
		{1792.0f, 1728.0f},
		{1792.0f, 1792.0f},
		{1792.0f, 1856.0f},
		{1792.0f, 1920.0f}, //50
		{1920.0f, 128.0f},
		{1920.0f, 192.0f},
		{1920.0f, 256.0f},
		{1920.0f, 320.0f},
		{1920.0f, 384.0f}, //55
		{128.0f, 1920.0f},
		{192.0f, 1920.0f},
		{256.0f, 1920.0f},
		{320.0f, 1920.0f},
		{384.0f, 1920.0f}, //60
		{2048.0f, 640.0f},
		{2048.0f, 704.0f},
		{2048.0f, 768.0f},
		{2048.0f, 832.0f},
		{2048.0f, 896.0f}, //65
		{640.0f, 2048.0f},
		{704.0f, 2048.0f},
		{768.0f, 2048.0f},
		{832.0f, 2048.0f},
		{896.0f, 2048.0f}, //70
		{960.0f, 1920.0f},
		{1024.0f, 1920.0f},
		{1088.0f, 1920.0f},
		{1152.0f, 1920.0f},
		{1216.0f, 1920.0f}, //75
		{1920.0f, 960.0f},
		{1920.0f, 1024.0f},
		{1920.0f, 1088.0f},
		{1920.0f, 1152.0f},
		{1920.0f, 1216.0f}, //80
		{1984.0f, 1920.0f},
		{2048.0f, 1920.0f},
		{2112.0f, 1920.0f},
		{2176.0f, 1920.0f},
		{2240.0f, 1920.0f}, //85
		{1920.0f, 1984.0f},
		{1920.0f, 2048.0f},
		{1920.0f, 2112.0f},
		{1920.0f, 2176.0f},
		{1920.0f, 2240.0f}, //90
		{2248.0f, 64.0f},
		{2248.0f, 128.0f},
		{2248.0f, 192.0f},
		{2248.0f, 256.0f}, //94
		{0.0f, 0.0f},
		{64.0f, 0.0f},
		{128.0f, 0.0f},
		{192.0f, 0.0f},
		{256.0f, 0.0f},
		{320.0f, 0.0f},
		{384.0f, 0.0f},
		{448.0f, 0.0f},
		{512.0f, 0.0f},
		{576.0f, 0.0f},
		{640.0f, 0.0f},
		{704.0f, 0.0f},
		{768.0f, 0.0f},
		{832.0f, 0.0f},
		{896.0f, 0.0f},
		{960.0f, 0.0f},
		{1024.0f, 0.0f},
		{1088.0f, 0.0f},
		{1152.0f, 0.0f},
		{1216.0f, 0.0f},
		{1280.0f, 0.0f},
		{1344.0f, 0.0f},
		{1408.0f, 0.0f},
		{1472.0f, 0.0f},
		{1536.0f, 0.0f},
		{1600.0f, 0.0f},
		{1664.0f, 0.0f},
		{1728.0f, 0.0f},
		{1792.0f, 0.0f},
		{1856.0f, 0.0f},
		{1920.0f, 0.0f},
		{1984.0f, 0.0f},
		{2048.0f, 0.0f},
		{2112.0f, 0.0f},
		{2176.0f, 0.0f},
		{2240.0f, 0.0f},
		{2304.0f, 0.0f},
		{2368.0f, 0.0f},
		{2432.0f, 0.0f},
		{2496.0f, 0.0f},
		{2496.0f, 64.0f},
		{2496.0f, 128.0f},
		{2496.0f, 192.0f},
		{2496.0f, 256.0f},
		{2496.0f, 320.0f},
		{2496.0f, 384.0f},
		{2496.0f, 448.0f},
		{2496.0f, 512.0f},
		{2496.0f, 576.0f},
		{2496.0f, 640.0f},
		{ 2496.0f, 704.0f },
		{ 2496.0f, 768.0f },
		{ 2496.0f, 832.0f },
		{ 2496.0f, 896.0f },
		{ 2496.0f, 960.0f },
		{ 2496.0f, 1024.0f },
		{ 2496.0f, 1088.0f },
		{ 2496.0f, 1152.0f },
		{ 2496.0f, 1216.0f },
		{ 2496.0f, 1280.0f },
		{ 2496.0f, 1344.0f },
		{ 2496.0f, 1408.0f },
		{ 2496.0f, 1472.0f },
		{ 2496.0f, 1536.0f },
		{ 2496.0f, 1600.0f },
		{ 2496.0f, 1664.0f },
		{ 2496.0f, 1728.0f },
		{ 2496.0f, 1792.0f },
		{ 2496.0f, 1856.0f },
		{ 2496.0f, 1920.0f },
		{ 2496.0f, 1984.0f },
		{ 2496.0f, 2048.0f },
		{ 2496.0f, 2112.0f },
		{ 2496.0f, 2176.0f },
		{ 2496.0f, 2240.0f },
		{ 2496.0f, 2304.0f },
		{ 2496.0f, 2368.0f },
		{ 2496.0f, 2432.0f },
		{ 2496.0f, 2496.0f },
		{ 2432.0f, 2496.0f },
		{ 2368.0f, 2496.0f },
		{ 2304.0f, 2496.0f },
		{ 2240.0f, 2496.0f },
		{ 2176.0f, 2496.0f },
		{ 2112.0f, 2496.0f },
		{ 2048.0f, 2496.0f },
		{ 1984.0f, 2496.0f },
		{ 1920.0f, 2496.0f },
		{ 1856.0f, 2496.0f },
		{ 1792.0f, 2496.0f },
		{ 1728.0f, 2496.0f },
		{ 1664.0f, 2496.0f },
		{ 1600.0f, 2496.0f },
		{ 1536.0f, 2496.0f },
		{ 1472.0f, 2496.0f },
		{ 1408.0f, 2496.0f },
		{ 1344.0f, 2496.0f },
		{ 1280.0f, 2496.0f },
		{ 1216.0f, 2496.0f },
		{ 1152.0f, 2496.0f },
		{ 1088.0f, 2496.0f },
		{ 1024.0f, 2496.0f },
		{ 960.0f, 2496.0f },
		{ 896.0f, 2496.0f },
		{ 832.0f, 2496.0f },
		{ 768.0f, 2496.0f },
		{ 704.0f, 2496.0f },
		{ 640.0f, 2496.0f },
		{ 576.0f, 2496.0f },
		{ 512.0f, 2496.0f },
		{ 448.0f, 2496.0f },
		{ 384.0f, 2496.0f },
		{ 320.0f, 2496.0f },
		{ 256.0f, 2496.0f },
		{ 192.0f, 2496.0f },
		{ 128.0f, 2496.0f },
		{ 64.0f, 2496.0f },
		{ 0.0f, 2496.0f },
		{ 0.0f, 2432.0f },
		{ 0.0f, 2378.0f },
		{ 0.0f, 2304.0f },
		{ 0.0f, 2240.0f },
		{ 0.0f, 2176.0f },
		{ 0.0f, 2112.0f },
		{ 0.0f, 2048.0f },
		{ 0.0f, 1984.0f },
		{ 0.0f, 1920.0f },
		{ 0.0f, 1856.0f },
		{ 0.0f, 1892.0f },
		{ 0.0f, 1728.0f },
		{ 0.0f, 1664.0f },
		{ 0.0f, 1600.0f },
		{ 0.0f, 1536.0f },
		{ 0.0f, 1472.0f },
		{ 0.0f, 1408.0f },
		{ 0.0f, 1344.0f },
		{ 0.0f, 1280.0f },
		{ 0.0f, 1216.0f },
		{ 0.0f, 1152.0f },
		{ 0.0f, 1088.0f },
		{ 0.0f, 1024.0f },
		{ 0.0f, 960.0f },
		{ 0.0f, 896.0f },
		{ 0.0f, 832.0f },
		{ 0.0f, 768.0f },
		{ 0.0f, 704.0f },
		{ 0.0f, 640.0f },
		{ 0.0f, 576.0f },
		{ 0.0f, 512.0f },
		{ 0.0f, 448.0f },
		{ 0.0f, 384.0f },
		{ 0.0f, 320.0f },
		{ 0.0f, 256.0f },
		{ 0.0f, 192.0f },
		{ 0.0f, 128.0f },
		{ 0.0f, 64.0f },
	};

	for (size_t a = 0; a < this->obstacleNum; ++a) {
		this->obstacle[a].setCoordinates(obstacleCoordinates[a][0], obstacleCoordinates[a][1]);
		this->obstacle[a].setDimensions(64.0f, 64.0f);
		this->obstacle[a].setTextureIndex(1);
	}

	this->character[0].setCoordinates(0.0f, 0.0f);
	this->character[0].setTextureIndex(2);
	this->character[1].setCoordinates(1536.0f, 896.0f);
	this->character[1].setTextureIndex(3);

	for (size_t a = 0; a < this->characterNum; ++a) {
		this->character[a].setDimensions(64.0f, 64.0f);
	}

	this->character[0].setMovementPerSecond(256.0f);

	this->runProgram = true;
}

Program::~Program() {
	delete[] this->background;
	delete[] this->obstacle;
	delete[] this->character;

	for (size_t a = 0; a < this->textureNum; ++a) {
		SDL_DestroyTexture(this->texture[a]);
	}
	delete[] this->texture;

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

void Program::run() {
	SDL_Event event;
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	while (this->runProgram) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_w) {
					this->inputState.w = true;
					this->inputState.s = false;
				}
				else if (event.key.keysym.sym == SDLK_a) {
					this->inputState.a = true;
					this->inputState.d = false;
				}
				else if (event.key.keysym.sym == SDLK_s) {
					this->inputState.s = true;
					this->inputState.w = false;
				}
				else if (event.key.keysym.sym == SDLK_d) {
					this->inputState.d = true;
					this->inputState.a = false;
				}
				else if (event.key.keysym.sym == SDLK_x && this->pathfindingData.getPathComplete())
					this->plotAIPath(this->character[0].getX(), this->character[0].getY());
			}
			else if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_w)
					this->inputState.w = false;
				else if (event.key.keysym.sym == SDLK_a)
					this->inputState.a = false;
				else if (event.key.keysym.sym == SDLK_s)
					this->inputState.s = false;
				else if (event.key.keysym.sym == SDLK_d)
					this->inputState.d = false;
			}
			if (event.type == SDL_QUIT)
				this->runProgram = false;
		}
		currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> durationElapsed = currentTime - startTime;
		float timeElapsed = durationElapsed.count();
		startTime = std::chrono::steady_clock::now();

		if (inputState.a || inputState.d) {
			if (inputState.d)
				this->character[0].setHorizontalMovement(this->character[0].getMovementPerSecond() * timeElapsed);
			else if (inputState.a)
				this->character[0].setHorizontalMovement((this->character[0].getMovementPerSecond() * timeElapsed) * -1.0f);
		}
		else if (this->character[0].getHorizontalMovement() != 0.0f) {
			this->character[0].setHorizontalMovement(0.0f);
		}
		if (inputState.w || inputState.d) {
			if(inputState.s)
				this->character[0].setVerticalMovement(this->character[0].getMovementPerSecond() * timeElapsed);
			else if (inputState.w)
				this->character[0].setVerticalMovement((this->character[0].getMovementPerSecond() * timeElapsed) * -1.0f);
		}
		this->moveUser(0);

		if (this->pathfindingData.getPathComplete() == false)
			this->moveAI(timeElapsed);

		SDL_RenderClear(this->renderer);
		for (size_t a = 0; a < this->backgroundNum; ++a) {
			SDL_Rect clipData = { 0, 0, 64, 64 };
			SDL_FRect drawData = {
				this->background[a].getX(),
				this->background[a].getY(),
				this->background[a].getWidth(),
				this->background[a].getHeight()
			};
			SDL_RenderCopyF(this->renderer, this->texture[background[a].getTextureIndex()], &clipData, &drawData);
		}
		for (size_t a = 0; a < this->obstacleNum; ++a) {
			SDL_Rect clipData = { 0, 0, 64, 64 };
			SDL_FRect drawData = {
				this->obstacle[a].getX(),
				this->obstacle[a].getY(),
				this->obstacle[a].getWidth(),
				this->obstacle[a].getHeight()
			};
			SDL_RenderCopyF(this->renderer, this->texture[obstacle[a].getTextureIndex()], &clipData, &drawData);
		}
		for (size_t a = 0; a < this->characterNum; ++a) {
			SDL_Rect clipData = { 0, 0, 64, 64 };
			SDL_FRect drawData = {
				this->character[a].getX(),
				this->character[a].getY(),
				this->character[a].getWidth(),
				this->character[a].getHeight()
			};
			SDL_RenderCopyF(this->renderer, this->texture[character[a].getTextureIndex()], &clipData, &drawData);
		}
		SDL_RenderPresent(this->renderer);
	}
}

void Program::moveUser(size_t characterIndex) {
	if (vertical > 0) {
		if (vertical > this->character[0].getMaxMovementPerFramePositive())
			vertical = this->maxMovementPerFramePositive;
	}
	else if (vertical < 0) {
		if (vertical < this->maxMovementPerFrameNegative)
			vertical = this->maxMovementPerFrameNegative;
	}
	if (vertical > 0) {
		if (vertical > this->maxMovementPerFramePositive)
			vertical = this->maxMovementPerFramePositive;
	}
	else if (vertical < 0) {
		if (vertical < this->maxMovementPerFrameNegative)
			vertical = this->maxMovementPerFrameNegative;
	}
	for (size_t a = 0; a < this->obstacleNum; ++a) {

	}
	
	
	/*
	size_t** collisionOrderIndex[8][8];

	size_t currentCollisionSet = 0;

	first index represents order of collision, second is the index of the objects
	*/

	float positiveHorizontal;
	float positiveVertical;

	if (horizontal < 0.0f)
		positiveHorizontal = horizontal * -1.0f;
	else
		positiveHorizontal = horizontal;
	if (vertical < 0.0f)
		positiveVertical = vertical * -1.0f;
	else
		positiveVertical = vertical;

	if (positiveVertical > (this->movementPerSecond / 30.0f)) {
		positiveVertical = this->movementPerSecond / 30.0f;
		if (vertical < 0)
			vertical = positiveVertical * -1;
		else
			vertical = positiveVertical;
	}
	if (horizontal > (this->movementPerSecond / 30.0f)) {
		positiveHorizontal = this->movementPerSecond / 30.0f;
		if (horizontal < 0)
			horizontal = positiveHorizontal * -1;
		else
			horizontal = positiveHorizontal;
	}

	float tempX = this->character[0].getX() + horizontal;
	float tempY = this->character[0].getY() + vertical;

	float characterX = this->character[0].getX();
	float characterY = this->character[0].getY();
	float characterWidth = this->character[0].getWidth();
	float characterHeight = this->character[0].getHeight();

	if (horizontal != 0 && vertical != 0) {
		this->collisionCandidatesCurrentNum = 0;

		bool worldCollision[4] = { false, false, false, false }; //left, up, right, down

		for (size_t a = 0; a < this->obstacleNum; ++a) {
			if (
				((this->obstacle[a].getX() + this->obstacle[a].getWidth()) >= (characterX - positiveHorizontal))
				&&
				((this->obstacle[a].getX()) <= (characterX + characterWidth + positiveHorizontal))
				&&
				((this->obstacle[a].getY() + this->obstacle[a].getHeight()) >= (characterY - positiveVertical))
				&&
				((this->obstacle[a].getY()) <= (characterY + characterHeight + positiveVertical))
				) {
				this->collisionCandidates[this->collisionCandidatesCurrentNum] = &obstacle[a];
				this->collisionCandidatesCurrentNum += 1;
			}
		}

		if ((characterX - positiveHorizontal) <= 0)
			worldCollision[0] = true;
		if ((characterX + characterWidth + positiveHorizontal) >= 1600)
			worldCollision[2] = true;
		if ((characterY - positiveVertical) <= 0)
			worldCollision[1] = true;
		if ((characterY + characterHeight + positiveVertical) >= 960)
			worldCollision[3] = true;

		size_t** collisionOrderIndex[8][8];
		size_t collisionOrderNum[8] = { 0,0,0,0,0,0,0,0 };
		size_t currentCollisionSet = 0;

		for (size_t a = 0; a < this->collisionCandidatesCurrentNum; ++a) {

		}
	}

	if ((this->character[0].getX() + horizontal) < 0)
		tempX = 0.0f;
	else if ((this->character[0].getX() + this->character[0].getWidth() + horizontal) > 1600)
		tempX = 1600.0f - this->character[0].getWidth();
	if ((this->character[0].getY() + vertical) < 0)
		tempY = 0.0f;
	else if ((this->character[0].getY() + this->character[0].getHeight() + vertical) > 960)
		tempY = 960.0f - this->character[0].getHeight();
	this->character[0].setCoordinates(tempX, tempY);
}

void Program::moveAI(float timeElapsed) {
	return;
}

void Program::plotAIPath(float playerX, float playerY) {
	return;
}