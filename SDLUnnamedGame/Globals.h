#pragma once
#include <iostream>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include "./GameEngine/Camera.h"
#include <MyGraphicsLibrary/Texture.h>

#define BLOCK_TEXTURE_SIZE 250

struct Colors {
    const MGL::Color White;
    const MGL::Color Black;
};
enum BlockTypes {
    Null = 0,
    Grass,
    Sand,
    Log,
    Leaf,
    Size
};

extern std::shared_ptr<MGL::Texture> blockTextures[BlockTypes::Size];