#include "dependencies/openalSoft/include/AL/al.h"
#include "dependencies/openalSoft/include/AL/alc.h"
#include "dependencies/openalSoft/include/AL/alext.h"
#include "dependencies/libvorbis/include/vorbis/vorbisfile.h"
#include "dependencies/SDL2/include/SDL.h"
#include "dependencies/SDL2_image/include/SDL_image.h"
#include "dependencies/SDL2_ttf/include/SDL_ttf.h"
#include <iostream>
#include <fstream>

struct StreamingAudioData {
	StreamingAudioData() : sizeConsumed(0), oggCurrentSection(0) {}
	ALuint buffers[4];
	const char* filename;
	std::ifstream file;
	uint8_t channels;
	int32_t sampleRate;
	uint8_t bitsPerSample;
	ALsizei size;
	ALuint source;
	ALsizei sizeConsumed;
	ALenum format;
	OggVorbis_File oggVorbisFile;
	int_fast32_t oggCurrentSection;
	size_t duration;
};

struct SoundEffectAudioData {
	SoundEffectAudioData() {}
	ALuint* buffers; //point to a position in the audio pool
	size_t audioDataStart;
	size_t audioDataSize;
	const char* filename;
	uint8_t channels;
	int32_t sampleRate;
	uint8_t bitsPerSample;
	ALsizei size;
	ALuint source;
	ALsizei sizeConsumed;
	ALenum format;
	OggVorbis_File oggVorbisFile;
	int_fast32_t oggCurrentSection;
	size_t duration;
};

size_t read_ogg_callback(void* destination, size_t size1, size_t size2, void* fileHandle) {
	StreamingAudioData* audioData = reinterpret_cast<StreamingAudioData*>(fileHandle);
	ALsizei length = size1 * size2;
	if (audioData->sizeConsumed + length > audioData->size)
		length = audioData->size - audioData->sizeConsumed;
	if (!audioData->file.is_open()) {
		audioData->file.open(audioData->filename, std::ios::binary);
		if (!audioData->file.is_open()) {
			std::cerr << "Error: could not open streaming file " << audioData->filename << std::endl;
			return 0;
		}
	}
	char* moreData = new char[length];
	audioData->file.clear();
	audioData->file.seekg(audioData->sizeConsumed);
	if (!audioData->file.read(&moreData[0], length)) {
		if (audioData->file.eof())
			audioData->file.clear();
		else if (audioData->file.fail()) {
			std::cerr << "error: ogg stream has fail bit set " << audioData->filename << std::endl;
			audioData->file.clear();
			return 0;
		}
		else if (audioData->file.bad()) {
			std::cerr << "error: ogg stream has bad bit set " << audioData->filename << std::endl;
			audioData->file.clear();
			return 0;
		}
	}
	audioData->sizeConsumed += length;
	std::memcpy(destination, &moreData[0], length);
	delete[] moreData;
	audioData->file.clear();
	return length;
}

int32_t seek_ogg_callback(void* fileHandle, ogg_int64_t to, int32_t type) {
	StreamingAudioData* audioData = reinterpret_cast<StreamingAudioData*>(fileHandle);
	if (type == SEEK_CUR)
		audioData->sizeConsumed += to;
	else if (type == SEEK_END)
		audioData->sizeConsumed = audioData->size - to;
	else if (type == SEEK_SET)
		audioData->sizeConsumed = to;
	else
		return -1;
	
	if (audioData->sizeConsumed < 0) {
		audioData->sizeConsumed = 0;
		return -1;
	}
	if (audioData->sizeConsumed > audioData->size) {
		audioData->sizeConsumed = audioData->size;
		return -1;
	}
	return 0;
}

long int tell_ogg_callback(void* fileHandle) {
	StreamingAudioData* audioData = reinterpret_cast<StreamingAudioData*>(fileHandle);
	return audioData->sizeConsumed;
}

bool create_sound_effect_from_file(const char* filename, SoundEffectAudioData& audioData) {
	audioData.filename = filename;
	std::ifstream readFile(filename, std::ios::binary);
	if (!readFile.is_open()) {
		std::cerr << "error couldn't open file" << std::endl;
		return 0;
	}
	readFile.seekg(0, std::ios_base::beg);
	readFile.ignore(std::numeric_limits<std::streamsize>::max());
	audioData.size = readFile.gcount();
	readFile.clear();
	readFile.seekg(0, std::ios_base::beg);
	audioData.sizeConsumed = 0;
}

bool create_stream_from_file(const char* filename, StreamingAudioData& audioData) {
	audioData.filename = filename;
	audioData.file.open(filename, std::ios::binary);
	if (!audioData.file.is_open()) {
		std::cerr << "error couldn't open file" << std::endl;
		return 0;
	}
	audioData.file.seekg(0, std::ios_base::beg);
	audioData.file.ignore(std::numeric_limits<std::streamsize>::max());
	audioData.size = audioData.file.gcount();
	audioData.file.clear();
	audioData.file.seekg(0, std::ios_base::beg);
	audioData.sizeConsumed = 0;
	ov_callbacks oggCallbacks;
	oggCallbacks.read_func = read_ogg_callback;
	oggCallbacks.close_func = nullptr;
	oggCallbacks.seek_func = seek_ogg_callback;
	oggCallbacks.tell_func = tell_ogg_callback;

	if (ov_open_callbacks(reinterpret_cast<void*>(&audioData), &audioData.oggVorbisFile, nullptr, -1, oggCallbacks) < 0) {
		std::cerr << "error could not ov_open_callbacks" << std::endl;
		return false;
	}

	vorbis_info* vorbisInfo = ov_info(&audioData.oggVorbisFile, -1);

	audioData.channels = vorbisInfo->channels;
	audioData.bitsPerSample = 16;
	audioData.sampleRate = vorbisInfo->rate;
	audioData.duration = ov_time_total(&audioData.oggVorbisFile, -1);

	alGenBuffers(4, &audioData.buffers[0]);
	if (audioData.file.eof()) {
		std::cerr << "error already reached eof without loading data" << std::endl;
		return false;
	}
	else if (audioData.file.fail()) {
		std::cerr << "error fail bit set" << std::endl;
		return false;
	}
	else if (!audioData.file) {
		std::cerr << "error file is false" << std::endl;
		return false;
	}

	char* data = new char[65536]; //replace these with a bufferSize variable, but no globals

	for (size_t i = 0; i < 4; ++i) {
		size_t dataSoFar = 0;
		while (dataSoFar < 65536) {
			int32_t result = ov_read(&audioData.oggVorbisFile, &data[dataSoFar], 65536 - dataSoFar, 0, 2, 1, &audioData.oggCurrentSection);
			if (result == OV_HOLE) {
				std::cerr << "error: OV_HOLE found in initial read of buffer " << i << std::endl;
				break;
			}
			else if (result == OV_EBADLINK) {
				std::cerr << "error: PV_EBADLINK found in initial read of buffer " << i << std::endl;
				break;
			}
			else if (result == OV_EINVAL) {
				std::cerr << "error: OV_EINVAL found in initial read of buffer " << i << std::endl;
			}
			else if (result == 0) {
				std::cerr << "error: eof found in initial read of buffer " << i << std::endl;
				break;
			}
			dataSoFar += result;
		}
		if (audioData.channels == 1 && audioData.bitsPerSample == 8)
			audioData.format = AL_FORMAT_MONO8;
		else if (audioData.channels == 1 && audioData.bitsPerSample == 16)
			audioData.format = AL_FORMAT_MONO16;
		else if (audioData.channels == 2 && audioData.bitsPerSample == 8)
			audioData.format = AL_FORMAT_STEREO8;
		else if (audioData.channels == 2 && audioData.bitsPerSample == 16)
			audioData.format = AL_FORMAT_STEREO16;
		else {
			std::cerr << "error: unrecognised ogg format: " << audioData.channels << " channels, " << audioData.bitsPerSample << " bps" << std::endl;
			delete[] data;
			return false;
		}
		alBufferData(audioData.buffers[i], audioData.format, data, dataSoFar, audioData.sampleRate);
	}
	alGenSources(1, &audioData.source);
	alSourcef(audioData.source, AL_PITCH, 1.0f);
	alSourcef(audioData.source, AL_GAIN, 1.0f);
	alSource3f(audioData.source, AL_POSITION, 0, 0, 0);
	alSource3f(audioData.source, AL_VELOCITY, 0, 0, 0);
	alSourcei(audioData.source, AL_LOOPING, AL_FALSE);
	alSourceQueueBuffers(audioData.source, 4, &audioData.buffers[0]);
	delete[] data;
	return true;
}

void play_stream(StreamingAudioData& audioData) {
	alSourceStop(audioData.source);
	alSourcePlay(audioData.source);
}

void update_stream(StreamingAudioData& audioData) {
	ALint buffersProcessed = 0;
	alGetSourcei(audioData.source, AL_BUFFERS_PROCESSED, &buffersProcessed);
	if (buffersProcessed <= 0)
		return;
	while (buffersProcessed--) {
		ALuint buffer;
		alSourceUnqueueBuffers(audioData.source, 1, &buffer);
		char* data = new char[65536];
		std::memset(data, 0, 65536);
		ALsizei dataSizeToBuffer = 0;
		size_t sizeRead = 0;

		while (sizeRead < 65536) {
			int32_t result = ov_read(&audioData.oggVorbisFile, &data[sizeRead], 65536 - sizeRead, 0, 2, 1, &audioData.oggCurrentSection);
			if (result == OV_HOLE) {
				std::cerr << "error: OV_HOLE found in initial read of buffer " << std::endl;
				break;
			}
			else if (result == OV_EBADLINK) {
				std::cerr << "error: PV_EBADLINK found in initial read of buffer " << std::endl;
				break;
			}
			else if (result == OV_EINVAL) {
				std::cerr << "error: OV_EINVAL found in initial read of buffer " << std::endl;
			}
			else if (result == 0) {
				int32_t seekResult = ov_raw_seek(&audioData.oggVorbisFile, 0);
				if (seekResult == OV_ENOSEEK)
					std::cerr << "ERROR: OV_ENOSEEK found when trying to loop" << std::endl;
				else if (seekResult == OV_EINVAL)
					std::cerr << "ERROR: OV_EINVAL found when trying to loop" << std::endl;
				else if (seekResult == OV_EREAD)
					std::cerr << "ERROR: OV_EREAD found when trying to loop" << std::endl;
				else if (seekResult == OV_EFAULT)
					std::cerr << "ERROR: OV_EFAULT found when trying to loop" << std::endl;
				else if (seekResult == OV_EOF)
					std::cerr << "ERROR: OV_EOF found when trying to loop" << std::endl;
				else if (seekResult == OV_EBADLINK)
					std::cerr << "ERROR: OV_EBADLINK found when trying to loop" << std::endl;
				if (seekResult != 0) {
					std::cerr << "error: unknown error in ov_raw_seek" << std::endl;
					return;
				}
			}
			sizeRead += result;
		}
		dataSizeToBuffer = sizeRead;
		if (dataSizeToBuffer > 0) {
			alBufferData(buffer, audioData.format, data, dataSizeToBuffer, audioData.sampleRate);
			alSourceQueueBuffers(audioData.source, 1, &buffer);
		}
		if (dataSizeToBuffer < 65536)
			std::cout << "data missing" << std::endl;
		ALint state;
		alGetSourcei(audioData.source, AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING) {
			alSourceStop(audioData.source);
			alSourcePlay(audioData.source);
		}
		delete[] data;
	}
}

void loadTexture(SDL_Renderer*& renderer, const char* fileName, SDL_Texture*& texture) {
	SDL_Surface* surface = IMG_Load(fileName);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

struct ActorData {
	void setData(float width, float height, bool isUI, bool isCamera, float x, float y, size_t textureIndex) {
		this->width = width;
		this->height = height;
		this->isUI = isUI;
		this->isCamera = isCamera;
		this->x = x;
		this->y = y;
		this->textureIndex = textureIndex;
	}
	float width;
	float height;
	bool isUI; //if true x and y and width and height represent percentages
	bool isCamera; //if true ignore textureIndex
	float x;
	float y;
	size_t textureIndex;
};

int main(int argc, char** argv) {
	ALCdevice* openALDevice = alcOpenDevice(nullptr);
	if (!openALDevice)
		return 0;
	ALCcontext* openALContext = alcCreateContext(openALDevice, nullptr);
	alcMakeContextCurrent(openALContext);
	StreamingAudioData audioData[2];

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC);
	SDL_Window* window = SDL_CreateWindow("audio test", 20, 20, 500, 500, SDL_WINDOW_SHOWN);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* texture[6];
	loadTexture(renderer, "mainCharacterTexture.png", texture[0]);
	loadTexture(renderer, "npcCharacterTexture.png", texture[1]);
	loadTexture(renderer, "tileTexture.png", texture[2]);
	loadTexture(renderer, "radioTexture.png", texture[3]);
	loadTexture(renderer, "recordPlayer.png", texture[4]);
	loadTexture(renderer, "button.png", texture[5]);
	float worldWidth = 5000;
	float worldHeight = 5000;
	const size_t actorNum = 6 + ((5000 / 250) * (5000 / 250));
	ActorData* actorData = new ActorData[actorNum];
	actorData[0].setData(250, 250, false, false, 2000, 2000, 0); //player character
	actorData[1].setData(250, 250, false, false, 3000, 3000, 1); //npc
	actorData[2].setData(250, 250, false, false, 1500, 1500, 3); //radio
	actorData[3].setData(250, 250, false, false, 1500, 3500, 4); //record player
	actorData[4].setData(100, 30, true, false, 5, 85, 5); //pause radio button
	actorData[5].setData(100, 30, true, false, 110, 85, 5); //resume radio button
	float tempX = 0.0f;
	float tempY = 0.0f;
	for (size_t a = 6; a < actorNum; ++a) {
		actorData[a].setData(250, 250, false, false, tempX, tempY, 2);
		tempX += 250.0f;
		if (tempX == 5000) {
			tempX = 0.0f;
			tempY += 250.0f;
		}
	}
	ActorData camera;
	camera.setData(500, 500, false, true, 1750, 1750, 0);

	bool runGame = true;
	SDL_Event event;
	while (runGame) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				runGame = false;
		}
		SDL_RenderClear(renderer);
		for (size_t a = 0; a < actorNum; ++a) {
			if (((actorData[a].x + actorData[a].width) > camera.x) &&
				(actorData[a].x < (camera.x + camera.width)) &&
				((actorData[a].y + actorData[a].height) > camera.y) &&
				(actorData[a].y < (camera.y + camera.height))) {
				SDL_FRect rect = { actorData[a].width, actorData[a].height, actorData[a].x - camera.x, actorData[a].y - camera.y };
				SDL_RenderCopyF(renderer, texture[actorData[0].textureIndex], NULL, &rect);
			}
		}
	}
	delete[] actorData;
	for (int a = 0; a < 6; ++a) {
		SDL_DestroyTexture(texture[a]);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	create_stream_from_file("testAudio_song0.ogg", audioData[0]);
	play_stream(audioData[0]);
	ALint state = AL_PLAYING;
	size_t cursor = 65536 * 4;
	while (state == AL_PLAYING) {
		update_stream(audioData[0]);
		alGetSourcei(audioData[0].source, AL_SOURCE_STATE, &state);
	}
	alDeleteSources(1, &audioData[0].source);
	alDeleteBuffers(4, &audioData[0].buffers[0]);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(openALContext);
	alcCloseDevice(openALDevice);
	return 0;
}