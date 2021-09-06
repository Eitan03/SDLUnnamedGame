#pragma once
#include "../../Point.h"

class WorldGenerator
{
	/*
		an abstract class representing an interface to any world generator
	*/
public:
	virtual int getBlock(PointI pos) = 0;
};

