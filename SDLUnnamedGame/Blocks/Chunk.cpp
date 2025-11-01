#include "Chunk.h"
#include <sstream>
#include <fstream>
#include "../Globals.h"
#include "./Block.h"

std::shared_ptr<MGL::Renderer> Chunk::renderer = nullptr;
std::unique_ptr<WorldGenerator> Chunk::worldGenerator = nullptr;
std::unique_ptr<ChunkDatabase> Chunk::chunkDatabase = nullptr;

Chunk::Chunk(MGL::PointI position) : ImmobileGameObject(position, { Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }, nullptr), blocks()
{
	this->texture = std::make_shared<MGL::TargetTexture>(*(this->renderer.get()), MGL::Rect{ 0, 0, BLOCK_TEXTURE_SIZE * CHUNK_SIZE, BLOCK_TEXTURE_SIZE * CHUNK_SIZE });

	this->loadChunk();
}

Chunk::~Chunk()
{
	Chunk::chunkDatabase->saveChunk(this->position, this->blocks);
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


void Chunk::loadChunk()
{
	if (this->chunkDatabase->isChunkSaved(this->position))
	{
		this->blocks = this->chunkDatabase->loadChunk(this->position);
	}
	else {
		this->blocks = createChunk();
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

std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::createChunk()
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
