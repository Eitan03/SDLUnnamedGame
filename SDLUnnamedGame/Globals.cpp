#pragma once
#include <iostream>
#include <vector>

#include "Utilities.h"
#include "./GameEngine/Camera.h"
#include <MyGraphicsLibrary/Texture.h>

Camera camera = Camera();

struct Colors {
		const MGL::Color White;
		const MGL::Color Black;
	};
Colors colors = {
				{255, 255, 255}, //White
				{0 ,0 ,0} //Black
	};

enum BlockTypes {
	Grass,
	Sand,
	Size
};
std::shared_ptr<MGL::Texture> blockTextures[BlockTypes::Size];
void setUpTextures(MGL::Renderer& renderer) {
	//setting up textures
	/*
		were  assuming that each texture is 250 by 250 and that there is max of 5 textures per row
	*/
	for (int i = 0; i < BlockTypes::Size; i++) {
		blockTextures[i] = MGL::Texture::CreateTextureFromImage("assets\\textures\\blocks.png", renderer, MGL::Rect{ (i % 5) * 250, (i / 5) * 250, 250, 250 });
	}
}
