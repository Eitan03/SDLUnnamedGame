#include "Block.h"
#include "../Globals.h"

int Block::sizeScaled = Block::getSize();

Block::Block(MGL::PointI position, std::shared_ptr<MGL::Texture> texture)
	: ImmobileGameObject(position, MGL::PointI{ size, size }, texture)
{
}

void Block::update(Camera* cam)
{
	sizeScaled =  cam->applyScale(Block::size);
}
