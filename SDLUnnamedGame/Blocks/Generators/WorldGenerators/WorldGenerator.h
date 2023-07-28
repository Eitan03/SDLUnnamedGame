#pragma once
#include <MyGraphicsLibrary/Point.h>

class WorldGenerator
{
	/*
		an abstract class representing an interface to any world generator
	*/
public:
	virtual int getBlock(MGL::PointI pos) = 0;
};

