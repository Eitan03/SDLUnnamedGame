#pragma once

#include "../GameEngine/ImmobileGameObject.h"
#include "../Globals.h"

class Block: public ImmobileGameObject
{
	friend class Camera; // camera calls the update function to change sizeScaled
public:

	Block(MGL::PointI position, std::shared_ptr<MGL::Texture> texture);

	static const int getSize() { return size; }
	static int getSizeScaled() { return sizeScaled; }

	static void update(Camera* cam);
	static const std::shared_ptr<MGL::Texture> getTexture(ID blockId) { return blockTextures[blockId]; }; // TODO maybe weak ptr?
protected:
	static int sizeScaled;
	static const int size = SCREEN_WIDTH / 16;
};
