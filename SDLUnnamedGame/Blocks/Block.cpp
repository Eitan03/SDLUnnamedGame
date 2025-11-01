#include "Block.h"
#include "../Globals.h"

int Block::sizeScaled = Block::getSize();

Block::Block(MGL::PointI position, BlockType type)
	: ImmobileGameObject(position, MGL::PointI{ size, size }, nullptr), type(type)
{
	this->texture = blockTextures[type];
}

void Block::onCameraChange(Camera* cam)
{
	sizeScaled =  cam->applyScale(Block::size);
}
