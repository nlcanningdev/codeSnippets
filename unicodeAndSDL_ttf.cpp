#include <Windows.h>
#include <fileapi.h>
#include <shlobj_core.h>
#include <KnownFolders.h>
#include <wchar.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "dependencies/SDL2/include/SDL.h"
#include "dependencies/SDL2_image/include/SDL_image.h"
#include "dependencies/SDL2_ttf/include/SDL_ttf.h"


//create testAppFolder directory in <username>/AppData/Local/
//then createa  a file testFile.txt and write "testing" to it
//using filesystem
//creates file in game directory also to test from (can't do this 
// except to read from in real game)
//uses sdl_ttf's unicode (uint16, close to wchar_t) functions to 
//display unicode strings both hardcoded and from files to the windows
//uses WideCharToMultiByte and MultiByteToWideChar because
//no other working solution yet on windows

int main(int argc, char** argv) {
	//if windows
	PWSTR windowsPath;
	if (!SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &windowsPath)))
		return 0; //would return error here
	std::filesystem::path folderPath = u8"\\testAppFolder";
	std::wstring windowsDirectoryCreationPath = std::wstring(windowsPath) + folderPath.wstring();
	std::wstring windowsFilePath = windowsDirectoryCreationPath;
	for (size_t a = 0; a < windowsFilePath.length(); ++a) {
		if (windowsFilePath[a] == L'\\')
			windowsFilePath[a] = L'/';
	}
	std::filesystem::path path = windowsFilePath;
	if (!std::filesystem::is_directory(windowsFilePath))
		CreateDirectoryW(windowsFilePath.c_str(), NULL);
	else
		std::cout << "directory already exists" << std::endl;
	std::filesystem::path filePath = u8"/testFile.txt";
	windowsFilePath += filePath.wstring();
	std::ofstream writeFile(windowsFilePath);
	if (!writeFile.is_open())
		std::cout << "file failed to open" << std::endl;
	else
		std::cout << "file was opened" << std::endl;
	writeFile << "testing";
	writeFile.close();
	writeFile.clear();

	wchar_t* windowsDirectoryPath = new wchar_t[MAX_PATH];
	GetModuleFileNameW(NULL, windowsDirectoryPath, MAX_PATH);
	path = windowsDirectoryPath;
	path = path.parent_path();
	path += u8"\\testFile.txt";
	writeFile.open(path.c_str(), std::ios::binary);
	std::wstring writeString = L"testing";
	int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &writeString[0], (int)writeString.size(), NULL, 0, NULL, NULL);
	std::string finalText(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, &writeString[0], (int)writeString.size(), &finalText[0], sizeNeeded, NULL, NULL);
	writeFile.write(&finalText[0], finalText.size());
	writeString = L"天下";
	sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &writeString[0], (int)writeString.size(), NULL, 0, NULL, NULL);
	finalText = std::string(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, &writeString[0], (int)writeString.size(), &finalText[0], sizeNeeded, NULL, NULL);
	size_t position = writeFile.tellp();
	writeFile.write(&finalText[0], finalText.size());
	size_t sizeOfText = (size_t)writeFile.tellp() - position;
	writeFile.close();
	writeFile.clear();

	std::cout << "program ran" << std::endl;



	char input;
	std::cin >> input;

	//return 0;

	std::cout << "running font test" << std::endl;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("unicodeFont", 30, 30, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

	size_t textureNum = 6;
	SDL_Texture** texture = new SDL_Texture*[textureNum];
	for (size_t a = 0; a < textureNum; ++a) {
		texture[a] = nullptr;
	}

	size_t fontNum = 5;
	TTF_Font** font = new TTF_Font*[fontNum];
	for (size_t a = 0; a < fontNum; ++a) {
		font[a] = nullptr;
	}

	size_t currentTexture = 0;
	size_t currentFont = 0;

	int currentY = 10;
	int* y = new int[textureNum];
	int* w = new int[textureNum];
	int* h = new int[textureNum];

	SDL_Event event;
	bool runProgram = true;

	int fontToLoad = -1;

	bool test = false;

	while (runProgram) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				runProgram = false;
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_0)
					fontToLoad = 0; //latin extended
				else if (event.key.keysym.sym == SDLK_1)
					fontToLoad = 1; //arabic
				else if (event.key.keysym.sym == SDLK_2)
					fontToLoad = 2; //devanagari
				else if (event.key.keysym.sym == SDLK_3)
					fontToLoad = 3; //chinese simplified
				else if (event.key.keysym.sym == SDLK_4)
					fontToLoad = 4; //chinese traditional
				else if (event.key.keysym.sym == SDLK_5)
					fontToLoad = 5; //japanese
			}
		}
		if (fontToLoad != -1 &&currentFont < 6) {
			test = true;
			SDL_Surface* surface = nullptr;
			std::wstring textToWrite;
			if (fontToLoad == 0) {
				textToWrite = L"Пролетарии всех стран, соединяйтесь!";
				font[currentFont] = TTF_OpenFont("F:\\source\\repos\\testEnvironment\\x64\\Release\\Open_Sans\\static\\OpenSans\\OpenSans-Regular.ttf", 12);
			}
			else if (fontToLoad == 1) {
				textToWrite = L"ٱلْمَمْلَكَة ٱلْعَرَبِيَّة ٱلسُّعُوْدِيَّة";
				font[currentFont] = TTF_OpenFont("F:\\source\\repos\\testEnvironment\\x64\\Release\\Amiri\\Amiri-Regular.ttf", 12);
			}
			else if (fontToLoad == 2) {
				textToWrite = L"देवनागरी लिपि";
				font[currentFont] = TTF_OpenFont("F:\\source\\repos\\testEnvironment\\x64\\Release\\Martel\\Martel-Regular.ttf", 12);
			}
			else if (fontToLoad == 3) {
				textToWrite = L"义勇军进行曲";
				font[currentFont] = TTF_OpenFont("F:\\source\\repos\\testEnvironment\\x64\\Release\\Noto_Sans_SC\\NotoSansSC-Regular.otf", 12);
			}
			else if (fontToLoad == 4) {
				textToWrite = L"中華民國國歌";
				font[currentFont] = TTF_OpenFont("F:\\source\\repos\\testEnvironment\\x64\\Release\\Noto_Sans_TC\\NotoSansTC-Regular.otf", 12);
			}
			else if (fontToLoad == 5) {
				textToWrite = L"君が代";
				font[currentFont] = TTF_OpenFont("F:\\source\\repos\\testEnvironment\\x64\\Release\\Noto_Sans_JP\\NotoSansJP-Regular.otf", 12);
			}
			surface = TTF_RenderUNICODE_Blended_Wrapped(font[currentFont], (const Uint16*)textToWrite.c_str(), SDL_Color{ 0, 0, 0, 0 }, 600);
			y[currentFont] = currentY;
			w[currentFont] = surface->w;
			h[currentFont] = surface->h;
			currentY += surface->h + 10;
			if (surface != nullptr) {
				texture[currentFont] = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
			}
			++currentFont;
			fontToLoad = -1;
		}
		else if (fontToLoad != -1 && currentFont == 6) {
			SDL_Surface* surface = nullptr;
			std::string readText(sizeOfText, 0);
			std::ifstream readFile(path.c_str(), std::ios::binary);
			readFile.seekg(position);
			readFile.read(&readText[0], sizeOfText);
			int wchars_num = MultiByteToWideChar(CP_UTF8, 0, readText.c_str(), -1, NULL, 0);
			std::wstring textToWrite(wchars_num, 0);
			MultiByteToWideChar(CP_UTF8, 0, readText.c_str(), -1, &textToWrite[0], wchars_num);
			readFile.close();
			readFile.clear();
			surface = TTF_RenderUNICODE_Blended_Wrapped(font[3], (const Uint16*)textToWrite.c_str(), SDL_Color{0, 0, 0, 0}, 600);
			y[currentFont] = currentY;
			w[currentFont] = surface->w;
			h[currentFont] = surface->h;
			currentY += surface->h + 10;
			if (surface != nullptr) {
				texture[currentFont] = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
			}
			++currentFont;
			fontToLoad = -1;
		}
		SDL_RenderClear(renderer);
		for (size_t a = 0; a < currentFont; ++a) {
			SDL_Rect screenCoordinates = { 10, y[a], w[a], h[a]};
			SDL_RenderCopy(renderer, texture[a], NULL, &screenCoordinates);
			if(test)
				std::cout << "image renderered: " << a << std::endl;
		}
		test = false;
		SDL_RenderPresent(renderer);
	}

	for (size_t a = 0; a < textureNum; ++a) {
		SDL_DestroyTexture(texture[a]);
	}
	delete[] texture;

	for (size_t a = 0; a < fontNum; ++a) {
		TTF_CloseFont(font[a]);
	}
	delete[] font;

	delete[] y;
	delete[] w;
	delete[] h;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();

	return 0;
}