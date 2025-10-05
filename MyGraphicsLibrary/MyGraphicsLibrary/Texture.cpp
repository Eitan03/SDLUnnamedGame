#include "Texture.h"

#include "./pimpl.h" 

namespace MGL {
	Texture::Texture(Renderer& renderer, Rect textureRect )
		:	pImpl(std::make_unique<Texture::pimpl>()), renderer(renderer), textureRect(textureRect)
	{
	}

	void Texture::renderABS(int x, int y)
	{
		//Set rendering space and render to screen
		Rect renderQuad = { x, y, this->textureRect.w, this->textureRect.h };
		pImpl.get()->renderCopy(this->renderer, this->textureRect, renderQuad);
	}

	void Texture::renderABS(Rect locationAndSize)
	{
		pImpl.get()->renderCopy(this->renderer, this->textureRect, locationAndSize);
	}

	std::shared_ptr<Texture> Texture::CreateTextureFromImage(std::string path, Renderer& renderer, Rect textureRect)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(renderer, textureRect);

		SDL_Surface* textureSurface = IMG_Load(path.c_str());
		if (textureSurface == NULL) {
			throw MyGraphicsLibraryException("Unable to load image " + path + "! SDL_image Error: " + IMG_GetError());
		}

		texture->sdlTexture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(SDL_CreateTextureFromSurface(renderer.get() , textureSurface), SDL_DestroyTexture);
		if ( ! texture->sdlTexture) {
			throw MyGraphicsLibraryException("Unable to load texture " + path + "! SDL_image Error: " + IMG_GetError());
		}

		if (textureRect.w == -1) {
			texture->textureRect.w = textureSurface->w;
			texture->textureRect.h = textureSurface->h;
		}

		SDL_FreeSurface(textureSurface);
		return texture;
	}
}
