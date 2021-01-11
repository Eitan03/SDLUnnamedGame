#include "Text.h"

Text::Text(std::string text, Color color, TTF_Font& font, Renderer& renderer)
    : texture(nullptr, nullptr), text(text), font(font), color(color), renderer(renderer), textureRect({0 ,0 ,0, 0})
{
    setText(text);
}

void Text::setText(std::string text) //not efficient atm
{
    //Render text surface
    SDL_Surface* textureSurface = TTF_RenderText_Solid(&font, text.c_str(), color.ToSDL());
    if (textureSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        assert(false);
    }
    //Create texture from surface pixels
    texture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(SDL_CreateTextureFromSurface(renderer.get(), textureSurface), SDL_DestroyTexture);
    if (texture.get() == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        assert(false);
    }
    //Get image dimensions
    this->textureRect.w = textureSurface->w;
    this->textureRect.h = textureSurface->h;

    //Get rid of old surface
    SDL_FreeSurface(textureSurface);
}

Text::~Text()
{
	SDL_DestroyTexture((this->texture).get());
	this->texture.release();
}

void Text::renderABS(int x, int y)
{
	//Set rendering space and render to screen
    this->textureRect.x = x;
    this->textureRect.y = y;
	SDL_RenderCopy(renderer.get(), texture.get(), &textureRect, &textureRect);
}

void Text::renderABS(Point location)
{
    this->textureRect.x = location.x;
    this->textureRect.y = location.y;
	SDL_RenderCopy(renderer.get(), texture.get(), &textureRect, &textureRect);
}