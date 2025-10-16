#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MyGraphicsLibrary/Window.h"
#include "MyGraphicsLibrary/Renderer.h"
#include "MyGraphicsLibrary/Texture.h"
#include "MyGraphicsLibrary/Text.h"
#include "MyGraphicsLibrary/Event/Event.h"
#include "MyGraphicsLibrary/SetupFunctions.h"

#include "Globals.h"
#include "GameEngine/Camera.h"
#include "Blocks/Block.h"
#include "Blocks/ChunkManager.h"
#include "Blocks/Generators/StructureGenerator.h"

#include <MyGraphicsLibrary/Timer.h>

void initlialize();
void initlializeGameEngine();
void initlializeGame();

void close();
void closeGameEngine();

extern Camera camera;
extern Colors colors;
extern void setUpTextures(MGL::Renderer& renderer);

std::shared_ptr<MGL::Window> window;
std::shared_ptr<MGL::Renderer> renderer;
MGL::Font* font; // erro when turining to shared_ptr?


bool quitApplication = false;
bool isMouseInWindow = true;
void moveScreen();
MGL::Timer cameraMovmentsTimer; //TODO replace with general tick/fps system

MGL::Timer fpsTimer;
int fpsCount;
void updateFpsCount();

Direction screenMoveDirection = None;
MGL::PointI mousePositionABS = { -1 , -1 };
MGL::PointF mousePosition = { -1 , -1 };
MGL::Rect mouseRect = { -1, -1, Block::getSize(), Block::getSize() };
std::unique_ptr<MGL::Text> mousePositionABSText;
std::unique_ptr<MGL::Text> fpsText;
void renderMouseRect();


std::unique_ptr<StructureGenerator> treeStructure;

std::shared_ptr<ChunkManager> chunkManager;


class EventFactory {
public:
	virtual void runEvents() = 0;
private:
	virtual void proccessEvent(const MGL::Event &event) = 0;
	virtual void keydownEvent(MGL::KeyCodes key) = 0;
};

class GameplayEventFactory : public EventFactory {

public:

	GameplayEventFactory();
	void runEvents() override;
private:
	void updateMousePosition();

	void changeScale(int32_t mouseMovement);

	void proccessEvent(const MGL::Event &event) override;


	void keydownEvent(MGL::KeyCodes key) override;
};

std::unique_ptr<EventFactory> gameplayEventFactory;

void gameLoop();

void render();