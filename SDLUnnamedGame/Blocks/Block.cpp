#include "Block.h"



Block::Block(PointI position, std::shared_ptr<Texture> texture)
	: GameObject({ (float)(position.x), (float)(position.y) }, { Globals::getInstance()->BlockSize, Globals::getInstance()->BlockSize }, texture)
{
}

Block::~Block()
{
}
