#include "TargetTexture.h"

TargetTexture::TargetTexture(Renderer& renderer, Rect textureRect): Texture(renderer, textureRect)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, textureRect.w, textureRect.h);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // TODO why
	
	this->sdlTexture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, SDL_DestroyTexture);
}

void TargetTexture::DrawToTexture(Texture* textures, PointI texturesPosition, size_t texturesSize)
{
	SDL_Texture* prevTarget = SDL_GetRenderTarget(this->renderer.get());
	
	SDL_Renderer* renderer = this->renderer.get();

    SDL_SetRenderTarget(renderer, this->sdlTexture.get());

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

	for (int i = 0; i < texturesSize; i++) {

		SDL_RenderCopy(renderer, textures[i].getTexture(), &(textures[i].getTextureRect()), texturesPosition[i]);
	}

    SDL_SetRenderTarget(renderer, prevTarget);
}
