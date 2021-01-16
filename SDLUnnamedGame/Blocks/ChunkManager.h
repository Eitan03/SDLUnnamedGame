#pragma once
#include <vector>

#include "Chunk.h"

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();
	void loadChunk(PointI pos);
	void unloadChunk(PointI pos);

	void render();

private:
	std::vector<Chunk> loadedChunks;
};

