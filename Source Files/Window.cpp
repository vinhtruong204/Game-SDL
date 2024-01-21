#include "../Header Files/Window.h"

Window::Window()
{
    mRenderer = nullptr;
    mWindow = nullptr;

    mWidth = 0;
    mHeight = 0;

    mFullScreen = false;
    mMinimized = false;
}

bool Window::init()
{
    // Create window resizeable
    mWindow = SDL_CreateWindow("Dang bao nhieu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (mWindow == nullptr)
    {
        std::cout << "Could not create window! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
    }

    return mWindow != nullptr;
}

bool Window::createRenderer()
{
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr)
    {
        std::cout << "Failed to create renderer from window! Error: " << SDL_GetError() << std::endl;
    }
    return mRenderer != nullptr;
}

void Window::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_WINDOWEVENT)
    {
        switch (e.window.event)
        {
        // Get new dimension of window and repaint
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            SDL_RenderPresent(mRenderer);
            break;

        // Repaint on exposed
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(mRenderer);
            break;

        // Window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

        // Window maximized
        case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;

        // Window restored
        case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
        }
    }

    // Exit full screen on Enter key
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11)
    {
        if (mFullScreen)
        {
            SDL_SetWindowFullscreen(mWindow, 0);
            mFullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
            mFullScreen = true;
            mMinimized = false;
        }
    }
}

void Window::free()
{
    if (mWindow != nullptr)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;

        mFullScreen = false;
        mMinimized = false;
        mWidth = 0;
        mHeight = 0;
    }

    if (mRenderer != nullptr)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
}

void Window::clearScreen()
{
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer);
}

void Window::updateScreen()
{
    SDL_RenderPresent(mRenderer);
}

int Window::getWidth()
{
    return this->mWidth;
}

int Window::getHeight()
{
    return this->mHeight;
}

SDL_Renderer *Window::getRenderer()
{
    return this->mRenderer;
}

bool Window::isMinimized()
{
    return this->mMinimized;
}

Window::~Window()
{
    free();
}