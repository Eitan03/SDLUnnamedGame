#pragma once
#pragma once
#include <memory>
#include <SDL.h>
#include <string>
#include <iostream>

#include "../Renderer.h"
#include "./Enums.h"
#include <SDL.h>

namespace MGL {

	typedef SDL_Event Event;

	int GetEvent(Event* event);

	uint32_t GetMouseState(int *x, int *y) { return SDL_GetMouseState(x, y); }
	
}

