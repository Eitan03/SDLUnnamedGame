#include "Block.h"
#include "../Globals.h"

int Block::sizeScaled = Block::getSize();

void Block::update(Camera* cam)
{
	sizeScaled =  cam->applyScale(Block::size);
}
