#include "ChunkManager.h"
#include <cmath>

ChunkManager::ChunkManager(Camera* camera)
{
}

ChunkManager::~ChunkManager()
{
	std::cout << "called chunk manager dsetructor" << std::endl;
}

void ChunkManager::loadChunk(MGL::PointI pos)
{
	std::unique_ptr<Chunk> chunk = std::make_unique<Chunk>(pos);
	loadedChunks.emplace(pos, std::move(chunk));
}

void ChunkManager::unloadChunk(MGL::PointI pos)
{
	loadedChunks.erase(pos);
}

void ChunkManager::render()
{

	for (auto const& chunk : loadedChunks)
	{
		chunk.second->render();
	}
	
}

void ChunkManager::update(MGL::PointI cameraPosition, float scale)
{

	MGL::PointI cameraPos = (MGL::PointI)floor( (MGL::PointF)cameraPosition / (float)Block::getSizeScaled() );
	MGL::PointI cameraChunkPos = (MGL::PointI)floor( (MGL::PointF)cameraPos / (float)CHUNK_SIZE );
	
	updateLoadedChunks( getChunksToLoad(cameraChunkPos, scale) );
	
}

std::set<MGL::PointI> ChunkManager::getChunksToLoad(MGL::PointI cameraChunkPosition, float scale) {
	// return std::set<MGL::PointI>{MGL::PointI{ 0, 0 }};
	std::set<MGL::PointI> chunksToLoad;
	

	// MGL::PointI screenSizeInChunks = MGL::PointI( (SCREEN_WIDTH / Block::getSizeScaled()) / CHUNK_SIZE, (SCREEN_HEIGHT / Block::getSizeScaled()) / CHUNK_SIZE ) + 2;
	MGL::PointI screenSizeInChunks = MGL::PointI( SCREEN_WIDTH / (Block::getSizeScaled() * CHUNK_SIZE), SCREEN_HEIGHT / (Block::getSizeScaled() * CHUNK_SIZE)) + 2;

	for (MGL::PointI chunkPosition = cameraChunkPosition; chunkPosition.x < cameraChunkPosition.x + screenSizeInChunks.x; (chunkPosition.x)++) {
		for (; chunkPosition.y < cameraChunkPosition.y + screenSizeInChunks.y;  (chunkPosition.y)++ ) {
			chunksToLoad.insert(chunkPosition);
		}
		chunkPosition.y = cameraChunkPosition.y;
		
	}

	return chunksToLoad;
}

void ChunkManager::updateLoadedChunks(std::set<MGL::PointI> chunksToLoad) {
	
	for (auto it = loadedChunks.begin(); it != loadedChunks.end() /* not hoisted */; /* no increment */)
	{
		if (chunksToLoad.find(it->first) == chunksToLoad.end())
		{
			it = loadedChunks.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it : chunksToLoad) {
		if (loadedChunks.find(it) == loadedChunks.end()) {
			this->loadChunk(it);
		}
	}
}

void ChunkManager::setBlock(ID blockId, int layer, MGL::PointI position)
{
	MGL::PointI chunkPos = MGL::PointI{ (int)std::floor(position.x / (CHUNK_SIZE * 1.0)), (int)std::floor(position.y / (CHUNK_SIZE * 1.0)) };
	MGL::PointI blockPos = position - (chunkPos * CHUNK_SIZE);
	if (loadedChunks.find(chunkPos) == loadedChunks.end()) {
		loadChunk(chunkPos);
	}
	loadedChunks[chunkPos]->setBlock(blockId, layer, blockPos);
}

// TODO only calc if needed
void ChunkManager::cameraMoved(Camera* cam)
{
	this->update(cam->getLocation(), cam->getScale());
}

