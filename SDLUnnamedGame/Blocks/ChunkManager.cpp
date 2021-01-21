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
	loadedChunks.emplace(mapPosition, chunk);
}

void ChunkManager::unloadChunk(PointI pos)
{
	long long int mapPosition = 0;
	mapPosition = pos.x + ((long long int)pos.y << 32);

	Chunk* chunk = loadedChunks[mapPosition];
	delete chunk;
	loadedChunks.erase(mapPosition);

}

void ChunkManager::render()
{
	for (std::map<long long int, Chunk*>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++)
	{
		if ((it->second->blocks)[0][0] == nullptr) {
			assert(false);
		}
		std::cout << it->second->getPosition() << std::endl;

		it->second->render();
	}
}

void ChunkManager::update(PointI cameraPosition, float Scale)
{
	for (std::map<long long int, Chunk*>::iterator it = loadedChunks.begin(); it != loadedChunks.end(); it++)
	{
		delete it->second;
	}
	loadedChunks.clear();

	this->loadChunk( floor(cameraPosition / (float)16) );
}
