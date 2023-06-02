#pragma once
#include <vector>
#include <fstream>

#include "Block.h"
#include "../Primitives/TargetTexture.h"
#include "worldGenerators/GrassWorldGenerator.h"
#include "worldGenerators/PossionDiscWorldGenerator.h"
#define CHUNK_SIZE 8
#define LAYERS 3
/*
* To Be Done -
	3 layers-
	0 underground
	1 ground
	2 everything else (trees, flowers, etc.)
*/

class Chunk: GameObject
{
public:
	Chunk(PointI position);
	~Chunk();

	void render(); //renders all layers

	static void SetRenderer(std::shared_ptr<Renderer> renderer) { Chunk::renderer = renderer; }
protected:
	
	void loadFromFile(const char* path);
	Block* createBlock(int textureNumber, PointI position); // takes the number from the file and returns a block
	void createChunk(const char* path);

	Block* blocks[LAYERS][CHUNK_SIZE][CHUNK_SIZE];

	static WorldGenerator* const worldGenerator;
	static std::shared_ptr<Renderer> renderer; // used for the creating of the chunk textures
};

