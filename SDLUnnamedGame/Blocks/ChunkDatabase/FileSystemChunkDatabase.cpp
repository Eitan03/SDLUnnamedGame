#include "FileSystemChunkDatabase.h"

#include <sstream>
#include <fstream>

FileSystemChunkDatabase::FileSystemChunkDatabase(std::string chunksFolder)
{
	if (chunksFolder.empty()) {
		throw std::invalid_argument("chunksFolder cannot be empty");
	}

	if (chunksFolder.back() != '/' && chunksFolder.back() != '\\') {
		chunksFolder += '/';
	}
	this->chunksFolder = chunksFolder;
}

std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> FileSystemChunkDatabase::loadChunk(MGL::PointI pos)
{
	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};
	std::ifstream ifStream;
	ifStream.open(this->getChunkFilePath(pos));
	if (!ifStream.good())
	{
		throw GameEngineException(std::string("Failed to open file : ") + this->getChunkFilePath(pos));
	}

	int currentLayer = -1;
	int row = 0;
	int column = 0;


	std::string line;
	while (getline(ifStream, line)) {
		if (!line.compare("")) continue;

		if (line.find("layer ") == 0) { //if the line starts with "layer "
			currentLayer = std::stoi(line.substr(5, line.size() - 1));
			row = 0;
			column = 0;
			continue;
		}

		std::istringstream lineStream(line);
		std::string numberAsString;
		while (getline(lineStream, numberAsString, ',')) {
			if (row > CHUNK_SIZE || column > CHUNK_SIZE || currentLayer < 0 || currentLayer > LAYERS) {
				throw GameEngineException("either layer error, or row or column too big");
			}
			int blockTypeID = std::stoi(numberAsString);
			if (static_cast<BlockType>(blockTypeID) != BlockType::Null) {
				chunkData[currentLayer][row][column] = std::make_unique<Block>(pos * CHUNK_SIZE + MGL::PointI{row, column}, static_cast<BlockType>(blockTypeID));
			}
			row++;
		}
		row = 0;
		column++;
	}
	return chunkData;
}

void FileSystemChunkDatabase::saveChunk(MGL::PointI pos, std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS>& chunk)
{
	std::string path = this->getChunkFilePath(pos);
	std::cout << "saving " << path << std::endl;
	std::ofstream ofStream;
	ofStream.open(path);

	if (!ofStream.is_open())
	{
		throw GameEngineException(std::string("Failed to open file : ") + path);
	}

	for (int layer = 0; layer < LAYERS; layer++) {
		ofStream << "layer " << std::to_string(layer) << ":" << "\n";
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				if (chunk[layer][j][i] != nullptr) {
					ofStream << std::to_string(chunk[layer][j][i]->getType()) + ",";
				}
				else {
					ofStream << std::to_string(BlockType::Null) + ",";
				}
			}
			ofStream << "\n";
		}
		ofStream << "\n";
	}

	ofStream.close();
}

bool FileSystemChunkDatabase::isChunkSaved(MGL::PointI chunkPos)
{
	std::ifstream f(this->getChunkFilePath(chunkPos));
	return f.good();
}

std::string FileSystemChunkDatabase::getChunkFilePath(MGL::PointI pos) {
	return this->chunksFolder + std::to_string(pos.x) + "," + std::to_string(pos.y) + ".chunk";
}
