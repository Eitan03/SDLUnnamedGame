#pragma once
#include <map>
#include <set>

#include "Chunk.h"
#include "../Pattrens/observer.h"

class ChunkManager: observer
{
public:
	ChunkManager(Camera* camera);
	~ChunkManager();
	void loadChunk(PointI pos);
	void unloadChunk(PointI pos);

	void render();
	void update(PointI cameraPosition, float Scale);

	// bserver pattren
	void update() override;
private:
	std::map<long long int, Chunk*> loadedChunks;
};

