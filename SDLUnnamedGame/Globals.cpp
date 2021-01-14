#include "Globals.h"

Globals* Globals::instance = nullptr;

Globals::Globals():
	BlockSize(SCREEN_WIDTH / 16), camera(Camera()), BlockSizeScaled(BlockSize),
	colors(
		{
			{255, 255, 255}, //White
			{0 ,0 ,0} //Black
		}
	)
{
	
};

void Globals::setUpTextures(Renderer& renderer) {
	//setting up textures
	/*
		were  assuming that each texture is 250 by 250 and that there is max of 5 textures per row
	*/
	for (int i = 0; i < BlockTypes::Size; i++) {
		blockTextures[i] = new Texture("assets\\textures\\blocks.png", renderer, Rect{ (i % 5) * 250, (i / 5) * 250, 250, 250 }); //TODO change the word new here
	}
}

void Globals::deleteTextures() {
	for (int i = 0; i < BlockTypes::Size; i++) {
		delete blockTextures[i];
	}
}