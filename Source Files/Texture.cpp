#include "../Header Files/Texture.h"

Texture::Texture()
{
    mTexture = nullptr;

    mCollisionBox = {0, 0, 0, 0};
}

Texture::~Texture()
{
    // free();
}

void Texture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;

        mCollisionBox = {0, 0, 0, 0};
    }
}

bool Texture::loadFromFile(SDL_Renderer *renderer, std::string path)
{
    // Free old texture
    free();

    // Load the surface to lock the color
    SDL_Surface *loadedSurface = nullptr;
    loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr)
    {
        std::cout << "Could not load surface from file! Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        // Create texture from loaded surface
        mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (mTexture == nullptr)
        {
            std::cout << "Could not create texture from surface! Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            // Get image dimension
            mCollisionBox.w = loadedSurface->w;
            mCollisionBox.h = loadedSurface->h;
        }

        // Free loaded surface
        SDL_FreeSurface(loadedSurface);
        loadedSurface = nullptr;
    }

    return mTexture != nullptr;
}

void Texture::updateCollisionBox(int x, int y, int width, int height)
{
    mCollisionBox.x = x;
    mCollisionBox.y = y;
    mCollisionBox.w = width;
    mCollisionBox.h = height;
}

void Texture::render(SDL_Renderer *renderer, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    // Update width, height for collision box
    if (clip != nullptr)
    {
        mCollisionBox.w = clip->w;
        mCollisionBox.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, mTexture, clip, &mCollisionBox, angle, center, flip);
}

void Texture::setTexture(SDL_Texture *texture)
{
    this->mTexture = texture;
}

SDL_Rect *Texture::getCollisionBox()
{
    return &mCollisionBox;
}

SDL_Texture *Texture::getTexture()
{
    return mTexture;
}

int Texture::getWidth()
{
    return mCollisionBox.w;
}

int Texture::getHeight()
{
    return mCollisionBox.h;
}