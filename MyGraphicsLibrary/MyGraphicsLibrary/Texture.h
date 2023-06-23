#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Drawable.h"
#include "Renderer.h"

namespace MGL {
	class Texture: Drawable
	{
	public:
		Texture(Renderer& renderer, Rect textureRect = { -1, -1, -1, -1});
		void renderABS(int x, int y) override;
		void renderABS(Rect locationAndSize);

		inline Rect getTextureRect() const { return this->textureRect; };

		//for the copy constructor
		Renderer& getRenderer() const { return renderer; };
		SDL_Texture* getTexture() const { return sdlTexture.get(); };

		static std::shared_ptr<Texture> CreateTextureFromImage(std::string path, Renderer& renderer, Rect textureRect);
	protected:
		std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> sdlTexture;
		Renderer& renderer;
		Rect textureRect;
	};
}

