#pragma once
#include <vector>
#include <array>
#include <MyGraphicsLibrary/TargetTexture.h>

#include "Block.h"
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

class Chunk: public Gridable
{
public:
	Chunk(MGL::PointI position);
	~Chunk();

	void render() override; //renders all layers

	static void SetRenderer(std::shared_ptr<MGL::Renderer> renderer) { Chunk::renderer = renderer; }

	void setBlock(std::unique_ptr<Block> block, int layer, MGL::PointI position);
protected:
	
	std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> loadBlockIdsFromFile(const char* path);
	void loadChunk();
	std::unique_ptr<Block> createBlock(int textureNumber, MGL::PointI position); // takes the number from the file and returns a block
	std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> createChunk(const char* path);
	void saveChunk(const char* path);

	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> blocks;

	static std::unique_ptr<WorldGenerator> worldGenerator;
	static std::shared_ptr<MGL::Renderer> renderer; // used for the creating of the chunk textures

#ifndef NDEBUG // if debug
private:
	void printLayer(int layerNum);
#endif

};

