#include "Texture.h"

Texture::Texture( std::string path, Renderer& renderer, Rect textureRect )
	:	texture( nullptr, nullptr), renderer(renderer), textureRect(textureRect)
{
	SDL_Surface* textureSurface = IMG_Load(path.c_str());
	if (textureSurface == NULL) {
		throw GameEngineException("Unable to load image " + path + "! SDL_image Error: " + IMG_GetError());
	}

	texture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(SDL_CreateTextureFromSurface(renderer.get() , textureSurface), SDL_DestroyTexture);
	if ( ! texture) {
		throw GameEngineException("Unable to load texture " + path + "! SDL_image Error: " + IMG_GetError());
	}

	if (textureRect.w == -1) {
		this->textureRect.w = textureSurface->w;
		this->textureRect.h = textureSurface->h;
	}

	SDL_FreeSurface(textureSurface);
}

void Texture::renderABS(int x, int y)
{
	//Set rendering space and render to screen
	Rect renderQuad = { x, y, this->textureRect.w, this->textureRect.h };
	SDL_RenderCopy(renderer.get(), texture.get(), &textureRect, &renderQuad);
}

void Texture::renderABS(Rect locationAndSize)
{
	SDL_RenderCopy(renderer.get(), texture.get(), &textureRect, &locationAndSize);
}