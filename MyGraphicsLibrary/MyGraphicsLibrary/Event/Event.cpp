#include "Event.h"
#include <SDL.h>

namespace MGL {
	int GetEvent(Event* event) {
		return SDL_PollEvent(event);
	}
	uint32_t GetMouseState(int* x, int* y)
	{
		return SDL_GetMouseState(x, y);
	}
}

