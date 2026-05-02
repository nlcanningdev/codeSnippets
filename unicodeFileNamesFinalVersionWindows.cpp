/*#include "dependencies/SDL2/include/SDL.h"
#include "dependencies/SDL2_image/include/SDL_image.h"
#include "dependencies/openalSoft/include/AL/al.h"
#include "dependencies/openalSoft/include/AL/alc.h"
#include "audioInfo.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

std::string audioFileName = "audio"; //both of these would be part of the base program class in a real program

void loadAudio(AudioData& audioData) {
	std::ifstream((audioFileName + std::to_string(audioData.fileNum)).c_str(), std::ios::binary);

	std::string fileName = audioFileName + std::to_string(audioData.fileNum);
}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow("testEnvironment", 20, 20, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	char* data;
	std::ifstream readFile;
	readFile.open("testImage.png", std::ios::binary | std::ios::ate);
	size_t dataSize = readFile.tellg();
	data = new char[dataSize];
	readFile.seekg(0);
	readFile.read(data, dataSize);
	readFile.close();
	readFile.clear();
	SDL_RWops* rwop = SDL_RWFromMem(data, dataSize);
	if (rwop == NULL)
		std::cout << "rwop is NULL" << std::endl;
	else
		std::cout << "rwop should be fine" << std::endl;
	SDL_Surface* surface = IMG_Load_RW(rwop, 0);
	if (surface == NULL)
		std::cout << "surface is NULL" << std::endl;
	else
		std::cout << "surface should be fine" << std::endl;
	SDL_RWclose(rwop);
	delete[] data;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		std::cout << "texture is NULL" << std::endl;
	else
		std::cout << "texture should be fine" << std::endl;
	SDL_FreeSurface(surface);

	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE) {
		std::cout << "enumeration extension not available" << std::endl;
		return 0;
	}
	ALCdevice* device = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	if (!device) {
		std::cout << "unable to use default audio device" << std::endl;
		return 0;
	}
	ALCcontext* context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		std::cout << "failed to make default context" << std::endl;
		return 0;
	}
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	ALfloat listenerOrientation[6] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListenerfv(AL_ORIENTATION, listenerOrientation);
	ALuint source;
	alGenSources(ALuint(1), &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	//data related to wav files is hardcoded into the program
	AudioData audioData;
	loadAudio(audioData);


	//in final program, have the size etc of audio files (from wav headers
	//hardcoded in, because memcpy etc. is expensive

	bool runProgram = true;
	SDL_Event event;
	while (runProgram) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				runProgram = false;
		}
		SDL_RenderClear(renderer);
		SDL_FRect texturePosition = { 200.0f, 200.0f, 100.0f, 100.0f };
		SDL_RenderCopyF(renderer, texture, NULL, &texturePosition);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}*/

//check if dire

#include <Windows.h>
#include <fileapi.h>
#include <shlobj_core.h>
#include <KnownFolders.h>
#include <wchar.h>
#include <fstream>
#include <filesystem>
#include <iostream>

//create testAppFolder directory in <username>/AppData/Local/
//then createa  a file testFile.txt and write "testing" to it
//in unicode utf8

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
	path = path.parent_path().wstring();
	path += u8"\\testFile.txt";
	std::wofstream writeFileWide(path.c_str());
	writeFileWide << L"testing" << '\n';
	writeFileWide << path.wstring() << '\n';
	writeFileWide.close();
	writeFileWide.clear();

	std::cout << "program ran" << std::endl;
	char input;
	std::cin >> input;

	return 0;
}