#include "Chunk.h"

Texture** Chunk::blockTextures = Globals::getInstance()->blockTextures;

Chunk::Chunk(PointI position) : position(position), blocks()
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int l = LAYERS - 1; l > 0; l--) {
				blocks[l][i][j] = nullptr;
			}
		}
	}

	this->loadFromFile(std::string("./chunks/" + std::to_string(this->position.x) + "-" + std::to_string(this->position.y) + ".chunk").c_str());
}

Chunk::~Chunk()
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int l = 0; l < LAYERS; l++) {
				if (blocks[l][i][j] != nullptr) {
					delete blocks[l][i][j];
					blocks[l][i][j] = nullptr;
				}
			}
		}
	}
}

void Chunk::loadFromFile(const char* path)
{
	std::ifstream ifStream;
	ifStream.open(path);
	if (!ifStream.is_open())
	{
		std::cout << "creating File : " << path << std::endl;
		createChunk();
		ifStream.open(path);
	}

	unsigned int currentLayer = -1;
	int row = 0;
	int column = 0;

	
	std::string line;
	while (getline(ifStream, line)) {
		
		if (!line.compare("")) continue;

		if (line.find("layer ") == 0) { //if the line starts with "layer "
			currentLayer = std::stoi(line.substr(5, line.size() - 1));
			row = 0;
			column = 0;
		}
		else {
			
			while (line != "" && line.find(",") != std::string::npos ) {
				if (currentLayer > LAYERS || row > CHUNK_SIZE || column > CHUNK_SIZE) {
					std::cerr << "either currentLayer, row, or column is to big" << std::endl;
					assert(false);
				}
				int blockNum = std::stoi(line.substr(0, line.find(",")));
				blocks[currentLayer][row][column] = createBlock(blockNum, PointI(row, column));
				row++;
				line = line.substr(line.find(",") + 1);
			}
			row = 0;
			column++;


		}
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
			chunkData[i][j] = 0;
		}
	}

	std::ofstream ofStream;
	ofStream.open(std::string("./chunks/" + std::to_string(this->position.x) + "-" + std::to_string(this->position.y) + ".chunk").c_str());

	if (!ofStream.is_open())
	{
		std::cerr << "Failed to open file : " << "./chunks/" + std::to_string(this->position.x) + "-" + std::to_string(this->position.y) + ".chunk" << std::endl;
		assert(false);
	}

	ofStream << "layer 1:\n";

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			ofStream << std::to_string(chunkData[i][j]) + ",";
		}
		ofStream << "\n";
	}

	ofStream.close();
}

void Chunk::renderLayer(unsigned int layer)
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			blocks[layer][i][j]->render();
		}
	}
}

void Chunk::renderLayers(unsigned int layers[], unsigned int size)
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int l = LAYERS; l > 0; l--) {
				if (blocks[layers[l]][i][j] != nullptr) {
					blocks[layers[l]][i][j]->render();
					break;
				}
			}
		}
	}
}

void Chunk::render()
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int l = LAYERS - 1; l >= 0; l--) {
				if (blocks[l][i] != nullptr) {
					if (blocks[l][i][j] != nullptr) {
						blocks[l][i][j]->render();
						break;
					}
				}
			}
		}
	}
}
