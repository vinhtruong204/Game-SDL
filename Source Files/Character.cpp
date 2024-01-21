#include "../Header Files/Character.h"

Character::Character() : Texture()
{
    // Initialize the velocity
    mVelX = 0;
    mVelY = FALL_SPEED;

    // Set flip for the texture
    flip = SDL_FLIP_NONE;

    // Initialize value for the current frame
    mCurrentFrame = 0;

    // Inittialize walk status
    mCharacterStatus = STAND_STILL;

    onGround = false;

    isShooting = false;

}

void Character::setClips()
{
    // Set clip for each frame
    for (int i = 0; i < TOTAL_ANIMATION_FRAMES; i++)
    {
        mCharacterClips[i].x = i * CHARACTER_WIDTH;
        mCharacterClips[i].y = 0;
        mCharacterClips[i].w = CHARACTER_WIDTH;
        mCharacterClips[i].h = CHARACTER_HEIGHT;
    }
}

void Character::loadSoundEffect(std::string path)
{
    if (!gunfire.loadSoundEffect(path))
    {
        std::cout << "Could not load gunfire sound!\n";
    }
}

void Character::handleEvent(SDL_Event e, SDL_Renderer *renderer)
{
    // When user type down a key
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            mVelY = -JUMP_VEL;
            mCharacterStatus = JUMP_UP;
            break;
        case SDLK_s:
            mVelY = JUMP_VEL;
            mCharacterStatus = JUMP_DOWN;
            break;
        case SDLK_a:
            mVelX = -CHAR_VEL;
            flip = SDL_FLIP_HORIZONTAL; // Flip the texture horizontally
            mCharacterStatus = WALK_LEFT;
            break;
        case SDLK_d:
            mVelX = CHAR_VEL;
            flip = SDL_FLIP_NONE;
            mCharacterStatus = WALK_RIGHT;
            break;
        default:
            break;
        }
    }

    // If the key is released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        // Adjust velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            mVelY = FALL_SPEED;
            mCharacterStatus = STAND_STILL;
            break;
        case SDLK_s:
            mVelY = FALL_SPEED;
            mCharacterStatus = STAND_STILL;
            break;
        case SDLK_a:
            mVelX = 0;
            mCharacterStatus = STAND_STILL;
            break;
        case SDLK_d:
            mVelX = 0;
            mCharacterStatus = STAND_STILL;
            break;
        default:
            break;
        }
    }

    // If user tap left mouse to fire
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        // If user tap mouse button left
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            // Set flag shooting
            isShooting = true;

            // Play sound effect
            gunfire.playSoundEffect();

            // Create a bullet object
            Bullet newBullet;

            if (!newBullet.loadFromFile(renderer, "Images/bullet.png"))
            {
                std::cout << "Failed to load bullet image!\n";
                return;
            }

            // Initialize on screen variable
            newBullet.setOnScreen(true);

            // Set direct for the bullet
            Bullet::BulletDirection dir = flip == SDL_FLIP_NONE ? Bullet::BulletDirection::DIR_RIGHT : Bullet::BulletDirection::DIR_LEFT;
            newBullet.setBulletDirection(dir);

            // Set collision for the new bullet
            if (dir == Bullet::BulletDirection::DIR_RIGHT)
            {
                newBullet.updateCollisionBox(mCollisionBox.x + CHARACTER_WIDTH, mCollisionBox.y + CHARACTER_HEIGHT * 0.25, Bullet::BULLET_WIDTH, Bullet::BULLET_HEIGHT);
            }
            else
            {
                newBullet.updateCollisionBox(mCollisionBox.x, mCollisionBox.y + CHARACTER_HEIGHT * 0.25, Bullet::BULLET_WIDTH, Bullet::BULLET_HEIGHT);
            }

            // Push new bullet to the vector
            mBulletList.push_back(newBullet);
        }
    }

    // When mouse button is released
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        // Set default value for isShooting variable
        isShooting = false;
    }
}

void Character::handleShoot(int currentWindowWidth, SDL_Renderer *renderer)
{
    // Travel all bullet in a vector bullet
    for (int i = 0; i < mBulletList.size(); i++)
    {
        // If it on screen
        if (mBulletList[i].getOnScreen() == true)
        {
            // Move and render the bullet on the screen
            mBulletList[i].handleMove(currentWindowWidth);
            mBulletList[i].render(renderer);
        }

        // If it doesn't on screen
        else
        {
            // Erase from bullet list
            mBulletList.erase(mBulletList.begin() + i);
            i--;
        }
    }
}

void Character::move(int currentWindowWidth, int currentWindowHeight, Texture tile)
{
    // Move character left or right
    mCollisionBox.x += mVelX;

    // If the character move out window
    if ((mCollisionBox.x < 0) || (mCollisionBox.x + mCollisionBox.w > currentWindowWidth))
    {
        // Move back
        mCollisionBox.x -= mVelX;
    }

    // Move character up or down
    mCollisionBox.y += mVelY;

    // If the character move out window
    if ((mCollisionBox.y < 0) || (mCollisionBox.y > currentWindowHeight))
    {
        // Move back
        mCollisionBox.y = 0;
    }

    // If colliding with tile and not jump
    if (checkOnGround(tile))
    {
        // Move the character back along the y axis
        mCollisionBox.y -= mVelY;
        onGround = true;
    }
    else
    {
        onGround = false;
    }
}

void Character::render(SDL_Renderer *renderer)
{
    if (mCharacterStatus == WALK_LEFT || mCharacterStatus == WALK_RIGHT)
    {
        mCurrentFrame++;
    }
    else
    {
        mCurrentFrame = 0;
    }

    if (mCurrentFrame / 3 >= TOTAL_ANIMATION_FRAMES)
        mCurrentFrame = 0;
    Texture::render(renderer, &mCharacterClips[mCurrentFrame / 3], 0, nullptr, flip);
}

bool Character::checkOnGround(Texture tile)
{
    SDL_Rect *characterBox = &mCollisionBox;
    SDL_Rect *tileBox = tile.getCollisionBox();

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // All side of rectangle character
    leftA = characterBox->x;
    rightA = characterBox->x + characterBox->w;
    topA = characterBox->y;
    bottomA = characterBox->y + characterBox->h;

    // All side of rectangle tile
    leftB = tileBox->x;
    rightB = tileBox->x + tileBox->w;
    topB = tileBox->y;
    bottomB = tileBox->y + tileBox->h;

    // If any of the side from character are outside of tile
    if (leftA >= rightB || rightA <= leftB)
    {
        return false;
    }
    else if (topA >= bottomB || bottomA <= topB)
    {
        return false;
    }

    return true;
}

void Character::setIsShooting(bool isShooting)
{
    this->isShooting = isShooting;
}

bool Character::getIsShooting()
{
    return this->isShooting;
}

Character::~Character()
{
    Texture::free();

    // Re-initialize variables to their original values
    mVelX = 0;
    mVelY = 0;

    flip = SDL_FLIP_NONE;

    mCurrentFrame = 0;

    mCharacterStatus = STAND_STILL;

    onGround = false;

    isShooting = false;
}