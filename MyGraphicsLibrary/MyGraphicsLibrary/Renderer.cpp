#include "Renderer.h"

#include "./pimpl.h"

namespace MGL {
	Renderer::Renderer(Window *window)
		: pImpl(std::make_unique<Renderer::pimpl>(*window->pImpl.get()))
	{
	}

	Renderer::~Renderer()
	{
		// TODO free renderer or add unique pointer
	}

	void Renderer::setBackgroundColor(Color color)
	{
		//Initialize renderer color
		this->pImpl->setRenderDrawColor(color);
	}

	Color Renderer::getBackgroundColor()
	{
		Color color = this->pImpl->getRenderDrawColor();
		return color;
	}

	void Renderer::activeBlendMode()
	{
		this->pImpl->activeBlendMode();
	}

	void Renderer::deactiveBlendMode()
	{
		this->pImpl->deactiveBlendMode();
	}

	void Renderer::renderRectABS(Rect rect)
	{
		

		Color bgColor = this->getBackgroundColor();
		this->activeBlendMode();
		this->setBackgroundColor({255, 255, 255, 175});

		this->pImpl->renderFillRect(rect);

		this->deactiveBlendMode();
		this->setBackgroundColor(bgColor);
	}

	void Renderer::clear()
	{
		//Clear screen
		this->pImpl->renderClear();
	}

	void Renderer::present()
	{
		//Update screen
		this->pImpl->renderPresent();
	}
}

