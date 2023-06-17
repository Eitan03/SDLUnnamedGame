#include "Event.h"
#include <SDL.h>

namespace MGL {
	int GetEvent(Event* event) {
		return SDL_PollEvent(event);
	}
}

