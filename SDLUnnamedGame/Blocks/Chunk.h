#pragma once
#include <vector>
#include <assert.h>
#include <fstream>

#include "Block.h"
#include "../Globals.h"
#define CHUNK_SIZE 6
#define LAYERS 3
/*
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

	void renderLayer(unsigned int layer);
	void renderLayers(unsigned int layers[], unsigned int size); //size is the size of the layers array, will firstly render the frist layer in the array, then second etc.
	void render(); //renders all layers

	PointI getPosition(void) const { return this->position; }

	static Texture** blockTextures;
	Block* blocks[LAYERS][CHUNK_SIZE][CHUNK_SIZE];
protected:
	
	void loadFromFile(const char* path);
	Block* createBlock(int n, PointI position); // takes the number from the file and returns a block
	void createChunk();

	PointI position;
};

