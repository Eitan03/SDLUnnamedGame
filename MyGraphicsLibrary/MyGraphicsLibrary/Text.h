#pragma once
#include <iostream>

#include "Texture.h"
#include "Font.h"


namespace MGL {
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
	class Text : public Texture
	{
	public:
		Text(std::string text, Color color, Font& font, Renderer& renderer);
		void setText(std::string text);
		std::string getText() const { return text; };

	protected:
		std::string text;
		Color color;
		Font& font;
	};
}

