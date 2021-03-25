#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include "./Primitives/Texture.h"

struct Colors {
    const Color White;
    const Color Black;
};
enum BlockTypes {
    Grass,
    Sand,
    Size
};