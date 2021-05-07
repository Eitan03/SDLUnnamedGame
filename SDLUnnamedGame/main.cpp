#include <iostream>
#include <string>
#include <vector>
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
#include "GameEngine/Camera.h"
#include "Blocks/Block.h"
#include "Blocks/ChunkManager.h"


namespace EVENTS { void mouseMove(); void mouseScroll(SDL_Event& event); };
void init();
void close();
unsigned int moveScreen(unsigned int interval, void* param);


Window* window;
Renderer* renderer;
TTF_Font* font;

PointI mousePositionABS = { -1 , -1 }; //ABS position
PointF mousePosition = { -1 , -1 };
Rect mouseRect = { -1, -1, Block::getSize(), Block::getSize() };
std::unique_ptr<Text> mousePositionABSText;

//Main loop flag
bool quit = false;
bool isMouseInWindow = true;

extern Camera camera;
extern Texture* blockTextures[BlockTypes::Size];
extern Colors colors;
extern void setUpTextures(Renderer& renderer);

int main( int argc, char* args[] ) {

	init();

	ChunkManager* chunkManager = new ChunkManager(&(camera));
	//chunkManager->loadChunk(PointI(0, 0));
	//chunkManager->loadChunk(PointI(0, 1));

	Block tempSandBlock({ 6 ,7 }, blockTextures[1] );
	mousePositionABSText = std::make_unique<Text>("-1, -1", colors.White, *font, *renderer);

	renderer->setBackgroundColor( colors.Black );
	
	camera.addObserver((observer*)chunkManager);

	//Event handler
	SDL_Event event;

	SDL_AddTimer(10, moveScreen, NULL);
	

	EVENTS::mouseMove(); //initialzing values
	//While application is running
	while (!quit)
	{
		//rendering
		renderer->clear();

		chunkManager->render();
		tempSandBlock.render();

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
					std::cout << "pressed W" << std::endl;
					chunkManager->unloadChunk({ 0, 0 });
					break;
				}
				break;
			}

		}


		if (isMouseInWindow) {

			mouseRect.setPosition( floor(mousePosition) * Block::getSize() - camera.getLocation() );
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

	setUpTextures(*renderer);

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
		mousePosition = (PointF)(mousePositionABS + camera.getLocation()) / Block::getSizeScaled();
		mousePositionABSText.get()->setText(std::to_string((int)floor(mousePosition.x)) + ", " + std::to_string((int)floor(mousePosition.y)) );
	}

	void mouseScroll(SDL_Event& event)
	{
		if (event.wheel.y != 0) {
			float scaleDelta = 0.05;
			float before = camera.getScale();
			//temp = (mousePositionABS + cameraLocation) / (scale)
			if (event.wheel.y > 0) // scroll up
			{
				camera.addToScale(scaleDelta);
			}
			else if (event.wheel.y < 0) // scroll down
			{
				camera.addToScale(-scaleDelta);
			}
			float after = camera.getScale();
			camera.move((PointI)round((mousePositionABS + camera.getLocation()) * (1 - after / before)) * -1);

			mouseRect.w = Block::getSizeScaled();
			mouseRect.h = Block::getSizeScaled();
		}
	}

}

unsigned int moveScreen(unsigned int interval, void* param) {
	if (isMouseInWindow) {
		if ((mousePositionABS.y > 0) && (mousePositionABS.y < SCREEN_HEIGHT / 9)) {
			camera.move({ 0, -1 });
		}
		if (mousePositionABS.y > SCREEN_HEIGHT - (SCREEN_HEIGHT / 9)) {
			camera.move({ 0, 1 });
		}
		if ((mousePositionABS.x > 0) && (mousePositionABS.x < SCREEN_WIDTH / 16)) {
			camera.move({ -1, 0 });
		}
		if (mousePositionABS.x > SCREEN_WIDTH - (SCREEN_WIDTH / 16)) {
			camera.move({ 1, 0 });
		}
	}
	return interval;
}

