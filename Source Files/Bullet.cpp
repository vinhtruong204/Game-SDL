#include "../Header Files/Bullet.h"

Bullet::Bullet()
{
    mCurrentDirection = DIR_NONE;
    mOnScreen = false;
}

Bullet::~Bullet()
{
    mCurrentDirection = DIR_NONE;
    mOnScreen = false;
}

void Bullet::handleMove(int currentWindowWidth)
{
    // If current direction is left
    if (mCurrentDirection == DIR_LEFT)
    {
        // Move the bullet to left
        mCollisionBox.x += -BUL_VEL;
    }

    // If current direction is right or don't have direction
    else
    {
        // Move the bullet to right
        mCollisionBox.x += BUL_VEL;
    }

    // If bullet went out of screen
    if (mCollisionBox.x < 0 || mCollisionBox.x > currentWindowWidth)
    {
        mOnScreen = false;
    }
}

void Bullet::setOnScreen(bool pOnScreen)
{
    this->mOnScreen = pOnScreen;
}

bool Bullet::getOnScreen()
{
    return this->mOnScreen;
}

void Bullet::setBulletDirection(BulletDirection pCurrentDiection)
{
    this->mCurrentDirection = pCurrentDiection;
}

Bullet::BulletDirection Bullet::getBulletDirection()
{
    return this->mCurrentDirection;
}