#include "grassWorldGenerator.h"
#include "../../../Globals.h"

GrassWorldGenerator::GrassWorldGenerator()
{
}

int GrassWorldGenerator::getBlock(MGL::PointI pos)
{
    return BlockTypes::Grass;
}
