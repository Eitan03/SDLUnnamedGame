#pragma once

#include "./Window.h"
#include "./Renderer.h"
#include "./Texture.h"
#include "./Font.h"
#include "./Event/Event.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>


namespace MGL {

	inline SDL_Rect convertRectToSDLRect(const Rect& rect);

	inline SDL_Color convertColorToSDLColor(const Color& color);

	struct Window::pimpl {
		pimpl(std::string name, int width, int height);
		pimpl(const pimpl&) = delete; // to not allow copyingm the internal pointer, and then destorying said copy and the pimpl object

		~pimpl();
		SDL_Window* window;
	};

	struct Texture::pimpl {
		pimpl(SDL_Texture* texture = nullptr);
		pimpl(const pimpl&) = delete; // to not allow copyingm the internal pointer, and then destorying said copy and the pimpl object

		~pimpl();

		void renderCopy(Renderer& renderer, const Rect& textureRect, const Rect& renderQuads);

		static Texture::pimpl *textureFromPath(Renderer& renderer, std::string path, Rect* textureRect);

		static Texture::pimpl *createTargetTexture(Renderer& renderer, const Rect& textureRect);

		static Texture::pimpl *textureFromText(std::string text , Font &font, Color color, Renderer &renderer, Rect *outRect);

		SDL_Texture* texture;
	};

	struct Renderer::pimpl {
		pimpl(Window::pimpl &window);
		pimpl(const pimpl&) = delete; // to not allow copyingm the internal pointer, and then destorying said copy and the pimpl object

		~pimpl();
		SDL_Renderer* renderer;

		void setRenderDrawColor(const Color& color);

		Color getRenderDrawColor();

		void activeBlendMode();

		void deactiveBlendMode();

		void renderFillRect(const Rect& rect);

		void renderClear();

		void renderPresent();

		Texture::pimpl getRenderTarget();

		void setRenderTarget(Texture::pimpl &texture);
	};

	struct Font::pimpl {
		pimpl(const pimpl&) = delete; // to not allow copyingm the internal pointer, and then destorying said copy and the pimpl object
	private:
		pimpl(TTF_Font* font);
	public:
		~pimpl();
	
		static Font::pimpl *fromPath(std::string path, int fontSize);

		TTF_Font* font;

	};
	
}
