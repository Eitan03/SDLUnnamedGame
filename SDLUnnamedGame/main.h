#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MyGraphicsLibrary/Window.h"
#include "MyGraphicsLibrary/Renderer.h"
#include "MyGraphicsLibrary/Texture.h"
#include "MyGraphicsLibrary/Text.h"
#include "MyGraphicsLibrary/EventHandler.h"

#include "Globals.h"
#include "GameEngine/Camera.h"
#include "Blocks/Block.h"
#include "Blocks/ChunkManager.h"

#include "Timer.h"

void initlialize();
void initlializeSDL();
void initlializeGameEngine();
void initlializeGame();

void close();
void closeSDL();
void closeGameEngine();

extern Camera camera;
extern std::shared_ptr<MGL::Texture> blockTextures[BlockTypes::Size];
extern Colors colors;
extern void setUpTextures(MGL::Renderer& renderer);

std::shared_ptr<MGL::Window> window;
std::shared_ptr<MGL::Renderer> renderer;
Font* font;


bool quitApplication = false;
bool isMouseInWindow = true;
void moveScreen();
Timer cameraMovmentsTimer;

Timer fpsTimer;
int fpsCount;
void updateFpsCount();

Direction screenMoveDirection = None;
PointI mousePositionABS = { -1 , -1 };
PointF mousePosition = { -1 , -1 };
Rect mouseRect = { -1, -1, Block::getSize(), Block::getSize() };
std::unique_ptr<Text> mousePositionABSText;
std::unique_ptr<Text> fpsText;
void renderMouseRect();

std::unique_ptr<ChunkManager> chunkManager;


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