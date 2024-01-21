#pragma once

#include "Texture.h"

class Bullet : public Texture
{
public:
    // Enum for the current direction of the bullet
    enum BulletDirection
    {
        DIR_NONE,
        DIR_LEFT,
        DIR_RIGHT
    };

    // Velocity for the bullet
    static const int BUL_VEL = 4;

    // Dimension of the bullet
    static const int BULLET_WIDTH = 12;
    static const int BULLET_HEIGHT = 12;

    // Constructor
    Bullet();

    // Destructor
    ~Bullet();

    // Handle move on screen for the bullet
    void handleMove(int currentWindowWidth);

    // Set the value for onScreen variable
    void setOnScreen(bool onScreen);

    // Get the value of the onScreen variable
    bool getOnScreen();

    // Set value of the direction of the bullet
    void setBulletDirection(BulletDirection currentDirection);

    // Get value for the direction of the bullet
    BulletDirection getBulletDirection();

private:
    // Check the bullet on screen
    bool mOnScreen;

    // Current direction of the bullet
    BulletDirection mCurrentDirection;
};
