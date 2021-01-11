#include "EventHandler.h"

EventHandler::EventHandler(bool& quit, Renderer& renderer)
	: event(SDL_Event()), _quit(quit), renderer(renderer)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::checkForEvents()
{
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type) {
		case SDL_QUIT:
			quit();
			break;
		case SDL_MOUSEMOTION:
			mouseMove();
		}
	}
}

void EventHandler::mouseMove()
{
	int x, y;
	SDL_GetMouseState( &x, &y );
	unsigned char r, g, b, a;
	SDL_GetRenderDrawColor(renderer.get(), &r, &g, &b, &a );
	printf("red: %u blue: %u green: %u alpha: %u\n", r, g, b, a);

}

void EventHandler::quit()
{
	_quit = true;
}
