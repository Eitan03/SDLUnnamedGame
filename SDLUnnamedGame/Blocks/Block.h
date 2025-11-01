#pragma once

#include "../GameEngine/ImmobileGameObject.h"
#include "../Globals.h"

class Block: public ImmobileGameObject
{
public:

	Block(MGL::PointI position, BlockType type);

	const BlockType getType() { return type; }


	static const int getSize() { return size; }
	static int getSizeScaled() { return sizeScaled; }

	static void onCameraChange(Camera* cam);

	static Block* createEmptyBlock() { return new Block({ 0,0 }, BlockType::Unkown); }
protected:
	virtual void update() {}; // TODO take nearby blocks, and make sure to update in the following tick to avoid infinite loop
	static int sizeScaled;
	static const int size = SCREEN_WIDTH / 16;
	BlockType type;
};
