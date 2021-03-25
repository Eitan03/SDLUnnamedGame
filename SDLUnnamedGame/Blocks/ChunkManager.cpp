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
	long long int position = (long long int)pos.x << 32 | pos.y;
	loadedChunks.emplace(position, chunk);
}

void ChunkManager::unloadChunk(PointI pos)
{
	long long int position = (long long int)pos.x << 32 | pos.y;
	loadedChunks.erase(position);
}

void ChunkManager::render()
{
	loadedChunks[0].get()->render();
	//for (auto chunk = loadedChunks.cbegin(); chunk != loadedChunks.cend() /* not hoisted */; chunk++/* no increment */) {
	//	chunk->second->render();
	//}
	
}

void ChunkManager::update(PointI cameraPosition, float Scale)
{

	PointI cameraPos = (PointI)floor( (PointF)cameraPosition / Block::getSizeScaled() );
	PointI cameraChunkPos = cameraPos / CHUNK_SIZE;
	std::cout << cameraPosition << std::endl;
	//std::cout << cameraPos << std::endl;
	//std::cout << cameraChunkPos << std::endl;
	loadedChunks[0] = std::make_unique<Chunk>(cameraChunkPos + PointI(1, 1));

	/*
	std::set<long long int> needToBeLoaded;
	PointI cameraChunk = (PointI)floor( (cameraPosition / ( (float)Globals::getInstance()->camera.applyScale(Globals::getInstance()->BlockSize)) / 16) );
	long long int cameraChunkPos = (long long int)cameraChunk.x << 32 | cameraChunk.y;;
	needToBeLoaded.insert(cameraChunkPos);
	std::cout << cameraChunk << std::endl;

	for (auto it = loadedChunks.cbegin(); it != loadedChunks.cend() /* not hoisted *; /* no increment *)
	{
		if (needToBeLoaded.find(it->first) == needToBeLoaded.end())
		{
			//loadedChunks.erase(it++);    // or "it = m.erase(it)" since C++11
			it = loadedChunks.erase(it);
		}
		else
		{
			++it;
		}
	}
	*/

}

void ChunkManager::update()
{
	subject* temp = observer::_subject;
	Camera* cam = dynamic_cast<Camera*>((this->_subject));
	this->update(cam->getLocation(), cam->getScale());
}
