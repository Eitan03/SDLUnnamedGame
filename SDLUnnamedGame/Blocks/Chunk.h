#pragma once
#include <vector>
#include <array>
#include <MyGraphicsLibrary/TargetTexture.h>
#include "../GameEngine/ImmobileGameObject.h"

#include "Block.h"
#include "Generators/WorldGenerators/GrassWorldGenerator.h"
#include "Generators/WorldGenerators/PossionDiscWorldGenerator.h"
#define CHUNK_SIZE 8
#define LAYERS 3
/*
* To Be Done -
	3 layers-
	0 underground
	1 ground
	2 everything else (trees, flowers, etc.)
*/

class Chunk : public ImmobileGameObject
{
public:
	Chunk(MGL::PointI position);
	~Chunk();

	void render() override; //renders all layers

	static void SetRenderer(std::shared_ptr<MGL::Renderer> renderer) { Chunk::renderer = renderer; }

	void setBlock(ID blockId, int layer, MGL::PointI position);
protected:

	std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> loadBlockIdsFromFile(const char* path);
	void loadChunk();
	std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> createChunk(const char* path);
	void saveChunk(const char* path);

	std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> blocks;

	static std::unique_ptr<WorldGenerator> worldGenerator;
	static std::shared_ptr<MGL::Renderer> renderer; // used for the creation of the chunk textures

#ifndef NDEBUG // if debug
private:
	void printLayer(int layerNum);
#endif

};

