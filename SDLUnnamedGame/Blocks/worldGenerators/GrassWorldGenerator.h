#pragma once
#include "worldGenerator.h"
class GrassWorldGenerator :
    public WorldGenerator
{
public:
    GrassWorldGenerator();
    int getBlock(PointI pos) override;
};

