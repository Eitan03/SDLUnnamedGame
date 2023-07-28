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

	void render();

	void update(MGL::PointI cameraPosition, float scale);
	std::set<MGL::PointI> getChunksToLoad(MGL::PointI cameraChunkPosition, float scale);
	void updateLoadedChunks(std::set<MGL::PointI> chunksToLoad);

	void setBlock(std::unique_ptr<Block> block, int layer);

	// observer pattren
	void cameraMoved(Camera* cam);
private:
	std::map<MGL::PointI, std::unique_ptr<Chunk>> loadedChunks;
};

