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
			throw "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
		}
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			throw "SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError());
		}
		if (TTF_Init() == -1)
		{
			throw "SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError());
		}

		/*
			//Open the font
			font = TTF_OpenFont("assets\\fonts\\Pixeled.ttf", 28);
			if (font == NULL)
			{
				throw "Failed to load lazy font! SDL_ttf Error: " + std::string(TTF_GetError());
			}
		*/
	}

	void closeSDL()
	{
		//Free global font
		// TTF_CloseFont(font);
		// font = NULL;
		
		//Quit SDL subsystems
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
}