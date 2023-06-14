#include "Text.h"

namespace MGL {

	Text::Text(std::string text, Color color, Font& font, Renderer& renderer)
		: texture(nullptr, nullptr), text(text), font(font), color(color), renderer(renderer), textureRect({0 ,0 ,0, 0})
	{
		setText(text);
	}

	void Text::setText(std::string text) //not efficient atm
	{
		//Render text surface
		SDL_Surface* textureSurface = TTF_RenderText_Solid(&font, text.c_str(), color);
		if (textureSurface == NULL)
		{
			throw MyGraphicsLibraryException("Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()) );
		}
		//Create texture from surface pixels
		texture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(SDL_CreateTextureFromSurface(renderer.get(), textureSurface), SDL_DestroyTexture);
		if (texture.get() == NULL)
		{
			throw MyGraphicsLibraryException("Unable to create texture from rendered text! SDL Error: " + std::string(SDL_GetError()) );
		}
		//Get image dimensions
		this->textureRect.w = textureSurface->w;
		this->textureRect.h = textureSurface->h;

		//Get rid of old surface
		SDL_FreeSurface(textureSurface);
	}

	void Text::renderABS(int x, int y)
	{
		Rect destRect = textureRect;
		destRect.setPosition({ x, y });
		SDL_RenderCopy(renderer.get(), texture.get(), &textureRect, &destRect);
	}

	void Text::renderABS(PointF location)
	{
		Rect destRect = textureRect;
		destRect.setPosition(location);
		SDL_RenderCopy(renderer.get(), texture.get(), &textureRect, &destRect);
	}
}
