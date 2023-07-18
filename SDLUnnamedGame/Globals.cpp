#include "Globals.h"
#include <iostream>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include <MyGraphicsLibrary/Texture.h>

Camera camera = Camera();

Colors colors = {
				{255, 255, 255}, //White
				{0 ,0 ,0} //Black
};

std::shared_ptr<MGL::Texture> blockTextures[BlockTypes::Size];
void setUpTextures(MGL::Renderer& renderer) {
	//setting up textures
	/*
		were  assuming that each texture is BLOCK_TEXTURE_SIZE by BLOCK_TEXTURE_SIZE and that there is max of 5 textures per row
	*/
	for (int i = 0; i < BlockTypes::Size; i++) {
		blockTextures[i] = MGL::Texture::CreateTextureFromImage("assets\\textures\\blocks.png", renderer, MGL::Rect{ (i % 5) * BLOCK_TEXTURE_SIZE, (i / 5) * BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE });
	}
}
