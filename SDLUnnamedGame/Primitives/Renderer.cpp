#include "Renderer.h"

Renderer::Renderer(Window& window)
	: renderer(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer)

{
	if (renderer == nullptr)
	{
		throw GameEngineException("Renderer could not be created! SDL Error: " +  std::string(SDL_GetError()) );
	}
	
	SDL_RendererInfo info;
	SDL_GetRendererInfo(this->renderer.get(), &info);
	if (!info.flags & SDL_RENDERER_TARGETTEXTURE) {
		throw GameEngineException("Renderer does not support target texture, and the game require that");
	}
}

Renderer::~Renderer()
{
	// TODO free renderer or add unique pointer
}

void Renderer::setBackgroundColor(Color color)
{
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer.get(), color.r, color.b, color.g, color.a);
}

Color Renderer::getBackgroundColor()
{
	Color color = { 0, 0 ,0 , 0 };
	SDL_GetRenderDrawColor(renderer.get(), &color.r, &color.g, &color.b, &color.a);
	return color;
}

void Renderer::activeBlendMode()
{
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
}

void Renderer::deactiveBlendMode()
{
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_NONE);
}

void Renderer::renderRectABS(Rect rect)
{
	

	Color bgColor = this->getBackgroundColor();
	this->activeBlendMode();
	this->setBackgroundColor(Color(255, 255, 255, 175));

	SDL_RenderFillRect(renderer.get(), &rect);

	this->deactiveBlendMode();
	this->setBackgroundColor(bgColor);
}

void Renderer::clear()
{
	//Clear screen
	SDL_RenderClear(renderer.get());
}

void Renderer::present()
{
	//Update screen
	SDL_RenderPresent(renderer.get());
}

