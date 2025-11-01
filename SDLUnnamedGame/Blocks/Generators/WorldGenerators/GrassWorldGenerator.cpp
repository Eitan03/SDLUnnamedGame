#include "grassWorldGenerator.h"
#include "../../../Globals.h"

GrassWorldGenerator::GrassWorldGenerator()
{
}

Block* GrassWorldGenerator::generateBlock(MGL::PointI pos)
{
		return new Block(pos, BlockType::Grass);
}
