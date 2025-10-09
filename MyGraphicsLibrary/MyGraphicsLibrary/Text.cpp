#include "Text.h"

#include "pimpl.h"

namespace MGL {

	Text::Text(std::string text, Color color, Font& font, Renderer& renderer)
		: Texture(renderer, {0 ,0 ,0, 0}), text(text), font(font), color(color)
	{
		setText(text);
	}

	void Text::setText(std::string text) //not efficient atm
	{
		this->pImpl = std::unique_ptr<Texture::pimpl>(
			Texture::pimpl::textureFromText(
				text,
				this->font,
				this->color,
				this->getRenderer(),
				&this->textureRect
			)
		);
	}
}
