#include "Block.h"

int Block::sizeScaled = Block::getSize();

Block::Block(PointI position, Texture* texture)
	: GameObject(PointF(position), { size, size }, texture)
{
}

Block::~Block()
{
}

void Block::update(Camera* cam)
{
	sizeScaled =  cam->applyScale(size);
}
