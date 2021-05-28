#pragma once
#include <memory>
#include <SDL.h>
#include <string>
#include <iostream>
#include "../Utilities.h"

class Window
{
public:
	Window(std::string name, int width, int height);
	Window(const Window&) = default;
	~Window();
	inline SDL_Window* get() const { return window.get(); }
private:
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
	int width;
	int height;
};

