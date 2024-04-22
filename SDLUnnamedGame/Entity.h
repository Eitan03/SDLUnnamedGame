#pragma once
#include "./GameEngine/MobileGameObject.h"

class Entity: MobileGameObject
{
public:
	Entity(PointF position, PointI size, Texture* texture, int speed);

protected:
	const int speed; //blocks per second
	PointI destenation;
};

