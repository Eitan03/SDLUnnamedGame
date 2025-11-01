#include "MockChunkDatabase.h"

std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> MockChunkDatabase::loadChunk(MGL::PointI pos)
{
	auto chunkData = std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS>();

		for (int row = 0; row < CHUNK_SIZE; row++) {
			for (int column = 0; column < CHUNK_SIZE; column++) {
				chunkData[1][row][column] = std::make_unique<Block>(pos * CHUNK_SIZE + MGL::PointI{ row, column }, BlockType::Grass);
			}
		}

		return chunkData;
}

void MockChunkDatabase::saveChunk(MGL::PointI pos, std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS>& chunk)
{
	return;
}

bool MockChunkDatabase::isChunkSaved(MGL::PointI chunkPos)
{
	return true;
}
