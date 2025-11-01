#pragma once
#include "worldGenerator.h"
class GrassWorldGenerator :
    public WorldGenerator
{
public:
    GrassWorldGenerator();
    Block* generateBlock(MGL::PointI pos) override;
};

