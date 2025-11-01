#pragma once
#include <vector>
#include <array>
#include <memory>
#include <MyGraphicsLibrary/TargetTexture.h>

#include "../GameEngine/ImmobileGameObject.h"
#include "../Globals.h"

#include "Generators/WorldGenerators/WorldGenerator.h"
#include "ChunkDatabase/ChunkDatabase.h"
#include "Block.h"


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
	static void SetDatabase(std::unique_ptr<ChunkDatabase> chunkDatabase) { Chunk::chunkDatabase = std::move(chunkDatabase); }
	static void SetWorldGenerator(std::unique_ptr<WorldGenerator> worldGenerator) { Chunk::worldGenerator = std::move(worldGenerator); }

	void setBlock(std::unique_ptr<Block> block, int layer, MGL::PointI position);
protected:

	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> createChunk();
	void loadChunk();

	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> blocks;

	static std::unique_ptr<WorldGenerator> worldGenerator;

private:
#ifndef NDEBUG // if debug
	void printLayer(int layerNum);
#endif
	static std::shared_ptr<MGL::Renderer> renderer; // used for the creation of the chunk textures
	static std::unique_ptr<ChunkDatabase> chunkDatabase;

	void _drawToChunk(std::shared_ptr<MGL::Texture> texture, MGL::PointI position);

};

