#pragma once
#include <map>
#include <set>

#include "Chunk.h"
#include "../Pattrens/observer.h"
#include "../Utilities.h"

class ChunkManager: observer
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
	void update() override;
private:
	std::map<PointI, std::unique_ptr<Chunk>> loadedChunks;
};

