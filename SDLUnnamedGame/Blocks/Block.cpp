#include "Block.h"
#include "../Globals.h"

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

std::unique_ptr<Block> createBlock(int textureNumber, MGL::PointI position)
{
	return std::make_unique<Block>(position, blockTextures[textureNumber], textureNumber);
}
