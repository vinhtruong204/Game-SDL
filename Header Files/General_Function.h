#pragma once

#include "Window.h"
#include "Texture.h"
#include "Character.h"
#include "Sound.h"

bool init(Window &window);
bool loadMedia(SDL_Renderer *renderer, Texture &backgroundTexture, Character &player, Texture &tile, Sound &music);
void close(Window &window, Texture &backgroundTexture, Character &player, Texture &tile, Sound &music);