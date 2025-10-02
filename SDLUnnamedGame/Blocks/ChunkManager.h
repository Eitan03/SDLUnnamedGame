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
	void loadChunk(MGL::PointI pos);
	void unloadChunk(MGL::PointI pos);

	void setBlock(ID blockId, int layer, MGL::PointI position);

	void render();

	// observer pattren
	void cameraMoved(Camera* cam);
private:
	void update(MGL::PointI cameraPosition, float scale);
	std::set<MGL::PointI> calculateChunksToLoad(MGL::PointI cameraChunkPosition, float scale);
	void updateLoadedChunks(std::set<MGL::PointI> chunksToLoad);

	std::map<MGL::PointI, std::unique_ptr<Chunk>> loadedChunks;


	MGL::PointI cameraChunkPos = MGL::PointI(-1, -1);
	float cameraScale = 0;
	bool shouldUpdateLoadedChunks(MGL::PointI newCameraPosition, float newScale) {
		return (newCameraPosition != this->cameraChunkPos) || (newScale != this->cameraScale);
	}

};

