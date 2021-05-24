#include "Block.h"

int Block::sizeScaled = Block::getSize();
Camera* Block::cam = nullptr;

Block::Block(PointI position, Texture* texture)
	: GameObject(PointF(position), { size, size }, texture)
{
}

Block::~Block()
{
}

void Block::update()
{
	sizeScaled =  cam->applyScale(size);
}
