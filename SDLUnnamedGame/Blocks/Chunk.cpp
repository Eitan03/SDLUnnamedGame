#include "Chunk.h"
#include <sstream>
#include <fstream>
#include "../Globals.h"
#include "./Block.h"

std::unique_ptr<WorldGenerator> Chunk::worldGenerator = std::make_unique<PossionDiscWorldGenerator>(PossionDiscWorldGenerator());
std::shared_ptr<MGL::Renderer> Chunk::renderer = std::shared_ptr<MGL::Renderer>();

Chunk::Chunk(MGL::PointI position) : Gridable(position, { Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }, nullptr), blocks()
{
	this->texture = std::make_shared<MGL::TargetTexture>(MGL::TargetTexture(*(this->renderer.get()), { 0, 0, BLOCK_TEXTURE_SIZE * CHUNK_SIZE, BLOCK_TEXTURE_SIZE * CHUNK_SIZE }));

	for (int layer = 0; layer < LAYERS; layer++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {
				this->blocks[layer][row][column] = 0; // TODO any cleaner way to init as empty?
			}
		}
	}

	this->loadChunk();
}

Chunk::~Chunk()
{
	std::string path = std::string("./chunks/" + std::to_string((int)(this->position.x)) + "," + std::to_string((int)(this->position.y)) + ".chunk");
	saveChunk(path.c_str());
}

void Chunk::render()
{
	Gridable::render(this->position * CHUNK_SIZE, this->size);
}

void Chunk::setBlock(ID blockId, int layer, MGL::PointI position)
{
	if (
		position.x >= CHUNK_SIZE || position.y >= CHUNK_SIZE ||
		position.x < 0 || position.y < 0 ||
		layer < 0 || layer >= LAYERS
		) {
		throw GameEngineException("invalid block to save!");
	}

	this->blocks[layer][position.x][position.y] = blockId;
	system("cls");
	std::cout << "layer " << layer << std::endl;
	this->printLayer(layer);

	std::shared_ptr<MGL::Texture> blockTexture = Block::getTexture(this->blocks[layer][position.x][position.y]);
	static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture(blockTexture, position * blockTexture->getTextureRect().getSize());
}

std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::loadBlockIdsFromFile(const char* path) {

	std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};
	std::ifstream ifStream;
	ifStream.open(path);

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
			chunkData[currentLayer][row][column] = blockTypeID;
			row++;
		}
		row = 0;
		column++;
	}
	return chunkData;

}

void Chunk::loadChunk()
{
	std::string path = std::string("./chunks/" + std::to_string((int)(this->position.x)) + "," + std::to_string((int)(this->position.y)) + ".chunk");
	std::ifstream ifStream(path);

	std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};
	if (ifStream.good())
	{
		chunkData = loadBlockIdsFromFile(path.c_str());
	}
	else {
		std::cout << "creating File : " << path << std::endl;
		chunkData = createChunk(path.c_str());
	}


	for (int currentLayer = 0; currentLayer < LAYERS; currentLayer++) {
	auto texturesToDraw = std::map<std::shared_ptr<MGL::Texture>, std::vector<MGL::PointI>>();

		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {

				int blockTypeID = chunkData[currentLayer][row][column];
				if (blockTypeID != 0) {
					this->blocks[currentLayer][row][column] = blockTypeID;

					std::shared_ptr<MGL::Texture> texture = Block::getTexture(this->blocks[currentLayer][row][column]);
					if (texturesToDraw.find(texture) == texturesToDraw.end()) {
						texturesToDraw[texture] = std::vector<MGL::PointI>();
					}
					MGL::PointI textureSize = texture->getTextureRect().getSize();
					texturesToDraw[texture].emplace_back(MGL::PointI{ row * textureSize.x, column * textureSize.y });

				}
			}
		}
		static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture(texturesToDraw);
		// TODO debug func that opens a texture in a differenty window?
	}
}

std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::createChunk(const char* path)
{
	
	std::array<std::array<std::array<ID, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[0][i][j] = worldGenerator->getBlock( (this->position * CHUNK_SIZE) + MGL::PointI(i, j) );
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[1][i][j] = 0;
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[2][i][j] = 0;
		}
	}

	return chunkData;
}

void Chunk::saveChunk(const char* path)
{
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
				ofStream << std::to_string(this->blocks[layer][j][i]) + ",";
			}
			ofStream << "\n";
		}
		ofStream << "\n";
	}

	ofStream.close();
}

#ifndef NDEBUG // if debug
void Chunk::printLayer(int layer)
{
	for (int column = 0; column < CHUNK_SIZE; column++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			if (this->blocks[layer][row][column]) {
			std::cout << this->blocks[layer][row][column] << ", ";
			}
			else {
				std::cout << " , ";
			}
		}
		std::cout << std::endl;
	}
}
#endif
