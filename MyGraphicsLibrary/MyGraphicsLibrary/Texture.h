#pragma once
#include <iostream>
#include <SDL.h>

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



	protected:
		struct pimpl;
		std::unique_ptr<pimpl> pImpl;
	public:
		static std::shared_ptr<Texture> CreateTextureFromImage(std::string path, Renderer& renderer, Rect textureRect);

		//for the copy constructor
		Renderer& getRenderer() const { return renderer; };
		pimpl* getTexture() const { return pImpl.get(); };

	protected:
		inline pimpl* get() const { return pImpl.get(); }
		Renderer& renderer;
		Rect textureRect;
	};
}

