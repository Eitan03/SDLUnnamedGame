#pragma once
#pragma once
#include <memory>
#include <SDL.h>
#include <string>
#include <iostream>

#include "Renderer.h"

namespace MGL {
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
}

