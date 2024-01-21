#include "../Header Files/Text.h"

Text::Text()
{
    // Initialize font and text color to black
    mFont = nullptr;
    mTextColor = SDL_Color{0, 0, 0, 0xFF};
}

Text::~Text()
{
    // Free font
    freeFont();

    mTextColor = SDL_Color{0, 0, 0, 0xFF};
}

bool Text::loadFont(std::string path, int size)
{
    // Free old font loaded
    freeFont();

    // Load font from specific file
    mFont = TTF_OpenFont(path.c_str(), size);

    // If could not load font from file
    if (mFont == nullptr)
    {
        std::cout << "Failed to load font from file path: " << path << " Error: " << TTF_GetError() << std::endl;
    }

    return mFont != nullptr;
}

void Text::freeFont()
{
    if (mFont != nullptr)
    {
        TTF_CloseFont(mFont);
        mFont = nullptr;
    }
}

bool Text::loadFromRenderedText(SDL_Renderer *renderer, std::string textureText)
{
    // Free old texture
    Texture::free();

    // Text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, textureText.c_str(), mTextColor);

    if (textSurface == nullptr)
    {
        std::cout << "Could not create texture from surface! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        // Create texture from surface
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (mTexture == nullptr)
        {
            std::cout << "Could not create texture from surface! Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            // Get text image dimension
            mCollisionBox.w = textSurface->w;
            mCollisionBox.h = textSurface->h;
        }

        // Free loaded textsurface
        SDL_FreeSurface(textSurface);
    }

    return mTexture != nullptr;
}

void Text::renderText(SDL_Renderer *renderer, std::string text)
{
    // If failed to create texture from text
    if (!loadFromRenderedText(renderer, text))
    {
        std::cout << "Could not create texture from text!\n";
    }

    // Render text to screen
    else
    {
        Texture::render(renderer);
    }
}

void Text::setFont(TTF_Font *font)
{
    this->mFont = font;
}

TTF_Font *Text::getFont()
{
    return this->mFont;
}

void Text::setTextColor(SDL_Color textColor)
{
    this->mTextColor = textColor;
}

SDL_Color Text::getTextColor()
{
    return this->mTextColor;
}
