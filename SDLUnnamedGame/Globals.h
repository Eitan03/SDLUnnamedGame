#pragma once
#include <iostream>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include <MyGraphicsLibrary/Texture.h>

#define BLOCK_TEXTURE_SIZE 250

struct Colors {
    const MGL::Color White;
    const MGL::Color Black;
};
enum BlockTypes {
    Grass,
    Sand,
    Size
};