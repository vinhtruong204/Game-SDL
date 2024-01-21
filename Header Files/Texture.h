#pragma once

#include "Window.h"

class Texture
{
public:
    // Constructor
    Texture();

    // Free memory
    void free();

    // Load image texture from file
    bool loadFromFile(SDL_Renderer *renderer, std::string path);

    // Update rectangle
    void updateCollisionBox(int x = 0, int y = 0, int width = 0, int height = 0);

    // Render to screen
    void render(SDL_Renderer *renderer, SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Set actual texture
    void setTexture(SDL_Texture *texture);

    // Get rectangle destination
    SDL_Rect *getCollisionBox();

    // Get actual texture
    SDL_Texture *getTexture();

    // Get image dimension
    int getWidth();
    int getHeight();

    // Destructor
    ~Texture();

protected:
    // The actual texture
    SDL_Texture *mTexture;

    // Rectangle when rendered
    SDL_Rect mCollisionBox;
};
