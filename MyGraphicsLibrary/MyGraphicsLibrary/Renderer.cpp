#include "Renderer.h"

#include "./pimpl.h"

namespace MGL {
	Renderer::Renderer(Window& window)
		: pImpl(std::make_unique<Renderer::pimpl>(window.pImpl.get()))
	{
		SDL_RendererInfo info;
		SDL_GetRendererInfo(this->pImpl.get()->renderer, &info);
		if (!info.flags & SDL_RENDERER_TARGETTEXTURE) {
			throw MyGraphicsLibraryException("Renderer does not support target texture, and the game require that");
		}
	}

	Renderer::~Renderer()
	{
		// TODO free renderer or add unique pointer
	}

	void Renderer::setBackgroundColor(Color color)
	{
		//Initialize renderer color
		this->pImpl.get()->setRenderDrawColor(color);
	}

	Color Renderer::getBackgroundColor()
	{
		Color color = this->pImpl.get()->getRenderDrawColor();
		return color;
	}

	void Renderer::activeBlendMode()
	{
		this->pImpl.get()->activeBlendMode();
	}

	void Renderer::deactiveBlendMode()
	{
		this->pImpl.get()->deactiveBlendMode();
	}

	void Renderer::renderRectABS(Rect rect)
	{
		

		Color bgColor = this->getBackgroundColor();
		this->activeBlendMode();
		this->setBackgroundColor({255, 255, 255, 175});

		this->pImpl.get()->renderFillRect(rect);

		this->deactiveBlendMode();
		this->setBackgroundColor(bgColor);
	}

	void Renderer::clear()
	{
		//Clear screen
		this->pImpl.get()->renderClear();
	}

	void Renderer::present()
	{
		//Update screen
		this->pImpl.get()->renderPresent();
	}
}

