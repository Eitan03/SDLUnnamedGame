#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <assert.h>

#include "Primitives/Window.h"
#include "Primitives/Renderer.h"
#include "Primitives/Texture.h"
#include "Primitives/Text.h"
#include "Primitives/EventHandler.h"

#include "Globals.h"
#include "Blocks/Block.h"
#include "GameEngine/Camera.h"

#include <vector>

namespace EVENTS { void mouseMove(); void mouseScroll(SDL_Event& event); };
void init();
void close();
unsigned int moveScreen(unsigned int interval, void* param);

Globals* globals = Globals::getInstance();

Window* window;
Renderer* renderer;
TTF_Font* font;

PointI mousePositionABS = { -1 , -1 }; //ABS position
PointF mousePosition = { -1 , -1 };
Rect mouseRect = { -1, -1, globals->BlockSize, globals->BlockSize };
std::unique_ptr<Text> mousePositionABSText;

//Main loop flag
bool quit = false;
bool isMouseInWindow = true;



std::vector< std::vector<Block>> chunk;
int main( int argc, char* args[] ) {

	init();

	
	std::shared_ptr<Texture> blockTexture = std::make_shared<Texture>("assets\\textures\\blocks.png", *renderer, Rect{ 0, 0, 250, 250 });
	chunk.reserve(36);
	for (int i = 0; i < 6; i++) {
		chunk.push_back(std::vector<Block>());
		for (int j = 0; j < 6; j++) {
			chunk[i].push_back(Block({ j ,i }, blockTexture) );
		}
	}
	PointF point = { 0 , 0 };
	std::cout << (point + 5).x << std::endl;
	Block sand({ 6 ,6 }, std::make_shared<Texture>("assets\\textures\\blocks.png", *renderer, Rect{ 251, 0, 250, 250 }) );
	int num = 0;
	mousePositionABSText = std::make_unique<Text>("-1, -1", globals->colors.White, *font, *renderer);

	renderer->setBackgroundColor( globals->colors.Black );
	
	

	//Event handler
	SDL_Event event;

	SDL_AddTimer(10, moveScreen, NULL);
	

	EVENTS::mouseMove(); //initialzing values
	//While application is running
	while (!quit)
	{
		
		//rendering
		renderer->clear();

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				chunk[j][i].render();
			}
		}
		sand.render();

		mousePositionABSText.get()->renderABS(0, 0);
		//eventHandler.checkForEvents();

		//Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type) {
			case SDL_QUIT:
				quit = false;
				break;
			case SDL_MOUSEMOTION:
				if (isMouseInWindow) {
					EVENTS::mouseMove();
				}
				break;
			case (SDL_MOUSEWHEEL):
				EVENTS::mouseScroll(event);
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_ENTER:
					isMouseInWindow = true;
					break;
				case SDL_WINDOWEVENT_LEAVE:
					isMouseInWindow = false;
					break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					break;
				}
				break;
			}

		}


		if (isMouseInWindow) { //might be able to optimize! by doing math

			//mouseRect.x = (int)floor(mousePosition.x) * globals->camera.applyScale(globals->BlockSize);
			//mouseRect.y = (int)floor(mousePosition.y) * globals->camera.applyScale(globals->BlockSize);

			mouseRect.x = (int)floor((float)(mousePositionABS.x + globals->camera.getLocation().x) / globals->camera.applyScale(globals->BlockSize));
			// mouseRect = floor( (mousePositionABS + cameraLocation) / (Block*scale) )
			mouseRect.x = (int)round(mouseRect.x * globals->camera.applyScale(globals->BlockSize) - (globals->camera.getLocation().x));
			// mouseRect = round( (mouseRect * Block * Scale) - cameraLocation ) )
			mouseRect.y = (int)floor((float)(mousePositionABS.y + globals->camera.getLocation().y) / globals->camera.applyScale(globals->BlockSize));
			mouseRect.y = (int)round(mouseRect.y * globals->camera.applyScale(globals->BlockSize) - (globals->camera.getLocation().y));
			renderer->renderRectABS(mouseRect);
		}

		renderer->present();

	}
	window->~Window();
	renderer->~Renderer();


	close();
	return 1;
}

void init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		assert(false);
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		assert(false);
	}

	
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		assert(false);
	}
	

	window = new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT);

	renderer = new Renderer(*window);

	//Open the font
	font = TTF_OpenFont("assets\\fonts\\Pixeled.ttf", 28);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		assert(false);
	}
}

void close() {

	//Free global font
	TTF_CloseFont(font);
	font = NULL;

	delete window;
	delete renderer;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

namespace EVENTS {
	void mouseMove()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		mousePositionABS = { x, y };
		mousePosition.x = (float)(mousePositionABS.x + globals->camera.getLocation().x) / globals->camera.applyScale(globals->BlockSize);
		mousePosition.y = (float)(mousePositionABS.x + globals->camera.getLocation().x) / globals->camera.applyScale(globals->BlockSize);
		mousePositionABSText.get()->setText(std::to_string((int)floor(mousePosition.x)) + ", " + std::to_string((int)floor(mousePosition.y)) );
	}

	void mouseScroll(SDL_Event& event)
	{
		if (event.wheel.y != 0) {
			float scaleDelta = 0.05;
			PointF temp = { (float)(mousePositionABS.x + globals->camera.getLocation().x) / globals->camera.getScale(), (float)(mousePositionABS.y + globals->camera.getLocation().y) / globals->camera.getScale() };
			//temp = (mousePositionABS + cameraLocation) / (scale)
			if (event.wheel.y > 0) // scroll up
			{
				globals->camera.addToScale(scaleDelta);
			}
			else if (event.wheel.y < 0) // scroll down
			{
				globals->camera.addToScale(-scaleDelta);
			}
			PointF temp2 = { (float)(mousePositionABS.x + globals->camera.getLocation().x) / globals->camera.getScale(), (float)(mousePositionABS.y + globals->camera.getLocation().y) / globals->camera.getScale() };
			//temp = (mousePositionABS + cameraLocation) / (scale)
			globals->camera.move({ -1 * (int)round((temp2.x - temp.x) * globals->camera.getScale()), -1 * (int)round((temp2.y - temp.y) * globals->camera.getScale()) });

			mouseRect.w = globals->camera.applyScale(globals->BlockSize);
			mouseRect.h = globals->camera.applyScale(globals->BlockSize);
		}
	}

}

unsigned int moveScreen(unsigned int interval, void* param) {
	if (isMouseInWindow)
	if ((mousePositionABS.y > 0) && (mousePositionABS.y < SCREEN_HEIGHT / 9)) {
		globals->camera.move({ 0, -1 });
	}
	if (mousePositionABS.y > SCREEN_HEIGHT - (SCREEN_HEIGHT / 9)) {
		globals->camera.move({ 0, 1 });
	}
	if ((mousePositionABS.x > 0) && (mousePositionABS.x < SCREEN_WIDTH / 16)) {
		globals->camera.move({ -1, 0 });
	}
	if (mousePositionABS.x > SCREEN_WIDTH - (SCREEN_WIDTH / 16)) {
		globals->camera.move({ 1, 0 });
	}
	return interval;
}