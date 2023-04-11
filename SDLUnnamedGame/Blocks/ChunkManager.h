#pragma once
#include <map>
#include <set>

#include "Chunk.h"
#include "../Utilities.h"

class ChunkManager
{
public:
	ChunkManager(Camera* camera);
	~ChunkManager();
	void loadChunk(PointI pos);
	void unloadChunk(PointI pos);

	void render();

	void update(PointI cameraPosition, float scale);
	std::set<PointI> chunksToLoad(PointI cameraChunkPosition, float scale);
	void updateLoadedChunks(std::set<PointI> chunksToLoad);

	// observer pattren
	void cameraMoved(Camera* cam);
private:
	std::map<PointI, std::unique_ptr<Chunk>> loadedChunks;
};

