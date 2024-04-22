#pragma once

#include "../GameEngine/ImmobileGameObject.h"

class Block: public ImmobileGameObject
{
	friend class Camera; // camera calls the update function to change sizeScaled
public:
	Block(PointI position, Texture* texture);
	~Block();
	static const int getSize() { return size; }
	static int getSizeScaled() { return sizeScaled; }

	static void update(Camera* cam);
protected:
	static int sizeScaled;
	static const int size = SCREEN_WIDTH / 16;
};

