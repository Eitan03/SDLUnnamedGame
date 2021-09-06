#include "Chunk.h"

#include "../Globals.h"
extern Texture* blockTextures[BlockTypes::Size];
WorldGenerator* const Chunk::worldGenerator = new GrassWorldGenerator();

Chunk::Chunk(PointI position) : position(position), blocks()
{
	for (int row = 0; row < CHUNK_SIZE; row++) {
		for (int column = 0; column < CHUNK_SIZE; column++) {
				blocks[column][row] = nullptr;
		}
	}

	this->loadFromFile(std::string("./chunks/" + std::to_string(this->position.x) + "," + std::to_string(this->position.y) + ".chunk").c_str());
}

Chunk::~Chunk()
{
	std::cout << "deleted Chunk" << this->position << std::endl;
	for (int row = 0; row < CHUNK_SIZE; row++) {
		for (int column = 0; column < CHUNK_SIZE; column++) {
			if (blocks[column][row] != nullptr) {
				delete blocks[column][row];
				blocks[column][row] = nullptr;
			}
		}
	}
}

void Chunk::loadFromFile(const char* path)
{
	std::cout << path << std::endl;
	std::ifstream ifStream;
	ifStream.open(path);
	if (!ifStream.is_open())
	{
		std::cout << "creating File : " << path << std::endl;
		createChunk();
		ifStream.open(path);
	}

	int row = 0;
	int column = 0;


	std::string line;
	while (getline(ifStream, line)) {
		if (!line.compare("")) continue;

		/* if (line.find("layer ") == 0) { //if the line starts with "layer "
			currentLayer = std::stoi(line.substr(5, line.size() - 1));
			row = 0;
			column = 0;
		} */

		while (line != "" && line.find(",") != std::string::npos) {
			if (row > CHUNK_SIZE || column > CHUNK_SIZE) {
				throw GameEngineException("row or column too big");
			}
			int blockTypeID = std::stoi(line.substr(0, line.find(",")));
			blocks[column][row] = createBlock(blockTypeID, PointI(column, row));
			row++;
			line = line.substr(line.find(",") + 1);
		}
		row = 0;
		column++;
	}
}


Block* Chunk::createBlock(int textureNumber, PointI position)
{
	return new Block((this->position * CHUNK_SIZE) + position, blockTextures[textureNumber]);

}

void Chunk::createChunk()
{
	
	int chunkData[CHUNK_SIZE][CHUNK_SIZE];

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[i][j] = worldGenerator->getBlock( (this->position * CHUNK_SIZE) + PointI(i, j) );
		}
	}

	std::ofstream ofStream;
	ofStream.open(std::string("./chunks/" + std::to_string(this->position.x) + "," + std::to_string(this->position.y) + ".chunk").c_str());

	if (!ofStream.is_open())
	{
		throw GameEngineException("Failed to open file : " + std::string("./chunks/") + std::to_string(this->position.x) + "," + std::to_string(this->position.y) + ".chunk");
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			ofStream << std::to_string(chunkData[i][j]) + ",";
		}
		ofStream << "\n";
	}

	ofStream.close();
}

void Chunk::render()
{
	for (int row = 0; row < CHUNK_SIZE; row++) {
		for (int column = 0; column < CHUNK_SIZE; column++) {
			if (blocks[column][row] != nullptr) {
				blocks[column][row]->render();
			}
			else {
				throw GameEngineException("block is nullptr");

			}
		}
	}
}
