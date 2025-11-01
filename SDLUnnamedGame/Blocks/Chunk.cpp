#include "Chunk.h"
#include <sstream>
#include <fstream>
#include "../Globals.h"
#include "./Block.h"

std::unique_ptr<WorldGenerator> Chunk::worldGenerator = std::make_unique<PossionDiscWorldGenerator>(PossionDiscWorldGenerator());
std::shared_ptr<MGL::Renderer> Chunk::renderer = std::shared_ptr<MGL::Renderer>();

Chunk::Chunk(MGL::PointI position) : ImmobileGameObject(position, { Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }, nullptr), blocks()
{
	this->texture = std::make_shared<MGL::TargetTexture>(*(this->renderer.get()), MGL::Rect{ 0, 0, BLOCK_TEXTURE_SIZE * CHUNK_SIZE, BLOCK_TEXTURE_SIZE * CHUNK_SIZE });

	this->loadChunk();
}

Chunk::~Chunk()
{
	std::string path = std::string("./chunks/" + std::to_string((int)(this->position.x)) + "," + std::to_string((int)(this->position.y)) + ".chunk");
	saveChunk(path.c_str());
}

void Chunk::render()
{
	ImmobileGameObject::render(this->position * CHUNK_SIZE, this->size);
}

void Chunk::setBlock(std::unique_ptr<Block> block, int layer, MGL::PointI position)
{
	if (
		position.x >= CHUNK_SIZE || position.y >= CHUNK_SIZE ||
		position.x < 0 || position.y < 0 ||
		layer < 0 || layer >= LAYERS
		) {
		throw GameEngineException("invalid block to save!");
	}

	auto blockTexture = block->getTexture();
	this->blocks[layer][position.x][position.y] = std::move(block);

#ifndef NDEBUG // if debug
	system("cls");
	std::cout << "layer " << layer << std::endl;
	this->printLayer(layer);
#endif

	this->_drawToChunk(blockTexture, position);
}

std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::loadBlocksFromFile(const char* path) {

	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};
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
			if (static_cast<BlockType>(blockTypeID) != BlockType::Null) {
				chunkData[currentLayer][row][column] = std::make_unique<Block>(this->getPosition() * CHUNK_SIZE, static_cast<BlockType>(blockTypeID));
			}
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

	if (ifStream.good())
	{
		this->blocks = loadBlocksFromFile(path.c_str());
	}
	else {
		std::cout << "creating File : " << path << std::endl;
		this->blocks = createChunk(path.c_str());
	}


	for (int currentLayer = 0; currentLayer < LAYERS; currentLayer++) {
		auto texturesToDraw = std::map<std::shared_ptr<MGL::Texture>, std::vector<MGL::PointI>>();

		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {

				Block* block = this->blocks[currentLayer][row][column].get();
				if (block != nullptr) {
					std::shared_ptr<MGL::Texture> blockTexture = block->getTexture();
					if (texturesToDraw.find(blockTexture) == texturesToDraw.end()) {
						texturesToDraw[blockTexture] = std::vector<MGL::PointI>();
					}
					MGL::PointI textureSize = blockTexture->getTextureRect().getSize();
					texturesToDraw[blockTexture].emplace_back(MGL::PointI{ row * textureSize.x, column * textureSize.y });

				}
			}
		}
		static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture(texturesToDraw);
		// TODO debug func that opens a texture in a differenty window?
	}
}

std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::createChunk(const char* path)
{

	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[0][i][j] = std::unique_ptr<Block>(worldGenerator->generateBlock((this->position * CHUNK_SIZE) + MGL::PointI(i, j)));
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[1][i][j] = std::unique_ptr<Block>(worldGenerator->generateBlock((this->position * CHUNK_SIZE) + MGL::PointI(i, j)));
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[2][i][j] = nullptr;
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
				if (this->blocks[layer][j][i] != nullptr) {
					ofStream << std::to_string(this->blocks[layer][j][i]->getType()) + ",";
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

#ifndef NDEBUG // if debug
void Chunk::printLayer(int layer)
{
	for (int column = 0; column < CHUNK_SIZE; column++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			if (this->blocks[layer][row][column]) {
				std::cout << this->blocks[layer][row][column]->getType() << ", ";
			}
			else {
				std::cout << " , ";
			}
		}
		std::cout << std::endl;
	}
}
#endif

void Chunk::_drawToChunk(std::shared_ptr<MGL::Texture> texture, MGL::PointI position)
{
	static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture(texture, position * texture->getTextureRect().getSize());
}
