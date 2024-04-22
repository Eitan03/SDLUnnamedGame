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

	// observer pattren
	void cameraMoved(Camera* cam);
private:
	void update(PointI cameraPosition, float scale);
	std::set<PointI> calculateChunksToLoad(PointI cameraChunkPosition, float scale);
	void updateLoadedChunks(std::set<PointI> chunksToLoad);

	std::map<PointI, std::unique_ptr<Chunk>> loadedChunks;


	PointI cameraChunkPos = PointI(-1, -1);
	float cameraScale = 0;
	bool shouldUpdateLoadedChunks(PointI newCameraPosition, float newScale) {
		return (newCameraPosition != this->cameraChunkPos) || (newScale != this->cameraScale);
	}

};

