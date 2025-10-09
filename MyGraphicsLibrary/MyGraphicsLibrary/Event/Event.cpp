#include "Event.h"
#include <SDL.h>
#include "../Utilities.h"


namespace MGL {

	Event GetEvent() { // TODO ugly switch statement, maybe refactor events?

		SDL_Event SDLEvent;

		WindowEventTypes windowEvent = {};

		if (SDL_PollEvent(&SDLEvent)) {
			switch (SDLEvent.type) {
			case SDL_QUIT:
				return { EventTypes::QUIT };
				break;
			case SDL_MOUSEMOTION:
				return { EventTypes::MOUSE_MOVED };
				break;
			case SDL_MOUSEWHEEL:
				return { EventTypes::MOUSE_WHEEL, PointI(SDLEvent.wheel.x, SDLEvent.wheel.y) };
				break;
			case SDL_WINDOWEVENT:
				switch (SDLEvent.window.type) {
				case SDL_WINDOWEVENT_ENTER:
					windowEvent = WindowEventTypes::ENTER;
					break;
				case SDL_WINDOWEVENT_LEAVE:
					windowEvent = WindowEventTypes::LEAVE;
					break;
				}
				return { .type = EventTypes::WINDOW_EVENT , .window = windowEvent };
				break;
			case SDL_KEYDOWN:
				return { .type = EventTypes::KEY_PRESSED, .pressedKey = static_cast<MGL::KeyCodes>(SDLEvent.key.keysym.sym) };
				break;
			}

			//throw MyGraphicsLibraryException("invalid key type!");
			return { EventTypes::UNKNOWN };
		}
		else {
			return { EventTypes::NONE };
		}
	}
	uint32_t GetMouseState(int* x, int* y)
	{
		return SDL_GetMouseState(x, y);
	}
}

