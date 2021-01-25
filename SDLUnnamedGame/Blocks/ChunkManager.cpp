#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
	
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::loadChunk(PointI pos)
{
	Chunk* chunk = new Chunk(pos);
	loadedChunks.emplace(pos, chunk);
}

void ChunkManager::unloadChunk(PointI pos)
{
	loadedChunks.erase(pos);
}

void ChunkManager::render()
{
	for (auto& chunk : loadedChunks) {
		chunk.second->render();
	}
	
}

void ChunkManager::update(PointI cameraPosition, float Scale)
{
	/*
	std::set<PointI> needToBeLoaded;
	needToBeLoaded.insert((PointI) floor(cameraPosition / (float)Globals::getInstance()->camera.applyScale(Globals::getInstance()->BlockSize)));
	std::cout << (PointI)floor(cameraPosition / (float)Globals::getInstance()->camera.applyScale(Globals::getInstance()->BlockSize)) << std::endl;

	std::map<PointI, Chunk*>::iterator itr = loadedChunks.begin();
	while (itr != loadedChunks.end()) {
		if (needToBeLoaded.find(itr->first) == needToBeLoaded.end()) {
			itr = loadedChunks.erase(itr);
		}
		else {
			++itr;
		}
	}
	*/
}
