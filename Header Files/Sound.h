#pragma once

#include "Window.h"

class Sound
{
public:
    // Constructor
    Sound();

    // Destructor
    ~Sound();

    // Load sound effect from file
    bool loadSoundEffect(std::string path);

    // Load music background from file
    bool loadMusic(std::string path);

    // Play sound effect
    void playSoundEffect();

    // Play music background
    void playMusic();

    // Free sound effect
    void freeSoundEffect();

    // Free music background
    void freeMusic();

private:
    // Specific action sound effects
    Mix_Chunk *mSoundEffect;

    // Music background
    Mix_Music *mMusic;
};
