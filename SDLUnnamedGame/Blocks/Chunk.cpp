#include "Chunk.h"

#include "../Globals.h"
extern std::shared_ptr<MGL::Texture> blockTextures[BlockTypes::Size];
std::unique_ptr<WorldGenerator> Chunk::worldGenerator = std::make_unique<PossionDiscWorldGenerator>(PossionDiscWorldGenerator());
std::shared_ptr<MGL::Renderer> Chunk::renderer = std::shared_ptr<MGL::Renderer>();

Chunk::Chunk(MGL::PointI position) : GameObject(position, { Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }, nullptr), blocks()
{
	this->texture = std::make_shared<MGL::TargetTexture>(MGL::TargetTexture(*(this->renderer.get()), { 0, 0, Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }));

	for (int layer = 0; layer < LAYERS; layer++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {
				this->blocks[layer][column][row] = std::unique_ptr<Block>{}; // TODO any cleaner way to init as empty?
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

void Chunk::setBlock(std::unique_ptr<Block> block, int layer, MGL::PointI position)
{
	if (
		position.x > CHUNK_SIZE || position.y > CHUNK_SIZE ||
		position.x < 0 || position.y < 0 ||
		layer < 0 || layer > LAYERS
		) {
		throw GameEngineException("invalid block to save!");
	}

	this->blocks[layer][position.x][position.y] = std::move(block);

	std::shared_ptr<MGL::Texture> blockTexture = this->blocks[layer][position.x][position.y]->getTexture();
	auto x = position * blockTexture->getTextureRect().getSize();
	static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture1(blockTexture, x); // TODO why x isnt passed correctly
}

std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::loadBlockIdsFromFile(const char* path) {

	std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};
	std::ifstream ifStream;
	ifStream.open(path);

	int currentLayer = -1;
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
			chunkData[currentLayer][column][row] = blockTypeID;
			row++;
			line = line.substr(line.find(",") + 1);
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

	std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};
	if (ifStream.good())
	{
		chunkData = loadBlockIdsFromFile(path.c_str());
	}
	else {
		std::cout << "creating File : " << path << std::endl;
		chunkData = createChunk(path.c_str());
	}

	int currentLayer = 0;
	int row = 0;
	int column = 0;

	auto texturesToDraw = std::map<std::shared_ptr<MGL::Texture>, std::vector<MGL::PointI>>();

	for (int layer = 0; layer < LAYERS; layer++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {

				int blockTypeID = chunkData[layer][column][row];
				if (blockTypeID != -1) {
					this->blocks[currentLayer][column][row] = createBlock(blockTypeID, MGL::PointI(column, row));

					std::shared_ptr<MGL::Texture> texture = this->blocks[currentLayer][column][row]->getTexture();
					if (texturesToDraw.find(texture) == texturesToDraw.end()) {
						texturesToDraw[texture] = std::vector<MGL::PointI>();
					}
					MGL::PointI textureSize = texture->getTextureRect().getSize();
					texturesToDraw[texture].push_back({ row * textureSize.x, column * textureSize.y });

				}
			}
		}
	}

	static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture(texturesToDraw);
}


std::unique_ptr<Block> Chunk::createBlock(int textureNumber, MGL::PointI position)
{
	return std::make_unique<Block>((MGL::PointI)(this->position * ( 1.0f * CHUNK_SIZE)) + position, blockTextures[textureNumber], textureNumber);

}

std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> Chunk::createChunk(const char* path)
{
	
	std::array<std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> chunkData{};

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[0][i][j] = -1;
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[1][i][j] = worldGenerator->getBlock( (MGL::PointI)(this->position * ( 1.0f * CHUNK_SIZE)) + MGL::PointI(i, j) );
		}
	}

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			chunkData[2][i][j] = -1;
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
				if (this->blocks[layer][i][j]) {
					ofStream << std::to_string(this->blocks[layer][i][j]->BlockId) + ",";
				}
				else {
					ofStream << "0,";
				}
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
