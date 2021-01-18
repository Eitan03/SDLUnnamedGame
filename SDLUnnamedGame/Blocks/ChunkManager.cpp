#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::loadChunk(PointI pos)
{ //TODO cehck if exists
	long long int mapPosition = 0;
	mapPosition = pos.x + ((long long int)pos.y << 32);
	Chunk* chunk = new Chunk(pos);
	chunk->load();
	loadedChunks.emplace(mapPosition, chunk);
}

void ChunkManager::unloadChunk(PointI pos)
{
	long long int mapPosition = 0;
	mapPosition = pos.x + ((long long int)pos.y << 32);

	Chunk* chunk = loadedChunks[mapPosition];
	chunk->unload();
	delete chunk;
	loadedChunks.erase(mapPosition);

}

void ChunkManager::render()
{
	for (auto const& chunk : loadedChunks) {
		chunk.second->render();
	}
}

void ChunkManager::update(PointI cameraPosition, float Scale)
{
}
