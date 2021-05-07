#pragma once

#include "../GameEngine/GameObject.h"

// this is not an obersver becuase the size and sizeScaled are static
class Block: public GameObject
{
	friend class Camera; //camera calls the update function to change sizeScaled
public:
	Block(PointI position, Texture* texture);
	~Block();
	static const int getSize() { return size; }
	static int getSizeScaled() { return sizeScaled; }

protected:
	static void update();
	static int sizeScaled;
	static const int size = SCREEN_WIDTH / 16;
	static Camera* cam;
};

