#include "Event.h"
#include <SDL3/SDL.h>
#include "../Utilities.h"


namespace MGL {

	Event GetEvent() { // TODO ugly switch statement, maybe refactor events?

		SDL_Event SDLEvent;

		if (SDL_PollEvent(&SDLEvent)) {
			switch (SDLEvent.type) {
			case SDL_EVENT_QUIT:
				return { EventTypes::QUIT };
				break;
			case SDL_EVENT_MOUSE_MOTION:
				return { EventTypes::MOUSE_MOVED };
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				return { EventTypes::MOUSE_WHEEL, PointI(SDLEvent.wheel.x, SDLEvent.wheel.y) };
				break;
			case SDL_EVENT_WINDOW_MOUSE_ENTER:
				return { EventTypes::WINDOW_ENTER };
				break;
			case SDL_EVENT_WINDOW_MOUSE_LEAVE:
				return { EventTypes::WINDOW_LEAVE };
				break;
			case SDL_EVENT_KEY_DOWN:
				return { .type = EventTypes::KEY_PRESSED, .pressedKey = static_cast<MGL::KeyCodes>(SDLEvent.key.key) };
				break;
			}

			//throw MyGraphicsLibraryException("invalid key type!");
			return { EventTypes::UNKNOWN };
		}
		else {
			return { EventTypes::NONE };
		}
	}
	uint32_t GetMouseState(float* x, float* y)
	{
		return SDL_GetMouseState(x, y);
	}
}

