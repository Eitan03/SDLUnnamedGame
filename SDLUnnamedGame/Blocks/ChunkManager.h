#pragma once
#include <map>

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
	std::map<long long int, Chunk*> loadedChunks;
};

