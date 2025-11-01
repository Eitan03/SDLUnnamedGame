#pragma once
#include "ChunkDatabase.h"

class MockChunkDatabase
	: public ChunkDatabase
{
public:
	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> loadChunk(MGL::PointI pos) override;
	void saveChunk(MGL::PointI pos, std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS>& chunk) override;

	bool isChunkSaved(MGL::PointI chunkPos) override;
};

