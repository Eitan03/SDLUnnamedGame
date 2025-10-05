#pragma once

#include "./Window.h"
#include "./Renderer.h"
#include "./Texture.h"

#include <SDL.h>
#include <SDL_image.h>


namespace MGL {

	SDL_Rect convertRectToSDLRect(const Rect& rect) {
		return { rect.x, rect.y, rect.w, rect.h };
	}

	SDL_Color convertColorToSDLColor(const Color& color) {
		return { color.r, color.g, color.b, color.a };
	}

	struct Window::pimpl {
		pimpl(std::string name, int width, int height) :
			window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN))
		{
			if (window == nullptr)
			{
				throw MyGraphicsLibraryException("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
			}
		}

		~pimpl() {
			SDL_DestroyWindow(window);
		}
		SDL_Window* window;
	};

	struct Renderer::pimpl {
		pimpl(Window::pimpl window) :
			renderer(SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED))
		{
			if (renderer == nullptr)
			{
				throw MyGraphicsLibraryException("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));
			}
		}

		~pimpl() {
			SDL_DestroyRenderer(renderer);
		}
		SDL_Renderer* renderer;

		void setRenderDrawColor(const Color& color) {
			SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
		}

		Color getRenderDrawColor() {
			Color color;
			SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
			return color;
		}

		void activeBlendMode() {
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		}

		void deactiveBlendMode() {
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}

		void renderFillRect(const Rect& rect) {
			SDL_Rect sdl_rect = convertRectToSDLRect(rect);
			SDL_RenderFillRect(renderer, &sdl_rect);
		}

		void renderClear() {
			SDL_RenderClear(renderer);
		}

		void renderPresent() {
			SDL_RenderPresent(renderer);
		}
	};

	struct Texture::pimpl {
		pimpl() :
			texture(nullptr)
		{
		}

		~pimpl() {
			SDL_DestroyWindow(window);
		}

		void renderCopy(Renderer &renderer, const Rect& textureRect, const Rect& renderQuads) {

			SDL_Rect sdl_teextureRect = convertRectToSDLRect(textureRect);
			SDL_Rect sdl_renderQuads = convertRectToSDLRect(renderQuads);
			SDL_RenderCopy(renderer.get()->renderer, texture, &sdl_teextureRect, &sdl_renderQuads);
		}
		
		Texture::pimpl implFromPath(std::string path) {
			SDL_Surface* textureSurface = IMG_Load(path.c_str());
			if (textureSurface == NULL) {
				throw MyGraphicsLibraryException("Unable to load image " + path + "! SDL_image Error: " + IMG_GetError());
			}

			texture->sdlTexture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(SDL_CreateTextureFromSurface(renderer.get(), textureSurface), SDL_DestroyTexture);
			if (!texture->sdlTexture) {
				throw MyGraphicsLibraryException("Unable to load texture " + path + "! SDL_image Error: " + IMG_GetError());
			}

		}

		SDL_Texture* texture;
	};

}
