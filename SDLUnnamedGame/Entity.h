#pragma once
#include "./GameEngine/GameObject.h"

class Entity: GameObject
{
public:
	Entity(PointF position, PointI size, Texture* texture, int speed);

protected:
	const int speed; //blocks per second
	PointI destenation;
};

