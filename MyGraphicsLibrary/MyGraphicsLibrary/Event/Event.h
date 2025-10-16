#pragma once
#include <memory>
#include <string>
#include <iostream>

#include "./Enums.h"
#include "../Point.h"

namespace MGL {

	struct Event {

		EventTypes type;
		union { // can be done with polymorphisem, but requires effecinvcy so i dont want to use it
			PointI wheel;
			KeyCodes pressedKey; // keyDown or KeyUp
		};
	};

	Event GetEvent();

	uint32_t GetMouseState(float* x, float* y);
	
}

