#include "StructureGenerator.h"
#include <fstream>
#include <map>
#include "../../Globals.h"

StructureGenerator::StructureGenerator(std::weak_ptr<ChunkManager> chunkManager, std::string name, std::array<std::vector<std::vector<int>>, LAYERS> blocks): 
	name(name), chunkManager(chunkManager),
	blocks(blocks)
{
}

StructureGenerator* StructureGenerator::loadFromFile(const char* path, std::weak_ptr<ChunkManager> chunkManager, std::string name)
{

	auto blocksId = loadBlocksIdFromFile(path);

	StructureGenerator* structure = new StructureGenerator(chunkManager, name, blocksId);

	return structure;
}

void StructureGenerator::place(MGL::PointI position)
{
	for (int layer = 0; layer < LAYERS; layer++) {
		if (this->blocks[layer].size() == 0) {
			continue;
		}

		for (int row = 0; row < this->blocks[layer].size(); row++) {
			for (int col = 0; col < this->blocks[layer][0].size(); col++) {
				if (this->blocks[layer][row][col] != -1) {
					if (auto chunkManagerPtr = this->chunkManager.lock()) {
						auto temp = createBlock(this->blocks[layer][row][col], position + MGL::PointI{ row, col });
						chunkManagerPtr->setBlock(
							std::move(temp),
							layer
						);
					}
				}
			}
		}
	}
}

std::array<std::vector<std::vector<int>>, LAYERS> StructureGenerator::loadBlocksIdFromFile(const char* path)
{
	std::array<std::vector<std::vector<int>>, LAYERS> blocksId{
			std::vector<std::vector<int>>{},
			std::vector<std::vector<int>>{},
			std::vector<std::vector<int>>{}
		};
	std::ifstream ifStream;
	ifStream.open(path);

	int size[2] = { -1, -1 };
	int currentLayer = -1;
	int row = 0;
	int column = 0;


	std::string line;
	while (getline(ifStream, line)) {
		if (!line.compare("")) continue;

		if (line.find("size ") == 0) { //if the line starts with "layer "
			if (size[0] != -1) {
				throw GameEngineException("size cant be specified twice!");
			}

			line = line.substr(5, line.size() - 1);
			auto delimPos = line.find("x");
			size[0] = std::stoi(line.substr(0, delimPos));
			size[1] = std::stoi(line.substr(delimPos + 1));
			continue;
		}

		if (line.find("layer ") == 0) { //if the line starts with "layer "
			currentLayer = std::stoi(line.substr(5, line.size() - 1));
			blocksId[currentLayer] = std::vector<std::vector<int>>(size[0], std::vector<int>(size[1], -1));

			row = 0;
			column = 0;
			continue;
		}
		
		while (line != "") {
			if (row > CHUNK_SIZE || column > CHUNK_SIZE || currentLayer < 0 || currentLayer > LAYERS) {
				throw GameEngineException("either layer error, or row or column too big");
			}
			int blockTypeID = std::stoi(line.substr(0, line.find(",")));
			blocksId[currentLayer][row][column] = blockTypeID;
			row++;
			auto nextDelim = line.find(",");
			if (nextDelim == std::string::npos) {
				break;
			}
			line = line.substr(line.find(",") + 1);
		}
		row = 0;
		column++;
	}

	return blocksId;
}
