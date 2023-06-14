#pragma once
#include <iostream>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include <MyGraphicsLibrary/Texture.h>

struct Colors {
    const MGL::Color White;
    const MGL::Color Black;
};
enum BlockTypes {
    Grass,
    Sand,
    Size
};