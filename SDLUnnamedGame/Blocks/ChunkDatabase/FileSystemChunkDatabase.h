#pragma once
#include "ChunkDatabase.h"

/*
	TODO make async to avoid spikes when loading/saving chunks
*/
class FileSystemChunkDatabase :
	public ChunkDatabase
{
public:
	FileSystemChunkDatabase(std::string chunksFolder);

	std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS> loadChunk(MGL::PointI pos) override;
	void saveChunk(MGL::PointI pos, std::array<std::array<std::array<std::unique_ptr<Block>, CHUNK_SIZE>, CHUNK_SIZE>, LAYERS>& chunk) override;

	bool isChunkSaved(MGL::PointI chunkPos) override;

protected:
	std::string chunksFolder;

	std::string getChunkFilePath(MGL::PointI pos);
};

