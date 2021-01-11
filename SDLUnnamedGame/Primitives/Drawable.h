#pragma once
#include <SDL.h>

class Drawable
{
public:
	void virtual renderABS(int x, int y) = 0; //in screen position and not wolrd position, in origin al size (without scale)
};

