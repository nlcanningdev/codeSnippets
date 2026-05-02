#include "sound.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>

void Sound::setupSound(std::string path) {
  buffer.loadFromFile(path.c_str());
  sound.setBuffer(buffer);
}
