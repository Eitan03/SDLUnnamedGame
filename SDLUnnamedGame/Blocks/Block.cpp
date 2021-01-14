#include "Block.h"



Block::Block(PointI position, Texture* texture)
	: GameObject({ (float)(position.x), (float)(position.y) }, { Globals::getInstance()->BlockSize, Globals::getInstance()->BlockSize }, texture)
{
}

Block::~Block()
{
}
