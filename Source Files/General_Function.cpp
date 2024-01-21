#include "../Header Files/General_Function.h"

bool init(Window &window)
{
    // Succes flag
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Could not initialize SDL! Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // Create window
        if (!window.init())
        {
            std::cout << "Failed to create window!\n";
            success = false;
        }
        else
        {
            // Create renderer
            if (!window.createRenderer())
            {
                std::cout << "Failed to create renderer!\n";
                success = false;
            }
            else
            {
                // Initialize render draw color
                SDL_SetRenderDrawColor(window.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

                // Init IMG load
                if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
                {
                    std::cout << "Could not initialize image load! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }

                // Init ttf
                if (TTF_Init() == -1)
                {
                    std::cout << "Could not init tff! Error: " << TTF_GetError() << "\n";
                    success = false;
                }

                // Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    std::cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << "\n";
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(SDL_Renderer *renderer, Texture &backgroundTexture, Character &player, Texture &tile, Sound &music)
{
    bool success = true;

    if (!backgroundTexture.loadFromFile(renderer, "Images/background.png"))
    {
        std::cout << "Failed to load background image!\n";
        success = false;
    }
    else
    {

        if (!player.loadFromFile(renderer, "Images/character.png"))
        {
            std::cout << "Could not load texture of character!\n";
            success = false;
        }
        else
        {
            // Set clip for the character
            player.setClips();
            
            // Load gunfire for the character
            player.loadSoundEffect("Audio/ak47.mp3");

            if (!tile.loadFromFile(renderer, "Images/tile.png"))
            {
                std::cout << "Failed to load tile image!\n";
                success = false;
            }
            else
            {
                if (!music.loadMusic("Audio/zombie_tsunami.mp3"))
                {
                    std::cout << "Failed to load music from file!\n";
                    success = false;
                }
            }
        }
    }

    return success;
}

void close(Window &window, Texture &backgroundTexture, Character &player, Texture &tile, Sound &music)
{
    // Destroy window and renderer
    window.free();

    // Free tile, player and background texture
    tile.free();
    player.free();
    backgroundTexture.free();

    // Free Music
    music.freeMusic();

    // Quit subsystems
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}