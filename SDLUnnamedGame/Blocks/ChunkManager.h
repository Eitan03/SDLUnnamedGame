#pragma once
#include <map>
#include <set>

#include "Chunk.h"

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();
	void loadChunk(PointI pos);
	void unloadChunk(PointI pos);

	void render();
	void update(PointI cameraPosition, float Scale);
private:
	std::map<PointI, Chunk*> loadedChunks;
};

