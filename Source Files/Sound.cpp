#include "../Header Files/Sound.h"

Sound::Sound()
{
    // Initialize value
    mSoundEffect = nullptr;
    mMusic = nullptr;
}

Sound::~Sound()
{
    freeSoundEffect();
    freeMusic();
}

bool Sound::loadSoundEffect(std::string path)
{
    // Free old sound effect
    freeSoundEffect();

    mSoundEffect = Mix_LoadWAV(path.c_str());

    if (mSoundEffect == nullptr)
    {
        std::cout << "Failed to load sound effect from file path: " << path << " Error: " << Mix_GetError() << std::endl;
    }

    return mSoundEffect != nullptr;
}

bool Sound::loadMusic(std::string path)
{
    // Free old music
    freeMusic();

    mMusic = Mix_LoadMUS(path.c_str());

    if (mMusic == nullptr)
    {
        std::cout << "Failed  to load music from file path: " << path << " Error: " << Mix_GetError() << std::endl;
    }

    return mMusic != nullptr;
}

void Sound::playSoundEffect()
{
    Mix_PlayChannel(-1, mSoundEffect, 0);
}

void Sound::playMusic()
{
    // If no music playing
    if (Mix_PlayingMusic() == 0)
    {
        // Play music
        Mix_PlayMusic(mMusic, -1); // -1: Loop until it is stopped
    }
}

void Sound::freeSoundEffect()
{
    if (mSoundEffect != nullptr)
    {
        Mix_FreeChunk(mSoundEffect);
        mSoundEffect = nullptr;
    }
}

void Sound::freeMusic()
{
    if (mMusic != nullptr)
    {
        Mix_FreeMusic(mMusic);
        mMusic = nullptr;
    }
}