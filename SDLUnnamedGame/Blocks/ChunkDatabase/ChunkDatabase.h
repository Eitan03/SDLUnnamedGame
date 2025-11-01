#pragma once
#include <array>
#include <memory>
#include "../Block.h"
#include "../../Globals.h"

class ChunkDatabase
{
public:
	virtual std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> loadChunk(MGL::PointI pos) = 0;
	virtual void saveChunk( MGL::PointI pos, std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS>& chunk) = 0;

	virtual bool isChunkSaved(MGL::PointI chunkPos) = 0;
};

