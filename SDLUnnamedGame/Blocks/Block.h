#pragma once

#include "../GameEngine/GameObject.h"
#include <MyGraphicsLibrary/Texture.h>
#include <MyGraphicsLibrary/Point.h>

class Block: public GameObject
{
	friend class Camera; //camera calls the update function to change sizeScaled
public:
	Block(MGL::PointI position, std::shared_ptr<MGL::Texture> texture, int blockId);
	~Block();
	static const int getSize() { return size; }
	static int getSizeScaled() { return sizeScaled; }

	static void update(Camera* cam);
	const int BlockId;
protected:
	static int sizeScaled;
	static const int size = SCREEN_WIDTH / 16;
};

