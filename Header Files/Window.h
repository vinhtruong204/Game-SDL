#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

class Window
{

public:
    // Initializes internals
    Window();

    // Create window
    bool init();

    // Create renderer from window
    bool createRenderer();

    // Handle window event
    void handleEvent(SDL_Event &e);

    // Deallocate window
    void free();

    // Clear screen
    void clearScreen();

    // Update screen
    void updateScreen();

    // Get window dimension
    int getWidth();
    int getHeight();

    // Get window renderer
    SDL_Renderer *getRenderer();

    // Is minimized
    bool isMinimized();

    // Destructor
    ~Window();

private:
    // Window internal
    SDL_Window *mWindow;

    // Window dimension
    int mWidth;
    int mHeight;

    // Check window full screen or minimized
    bool mFullScreen;
    bool mMinimized;

    // Window renderer
    SDL_Renderer *mRenderer;
};