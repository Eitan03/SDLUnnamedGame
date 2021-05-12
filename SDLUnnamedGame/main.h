#pragma once

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


void initlialize();
void initlializeSDL();
void initlializeGameEngine();

void close();
void closeSDL();
void closeGameEngine();

extern Camera camera;
extern Texture* blockTextures[BlockTypes::Size];
extern Colors colors;
extern void setUpTextures(Renderer& renderer);

std::shared_ptr<Window> window;
std::shared_ptr<Renderer> renderer;
TTF_Font* font;


bool quitApplication = false;
bool isMouseInWindow = true;
unsigned int moveScreen(unsigned int interval, void* param);

PointI mousePositionABS = { -1 , -1 };
PointF mousePosition = { -1 , -1 };
Rect mouseRect = { -1, -1, Block::getSize(), Block::getSize() };
std::unique_ptr<Text> mousePositionABSText;
void renderMouseRect();

ChunkManager* chunkManager;


class EventFactory {
public:
	virtual void runEvents() = 0;
private:
	virtual  void proccessEvent(SDL_Event event) = 0;
	virtual void windowEvent(Uint8 event) = 0;
	virtual void keydownEvent(SDL_Keycode key) = 0;
};

class EventFactoryImpl : public EventFactory {

public:

	EventFactoryImpl();
	void runEvents() override;
private:
	void updateMousePosition();

	void changeScale(Sint32 mouseMovement);

	void proccessEvent(SDL_Event event) override;

	void windowEvent(Uint8 event) override;

	void keydownEvent(SDL_Keycode key) override;
};

std::unique_ptr<EventFactory> eventFactory;

void gameLoop();

void render();