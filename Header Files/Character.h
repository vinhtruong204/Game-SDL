#pragma once

#include "Texture.h"
#include "Bullet.h"
#include "Sound.h"
#include "Text.h"

class Character : public Texture
{
public:
    // Maximum axis velocity of the character
    static const int CHAR_VEL = 5;

    // Jump velocity of the character
    static const int JUMP_VEL = 10;

    // Fall speed
    static const int FALL_SPEED = 2;
    
    // Total animation frames
    static const int TOTAL_ANIMATION_FRAMES = 8;

    // Character dimension
    static const int CHARACTER_WIDTH = 60;
    static const int CHARACTER_HEIGHT = 64;


    // Enum for the walk type
    enum WalkType
    {
        STAND_STILL,
        WALK_LEFT,
        WALK_RIGHT,
        JUMP_UP,
        JUMP_DOWN
    };

    // Constructor
    Character();

    // Set clips for the character
    void setClips();

    // Load gunfire from file
    void loadSoundEffect(std::string path);

    // Handle event for the character
    void handleEvent(SDL_Event e, SDL_Renderer *renderer);

    // Handled when the character shoots
    void handleShoot(int currentWindowWidth, SDL_Renderer *renderer);

    // Move character
    void move(int currentWindowWidth, int currentWindowHeight, Texture tile);

    // Render character to screen
    void render(SDL_Renderer *renderer);

    // Check collision with tiles
    bool checkOnGround(Texture tiles);

    // Set and get flag shooting
    void setIsShooting(bool isShooting);
    bool getIsShooting();

    // Destructor
    ~Character();

private:
    // Sound effect when fire
    Sound gunfire;

    // Bullet list when user tap to fire
    std::vector<Bullet> mBulletList;

    // Check if the character is shooting or not
    bool isShooting;

    // The velocity of the character
    int mVelX, mVelY;

    // Flip character when move
    SDL_RendererFlip flip;

    // Character clips
    SDL_Rect mCharacterClips[TOTAL_ANIMATION_FRAMES];

    // Current frame
    int mCurrentFrame;

    // Status walk
    WalkType mCharacterStatus;

    // Check player onground
    bool onGround;
};
