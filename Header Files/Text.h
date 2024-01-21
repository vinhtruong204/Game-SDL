#pragma once

#include "Texture.h"

class Text : public Texture
{
public:
    // Constructor
    Text();

    // Destructor
    ~Text();

    // Free old font loaded
    void freeFont();

    // Load font from file
    bool loadFont(std::string path, int size);

    // Create texture from text
    bool loadFromRenderedText(SDL_Renderer *renderer, std::string textureText);

    // Render text to screen
    void renderText(SDL_Renderer *renderer, std::string text);

    // Setters and getters of font
    void setFont(TTF_Font *font);
    TTF_Font *getFont();

    // Setters and getters of text color
    void setTextColor(SDL_Color textColor);
    SDL_Color getTextColor();

private:
    // Actual font and text color
    TTF_Font *mFont;
    SDL_Color mTextColor;
};

