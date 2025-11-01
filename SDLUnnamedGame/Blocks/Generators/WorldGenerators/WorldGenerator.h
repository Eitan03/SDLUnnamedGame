#pragma once
#include <MyGraphicsLibrary/Point.h>
#include "../../Block.h"

class WorldGenerator
{
	/*
		an abstract class representing an interface to any world generator of blocks
	*/
public:
	// generates a HEAP ALLOCATED block
	virtual Block* generateBlock(MGL::PointI pos) = 0;
};

