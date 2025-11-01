#include "Texture.h"

#include "./pimpl.h" 

namespace MGL {
	Texture::Texture(Renderer& renderer, Rect textureRect )
		:	pImpl(std::make_unique<Texture::pimpl>()), renderer(renderer), textureRect(textureRect)
	{
	}

	Texture::~Texture() = default;

	void Texture::renderABS(int x, int y)
	{
		//Set rendering space and render to screen
		Rect renderQuad = { x, y, this->textureRect.w, this->textureRect.h };
		pImpl->renderCopy(this->renderer, this->textureRect, renderQuad);
	}

	void Texture::renderABS(Rect locationAndSize)
	{
		pImpl->renderCopy(this->renderer, this->textureRect, locationAndSize);
	}

	void Texture::renderABS(Rect locationAndSize, Rect spriteLocationAndSize)
	{
		pImpl->renderCopy(this->renderer, spriteLocationAndSize, locationAndSize);
	}

	std::shared_ptr<Texture> Texture::CreateTextureFromImage(std::string path, Renderer& renderer, Rect textureRect)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(renderer, textureRect);

		texture->pImpl = std::unique_ptr<Texture::pimpl>(Texture::pimpl::textureFromPath(renderer, path, &textureRect));

		return texture;
	}
}
