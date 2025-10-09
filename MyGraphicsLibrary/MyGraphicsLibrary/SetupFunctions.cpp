#include "SetupFunctions.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

namespace MGL {
	void initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
			throw MyGraphicsLibraryException("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
		}
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			throw MyGraphicsLibraryException("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
		}
		if (TTF_Init() == -1)
		{
			throw MyGraphicsLibraryException("SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
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
		IMG_Quit();
		SDL_Quit();
	}
}