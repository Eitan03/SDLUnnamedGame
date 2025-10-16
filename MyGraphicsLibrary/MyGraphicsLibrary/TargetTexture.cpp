#include "TargetTexture.h"

#include "pimpl.h"

namespace MGL {
	TargetTexture::TargetTexture(Renderer& renderer, Rect textureRect): Texture(renderer, textureRect)
	{
		this->pImpl = std::unique_ptr<Texture::pimpl>(Texture::pimpl::createTargetTexture(renderer, textureRect));
	}

	TargetTexture::~TargetTexture() = default;

	void TargetTexture::DrawToTexture(std::map<std::shared_ptr<Texture>, std::vector<PointI>> textures)
	{
		Texture::pimpl prevTarget = this->getRendererPimpl()->getRenderTarget();
		
		this->getRendererPimpl()->setRenderTarget(*this->pImpl.get());

		// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		// SDL_RenderClear(renderer);
		// TODO add as clear func
		
		Rect textureRect = Rect();
		for (auto const& texture: textures) {
			textureRect.setSize(texture.first->getTextureRect().getSize());
			for (auto const& position : texture.second) {
				textureRect.setPosition(position);
				Rect srcRect = (texture.first->getTextureRect());
				//SDL_RenderCopy(renderer, texture.first->getTexture(), &srcRect, &textureRect);
				texture.first->getTexture()->renderCopy(renderer, srcRect, textureRect);
			}
		}

		this->getRendererPimpl()->setRenderTarget(prevTarget);
		this->renderer.setBackgroundColor({ 0, 0, 0, 0 });
	}
	void TargetTexture::DrawToTexture(std::shared_ptr<Texture> texture, PointI textureLocation)
	{
		Texture::pimpl prevTarget = this->getRendererPimpl()->getRenderTarget();


		this->getRendererPimpl()->setRenderTarget(*this->pImpl.get());

		Rect textureRect = Rect();
		textureRect.setSize(texture->getTextureRect().getSize());
		textureRect.setPosition(textureLocation);
		Rect srcRect = (texture->getTextureRect());
		//SDL_RenderCopy(renderer, texture->getTexture(), &srcRect, &textureRect);
		texture->getTexture()->renderCopy(renderer, srcRect, textureRect);

		this->getRendererPimpl()->setRenderTarget(prevTarget);
	}
}
