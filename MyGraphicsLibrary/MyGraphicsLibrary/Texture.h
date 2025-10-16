#pragma once
#include <iostream>

#include "Drawable.h"
#include "Renderer.h"

namespace MGL {
	class Texture: Drawable
	{
		friend class Renderer;
		friend class Font;
	public:
		Texture(Renderer& renderer, Rect textureRect = { -1, -1, -1, -1});
		~Texture(); // needed bc of pimpl

		Texture(const Texture& other) = default;

		void renderABS(int x, int y) override;
		void renderABS(Rect locationAndSize);

		inline Rect getTextureRect() const { return this->textureRect; };



	protected:
		struct pimpl;
		std::unique_ptr<pimpl> pImpl;

		inline pimpl* get() const { return pImpl.get(); }
		Renderer& renderer;
		Rect textureRect;

		inline Renderer::pimpl* getRendererPimpl() const { return renderer.get(); }
	public:
		static std::shared_ptr<Texture> CreateTextureFromImage(std::string path, Renderer& renderer, Rect textureRect);

		Renderer& getRenderer() const { return renderer; };
		pimpl* getTexture() const { return pImpl.get(); };

	};
}

