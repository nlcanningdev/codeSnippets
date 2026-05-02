#pragma once

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Sound {
  private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
  public:
    void setupSound(std::string path);
    inline void playSound() { sound.play(); }
};
