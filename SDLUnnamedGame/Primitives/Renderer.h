#pragma once
#include <memory>
#include <SDL.h>
#include <string>

#include "Window.h"
#include "../Utilities.h"

class Renderer
{
public:
	Renderer(Window& window);
	Renderer(const Renderer&) = default;
	~Renderer();
	void clear();
	void present();
	void setBackgroundColor(Color color);
	Color getBackgroundColor();

	inline SDL_Renderer* get() const { return renderer.get(); }

	void activeBlendMode();
	void deactiveBlendMode();

	void renderRectABS(Rect rect);

private:
	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
};

