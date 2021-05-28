#include "Window.h"

Window::Window(std::string name,int width, int height)
	: window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN), SDL_DestroyWindow)
	, width(width), height(height)
{
	if (window == nullptr)
	{
		throw GameEngineException("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
	}
}

Window::~Window()
{
	
}