#include "Chunk.h"

#include "../Globals.h"
extern std::shared_ptr<MGL::Texture> blockTextures[BlockTypes::Size];
std::unique_ptr<WorldGenerator> Chunk::worldGenerator = std::make_unique<PossionDiscWorldGenerator>(PossionDiscWorldGenerator());
std::shared_ptr<MGL::Renderer> Chunk::renderer = std::shared_ptr<MGL::Renderer>();

Chunk::Chunk(MGL::PointI position) : GameObject(position, { Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }, nullptr), blocks()
{
	// TODO make shared
	this->texture = std::make_shared<MGL::TargetTexture>(MGL::TargetTexture(*(this->renderer.get()), { 0, 0, Block::getSize() * CHUNK_SIZE, Block::getSize() * CHUNK_SIZE }));

	for (int layer = 0; layer < LAYERS; layer++) {
		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {
				this->blocks[layer][column][row] = std::unique_ptr<Block>{}; // TODO any cleaner way to init as empty?
			}
		}
	}

	this->loadFromFile(std::string("./chunks/" + std::to_string((int)(this->position.x)) + "," + std::to_string((int)(this->position.y)) + ".chunk").c_str());
}

void Chunk::loadFromFile(const char* path)
{
	std::ifstream ifStream;
	ifStream.open(path);
	if (!ifStream.is_open())
	{
		std::cout << "creating File : " << path << std::endl;
		createChunk(path);
		ifStream.open(path);
	}

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
			if (blockTypeID != -1) {
				this->blocks[currentLayer][column][row] = createBlock(blockTypeID, MGL::PointI(column, row));

			std::shared_ptr<MGL::Texture> texture = blocks[currentLayer][column][row]->getTexture();
				// texturesToDraw.push_back(blocks[currentLayer][column][row]->getTexture());
				if (texturesToDraw.find(texture) == texturesToDraw.end()) {
					texturesToDraw[texture] = std::vector<MGL::PointI>();
				}
				MGL::PointI textureSize = texture->getTextureRect().getSize();
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
	static_cast<MGL::TargetTexture*>(this->texture.get())->DrawToTexture(texturesToDraw);
}


std::unique_ptr<Block> Chunk::createBlock(int textureNumber, MGL::PointI position)
{
	return std::make_unique<Block>((MGL::PointI)(this->position * ( 1.0f * CHUNK_SIZE)) + position, blockTextures[textureNumber]);

}

void Chunk::createChunk(const char* path)
{
	
	int chunkData[LAYERS][CHUNK_SIZE][CHUNK_SIZE];

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
