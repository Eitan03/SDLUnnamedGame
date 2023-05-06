#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Drawable.h"
#include "Renderer.h"
#include "../Globals.h"

/* 
* https://github.com/grimfang4/SDL_FontCache
* https://stackoverflow.com/questions/22852226/c-sdl2-how-to-regularly-update-a-renderered-text-ttf
NOT DONE
TO DO:
optimize text
line breaks
fonts
size
*/

class Text : Drawable
{
public:
	Text(std::string text, Color color, TTF_Font& font, Renderer& renderer);
	void setText(std::string text);
	std::string getText() const { return text; };
	void renderABS(int x, int y) override;
	void renderABS(PointF location);

	inline Rect getRect() const { return this->textureRect; };

	//for the copy constructor
	Renderer& getRenderer() const { return renderer; };
	SDL_Texture* getTexture() const { return texture.get(); };
private:
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture;
	Rect textureRect;
	Renderer& renderer;

	std::string text;
	Color color;
	TTF_Font& font;
};

