#pragma once
#include <vector>
#include <fstream>

#include "Block.h"
#define CHUNK_SIZE 6
/*
* To Be Done -
	3 layers-
	0 underground
	1 ground
	2 everything else (trees, flowers, etc.)
*/

class Chunk
{
public:
	Chunk(PointI position);
	~Chunk();

	void render(); //renders all layers

	PointI getPosition(void) const { return this->position; }

protected:
	
	void loadFromFile(const char* path);
	Block* createBlock(int textureNumber, PointI position); // takes the number from the file and returns a block
	void createChunk();

	PointI position;
	Block* blocks[CHUNK_SIZE][CHUNK_SIZE];
};

