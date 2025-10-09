#include "Window.h"

#include "./pimpl.h"

namespace MGL {
	Window::Window(std::string name,int width, int height)
		: pImpl(std::make_unique<Window::pimpl>(name, width, height))
		, width(width), height(height)
	{
	}

	Window::~Window()
	{
	}
}