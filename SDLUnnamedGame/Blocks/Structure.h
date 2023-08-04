#pragma once
#include <vector>
#include <memory>
#include "Block.h"
#include "Chunk.h"

class Structure
{
public:
	Structure();


	static Structure* loadFromFile(const char* path);
protected:
	static std::array<std::vector<std::vector<int>>, LAYERS> loadBlocksIdFromFile(const char* path);
	std::array<std::vector<std::vector<std::unique_ptr<Block>>>, LAYERS> blocks;
};

