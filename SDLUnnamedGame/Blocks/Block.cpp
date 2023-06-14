#include "Block.h"

int Block::sizeScaled = Block::getSize();

Block::Block(MGL::PointI position, std::shared_ptr<MGL::Texture> texture)
	: GameObject(MGL::PointF(position), { size, size }, texture)
{
}

Block::~Block()
{
}

void Block::update(Camera* cam)
{
	sizeScaled =  cam->applyScale(size);
}
