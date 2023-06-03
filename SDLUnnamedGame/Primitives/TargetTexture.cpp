#include "TargetTexture.h"

TargetTexture::TargetTexture(Renderer& renderer, Rect textureRect): Texture(renderer, textureRect)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, textureRect.w, textureRect.h);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // TODO why
	
	this->sdlTexture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, SDL_DestroyTexture);
}

void TargetTexture::DrawToTexture(std::map<std::shared_ptr<Texture>, std::vector<PointI>> textures)
{
	SDL_Texture* prevTarget = SDL_GetRenderTarget(this->renderer.get());
	
	SDL_Renderer* renderer = this->renderer.get();

    SDL_SetRenderTarget(renderer, this->sdlTexture.get());

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
	
	Rect textureRect = Rect();
	for (auto const& texture: textures) {
		textureRect.setSize(texture.first->getTextureRect().getSize());
		for (auto const& position : texture.second) {
			textureRect.setPosition(position);
			Rect srcRect = (texture.first->getTextureRect());
			SDL_RenderCopy(renderer, texture.first->getTexture(), &srcRect, &textureRect);
		}
	}

    SDL_SetRenderTarget(renderer, prevTarget);
}
