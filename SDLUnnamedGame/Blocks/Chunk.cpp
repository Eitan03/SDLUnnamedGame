#include "Chunk.h"

Texture** Chunk::blockTextures = Globals::getInstance()->blockTextures;

Chunk::Chunk(PointI position) : position(position), blocks()
{
}

Chunk::~Chunk()
{
}

void Chunk::load()
{
	this->createChunk();

	for (int i = 0; i < CHUNK_SIZE; i++) {
	for (int j = 0; j < CHUNK_SIZE; j++) {
			blocks[i][j] = new Block(this->position + PointI( i, j ), blockTextures[0]);
		}
	}
}

void Chunk::unload()
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			delete blocks[i][j];
		}
	}
}

int Chunk::loadFromFile(std::string path)
{
	return 0;
}

void Chunk::createChunk()
{
	std::string data = "\n"; //might be somethnig better then string? istream?
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int i = 0; i < CHUNK_SIZE; i++) {
			data += "0,";
		}
		data.pop_back(); //removes the last character
		data += "\n";
	}


	tinyxml2::XMLDocument chunkFile;

	tinyxml2::XMLElement* chunk = chunkFile.NewElement("Chunk");
	chunk->SetAttribute("position", std::string(std::to_string(this->position.x) + "," + std::to_string(this->position.x)).c_str() );
	chunkFile.InsertFirstChild(chunk);

	tinyxml2::XMLElement* chunkData = chunkFile.NewElement("data");
	chunkData->SetText( data.c_str() );

	chunk->InsertEndChild(chunkData);

	tinyxml2::XMLError eResult = chunkFile.SaveFile( std::string("./chunks/" + std::to_string(this->position.x) + "," + std::to_string(this->position.x) + ".chunk").c_str() );
	XMLCheckResult(eResult);

}

void Chunk::render()
{
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			blocks[i][j]->render();
		}
	}
}
