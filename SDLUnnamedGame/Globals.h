#pragma once
#include <iostream>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include <MyGraphicsLibrary/Texture.h>

#define BLOCK_TEXTURE_SIZE 250

#define CHUNK_SIZE 8
#define LAYERS 3

struct Colors {
    const MGL::Color White;
    const MGL::Color Black;
};
enum BlockType {
    Null = 0,
    Grass,
    Sand,
    Log,
    Leaf,
    Size,
    Unkown = -1
};

extern std::shared_ptr<MGL::Texture> blockTextures[BlockType::Size];