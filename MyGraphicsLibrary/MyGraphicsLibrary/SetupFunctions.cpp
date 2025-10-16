#include "SetupFunctions.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace MGL {
	void initialize()
	{
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			throw MyGraphicsLibraryException("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
		}
		if (!TTF_Init())
		{
			throw MyGraphicsLibraryException("SDL_ttf could not initialize! SDL_ttf Error: " + std::string(SDL_GetError()));
		}

	}

	Font* initializeFont(const char* fontPath)
	{
			//Open the font
			Font *font = new Font(fontPath, 28);
			return font;
	}

	void close()
	{
		//Quit SDL subsystems
		TTF_Quit();
		SDL_Quit();
	}
}