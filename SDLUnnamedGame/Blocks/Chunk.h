#pragma once
#include <vector>
#include <assert.h>

#include "../tinyxml2/tinyxml2.h"
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { printf("Error: %i\n", a_eResult); assert(false); }
#endif

#include "Block.h"
#include "../Globals.h"
#define CHUNK_SIZE 6

class Chunk
{
public:
	Chunk(PointI position);
	~Chunk();

	void load();
	void unload();
	

	void render();

	static Texture** blockTextures;
protected:
	int loadFromFile(std::string path);
	void createChunk();

	Block* blocks[CHUNK_SIZE][CHUNK_SIZE];
	PointI position;
};

