#pragma once
#include <vector>
#include <memory>
#include "../ChunkManager.h"

class StructureGenerator
{
public:
	StructureGenerator(std::weak_ptr<ChunkManager> chunkManager, std::string name, std::array<std::vector<std::vector<int>>, LAYERS> blocks);

	
	// Warning! returns an heap object!
	static StructureGenerator* loadFromFile(const char* path, std::weak_ptr<ChunkManager> chunkManager, std::string name);
	std::string getName() { return name; };

	void place(MGL::PointI position);
protected:
	std::array<std::vector<std::vector<int>>, LAYERS> blocks;
	std::string name;
	std::weak_ptr<ChunkManager> chunkManager;

	static std::array<std::vector<std::vector<int>>, LAYERS> loadBlocksIdFromFile(const char* path);
};

