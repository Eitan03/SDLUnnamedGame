#include "Block.h"

int Block::sizeScaled = Block::getSize();
Camera* Block::cam = nullptr;

Block::Block(PointI position, Texture* texture)
	: GameObject({ (float)(position.x), (float)(position.y) }, { size, size }, texture)
{
}

Block::~Block()
{
}

void Block::update()
{
	sizeScaled =  cam->applyScale(size);
}
