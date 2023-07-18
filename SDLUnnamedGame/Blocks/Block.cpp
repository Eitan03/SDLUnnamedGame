#include "Block.h"

int Block::sizeScaled = Block::getSize();

Block::Block(MGL::PointI position, std::shared_ptr<MGL::Texture> texture, int blockId)
	: Gridable(position, { Block::size, Block::size }, texture), BlockId(blockId)
{
}

Block::~Block()
{
}

void Block::update(Camera* cam)
{
	sizeScaled =  cam->applyScale(Block::size);
}
