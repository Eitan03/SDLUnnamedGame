#include "ChunkManager.h"

ChunkManager::ChunkManager(Camera* camera)
{
	observer::setSubject((subject*)camera);
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
	std::cout << "unloaded" << std::endl;
	loadedChunks.erase(pos);
}

void ChunkManager::render()
{

	for (auto const& chunk : loadedChunks)
	{
		chunk.second->render();
	}
	
}

void ChunkManager::update(PointI cameraPosition, float scale)
{

	PointI cameraPos = (PointI)floor( (PointF)cameraPosition / Block::getSizeScaled() );
	PointI cameraChunkPos = (PointI)floor( (PointF)cameraPos / CHUNK_SIZE );
	
	updateLoadedChunks( chunksToLoad(cameraChunkPos, scale) );
	
}

std::set<PointI> ChunkManager::chunksToLoad(PointI cameraChunkPosition, float scale) {
	std::set<PointI> chunksToLoad;
	

	PointI screenSizeInChunks = PointI( (SCREEN_WIDTH / Block::getSizeScaled()) / 6, (SCREEN_HEIGHT / Block::getSizeScaled()) / 6 ) + 2;

	for (PointI chunkPosition = cameraChunkPosition; chunkPosition.x < cameraChunkPosition.x + screenSizeInChunks.x; (chunkPosition.x)++) {
		for (; chunkPosition.y < cameraChunkPosition.y + screenSizeInChunks.y;  (chunkPosition.y)++ ) {
			chunksToLoad.insert(chunkPosition);
		}
		chunkPosition.y = cameraChunkPosition.y;
		
	}

	return chunksToLoad;
}

void ChunkManager::updateLoadedChunks(std::set<PointI> chunksToLoad) {
	
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

void ChunkManager::update()
{
	subject* temp = observer::_subject;
	Camera* cam = dynamic_cast<Camera*>((this->_subject));
	this->update(cam->getLocation(), cam->getScale());
}
