#pragma once

#include <MyGraphicsLibrary/Point.h>
#include <MyGraphicsLibrary/Texture.h>
#include "../Utilities.h"
#include "../Globals.h"
#include "../GameEngine/Camera.h"

static class Block
{
	friend class Camera; //camera calls the update function to change sizeScaled
public:
	static const int getSize() { return size; }
	static int getSizeScaled() { return sizeScaled; }

	static void update(Camera* cam);
	static const std::shared_ptr<MGL::Texture> getTexture(ID blockId) { return blockTextures[blockId]; }; // TODO maybe weak ptr?
protected:
	static int sizeScaled;
	static const int size = SCREEN_WIDTH / 16;
};
