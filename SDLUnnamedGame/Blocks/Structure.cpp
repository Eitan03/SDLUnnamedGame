#include "Structure.h"
#include <fstream>
#include <map>

std::array<std::vector<std::vector<int>>, LAYERS> Structure::loadBlocksIdFromFile(const char* path)
{
    std::array<std::vector<std::vector<int>>, LAYERS> blocksId{};
	std::ifstream ifStream;
	ifStream.open(path);

	int currentLayer = 0;
	int row = 0;
	int column = 0;

	auto texturesToDraw = std::map<std::shared_ptr<MGL::Texture>, std::vector<MGL::PointI>>();

	std::string line;
	while (getline(ifStream, line)) {
		if (!line.compare("")) continue;

		if (line.find("layer ") == 0) { //if the line starts with "layer "
			currentLayer = std::stoi(line.substr(5, line.size() - 1));
			row = 0;
			column = 0;
			continue;
		}
		
		while (line != "" && line.find(",") != std::string::npos) {
			if (row > CHUNK_SIZE || column > CHUNK_SIZE || currentLayer < 0 || currentLayer > LAYERS) {
				throw GameEngineException("either layer error, or row or column too big");
			}
			int blockTypeID = std::stoi(line.substr(0, line.find(",")));
			blocksId[currentLayer][row][column] = blockTypeID;
			row++;
			line = line.substr(line.find(",") + 1);
		}
		row = 0;
		column++;
	}
	return blocksId;
}
