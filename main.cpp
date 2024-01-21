#include "Source Files/Window.cpp"
#include "Source Files/General_Function.cpp"
#include "Source Files/Texture.cpp"
#include "Source Files/Character.cpp"
#include "Source Files/Bullet.cpp"
#include "Source Files/Sound.cpp"
#include "Source Files/Text.cpp"

int main(int argc, char *args[])
{
    // The window of game
    Window window;

    // Texture on screen
    Texture backgroundTexture;
    Texture tile;

    // The character to play
    Character player;

    // Music background
    // Sound music;

    // Initialize SDL, SDL_image, SDL_Mixer, SDL_ttf
    if (!init(window))
    {
        std::cout << "Failed to initialize!\n";
    }
    else
    {
        // Load media from file
        if (!loadMedia(window.getRenderer(), backgroundTexture, player, tile))
        {
            std::cout << "Failed to load media!\n";
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            // Game running
            while (!quit)
            {
                // Handle event when it happened
                while (SDL_PollEvent(&e))
                {
                    // When user type quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    // Handle event for window
                    window.handleEvent(e);

                    // Handle event for character
                    player.handleEvent(e, window.getRenderer());
                }

                // When screen isn't minimized
                if (!window.isMinimized())
                {
                    // Clear screen
                    window.clearScreen();

                    // Play background music
                    // music.playMusic();

                    // Current window dimension
                    int currentWindowWidth = window.getWidth();
                    int currentWindowHeight = window.getHeight();

                    // Get new dimension of window for the background texture
                    backgroundTexture.updateCollisionBox(0, 0, currentWindowWidth, currentWindowHeight);

                    // Update collision box for the tile
                    tile.updateCollisionBox((currentWindowWidth - (currentWindowWidth - 300)) / 2, (currentWindowHeight - 32) / 2, currentWindowWidth - 300, 32);

                    // Move the character
                    player.move(currentWindowWidth, currentWindowHeight, tile);

                    // Render background to screen
                    backgroundTexture.render(window.getRenderer());

                    // Render tiles to screen
                    tile.render(window.getRenderer());

                    // Render current frame
                    player.render(window.getRenderer());

                    // If user tap left button
                    player.handleShoot(currentWindowWidth, window.getRenderer());

                    // Update screen
                    window.updateScreen();
                }
            }
        }
    }

    // Free resources and quit subsystem
    close(window, backgroundTexture, player, tile);
    return 0;
}