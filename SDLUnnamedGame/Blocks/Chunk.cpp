#include "Chunk.h"

#include "../Globals.h"
extern Texture* blockTextures[BlockTypes::Size];
WorldGenerator* const Chunk::worldGenerator = new PossionDiscWorldGenerator();

Chunk::Chunk(PointI position) : GameObject(position, { Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }, nullptr), blocks()
{
	this->texture = new TargetTexture();

	for (int layer = 0; layer < LAYERS; layer++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {
				blocks[layer][column][row] = nullptr;
			}
		}
	}

	this->loadFromFile(std::string("./chunks/" + std::to_string(this->position.x) + "," + std::to_string(this->position.y) + ".chunk").c_str());
}

Chunk::~Chunk()
{
	for (int layer = 0; layer < LAYERS; layer++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {
				if (blocks[layer][column][row] != nullptr) {
					delete blocks[layer][column][row];
					blocks[layer][column][row] = nullptr;
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

	int currentLayer = -1;
	int row = 0;
	int column = 0;

	auto texturesToDraw = std::map<const Texture*, std::vector<PointI>>();

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
			if (blockTypeID != -1) {
				blocks[currentLayer][column][row] = createBlock(blockTypeID, PointI(column, row));

				const Texture* texture = blocks[currentLayer][column][row]->getTexture();
				// texturesToDraw.push_back(blocks[currentLayer][column][row]->getTexture());
				if (texturesToDraw.find(texture) == texturesToDraw.end()) {
					texturesToDraw[texture] = std::vector<PointI>();
				}
				PointI textureSize = texture->getTextureRect().getSize();
				texturesToDraw[texture].push_back({ row * textureSize.x, column * textureSize.y});

			} else {
				blocks[currentLayer][column][row] = nullptr;
			}
			row++;
			line = line.substr(line.find(",") + 1);
		}
		row = 0;
		column++;
	}
	static_cast<TargetTexture*>(this->texture)->DrawToTexture(texturesToDraw);
}


Block* Chunk::createBlock(int textureNumber, PointI position)
{
	return new Block((this->position * CHUNK_SIZE) + position, blockTextures[textureNumber]);

}

void Chunk::createChunk()
{
	
	int chunkData[LAYERS][CHUNK_SIZE][CHUNK_SIZE];

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[0][i][j] = -1;
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[1][i][j] = worldGenerator->getBlock( (this->position * CHUNK_SIZE) + PointI(i, j) );
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[2][i][j] = -1;
		}
	}

	std::ofstream ofStream;
	ofStream.open(std::string("./chunks/" + std::to_string(this->position.x) + "," + std::to_string(this->position.y) + ".chunk").c_str());

	if (!ofStream.is_open())
	{
		throw GameEngineException("Failed to open file : " + std::string("./chunks/") + std::to_string(this->position.x) + "," + std::to_string(this->position.y) + ".chunk");
	}
	for (int layer = 0; layer < LAYERS; layer++) {
		ofStream << "layer " << std::to_string(layer) << ":" << "\n";
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				ofStream << std::to_string(chunkData[layer][i][j]) + ",";
			}
			ofStream << "\n";
		}
		ofStream << "\n";
	}

	ofStream.close();
}

void Chunk::render()
{
	// this->chunkTexture.


	bool rendered = false;
	for (int row = 0; row < CHUNK_SIZE; row++) {
		for (int column = 0; column < CHUNK_SIZE; column++) {
			for (int layer = 2; layer >= 0; layer--) {
				if (blocks[layer][column][row] != nullptr) {
					blocks[layer][column][row]->render();
					rendered = true;
					break;
				}
			}
			if (!rendered) {
				throw GameEngineException("block is nullptr");
			}
			rendered = false;
		}
	}
}
