#pragma once
#pragma once
#include <memory>
#include <SDL.h>
#include <assert.h>
#include <string>
#include <iostream>

#include "Renderer.h"

class EventHandler
{
public:
	EventHandler(bool& quit, Renderer& renderer);
	~EventHandler();
	void checkForEvents();
	void mouseMove();

	void quit();

private:
	SDL_Event event;
	bool& _quit;
	Renderer& renderer;
};

