#include "main.h"

int main(int argc, char* args[]) {
	try {
		initlialize();
		gameLoop();
		close();
	}
	catch (const std::exception& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		throw e;
	}
	return 0;
}

void initlialize() {
	MGL::initialize();
	initlializeGameEngine();
	initlializeGame();
}


void initlializeGameEngine()
{
	window = std::make_shared<MGL::Window>("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	renderer = std::make_shared<MGL::Renderer>(window.get());
	renderer->setBackgroundColor(colors.Black);
	setUpTextures(*renderer);

	font = MGL::initializeFont("assets\\fonts\\Pixeled.ttf");

	Chunk::SetRenderer(renderer);
	chunkManager = std::make_shared<ChunkManager>(&camera);

	mousePositionABSText = std::make_unique<MGL::Text>("-1, -1", colors.White, *font, *renderer);
	fpsText = std::make_unique<MGL::Text>("fps: -1", colors.White, *font, *renderer);

	treeStructure = std::unique_ptr<StructureGenerator>(StructureGenerator::loadFromFile("assets\\structures\\tree.struct", chunkManager, "tree"));

	gameplayEventFactory = std::make_unique<GameplayEventFactory>(GameplayEventFactory());

	cameraMovmentsTimer = MGL::Timer();

	fpsTimer = MGL::Timer();

	std::srand(1);
}

void initlializeGame() {
	camera.addObserver(std::bind(&ChunkManager::onCameraChange, chunkManager.get(), std::placeholders::_1));
	camera.addObserver(Block::onCameraChange);

	cameraMovmentsTimer.Start();

	fpsTimer.Start();
	fpsCount = 0;
}

GameplayEventFactory::GameplayEventFactory() {
	this->updateMousePosition();
}

void gameLoop() {
	while (!quitApplication)
	{
		updateFpsCount();
		moveScreen();
		gameplayEventFactory->runEvents();
		render();
		renderer->present();
	}
};

void updateFpsCount() {
	fpsCount++;
	if (fpsTimer.GetTime() >= 1000) {
		fpsText->setText("fps: " + std::to_string(fpsCount));
		fpsCount = 0;
		fpsTimer.Start();
	}
}

//TODO look at
// https://gafferongames.com/post/fix_your_timestep/
// https://www.daniweb.com/programming/software-development/threads/446383/sdl-and-time-based-movement-problem#post1925548
// might have a bug here that makes it inconsistent
void moveScreen() {
	if (screenMoveDirection != None) {
		if (!cameraMovmentsTimer.Started()) {
			cameraMovmentsTimer.Start();
			return;
		}

		if (cameraMovmentsTimer.GetTime() >= 10) {
			int timeDiff = cameraMovmentsTimer.GetTime();
			cameraMovmentsTimer.Start();

			int moveAmount;

			if (screenMoveDirection & Down) {
				moveAmount = floor(0.2 * timeDiff);
				camera.move({ 0, -moveAmount });
			}
			if (screenMoveDirection & Up) {
				moveAmount = floor(0.2 * timeDiff);
				camera.move({ 0, moveAmount });
			}
			if (screenMoveDirection & Left) {
				moveAmount = floor(0.2 * timeDiff);
				camera.move({ -moveAmount, 0 });
			}
			if (screenMoveDirection & Right) {
				moveAmount = floor(0.2 * timeDiff);
				camera.move({ moveAmount, 0 });
			}
		}
	}
	else {
		cameraMovmentsTimer.Stop(); // TODO find a way to not run stop every tick?
	}
}

void render() {
	renderer->clear();
	chunkManager->render();
	mousePositionABSText->renderABS(10, 0);
	fpsText->renderABS(SCREEN_WIDTH - fpsText.get()->getTextureRect().w - 10, 0);
	renderMouseRect();
}

void renderMouseRect()
{
	if (isMouseInWindow) {
		mouseRect.setPosition((MGL::PointI)floor(mousePosition) * Block::getSizeScaled() - camera.getLocation());
		renderer->renderRectABS(mouseRect);
	}
}

void GameplayEventFactory::runEvents() {
	
	for (MGL::Event event = MGL::GetEvent(); event.type != MGL::EventTypes::NONE; event = MGL::GetEvent())
	{
	
		if (event.type != MGL::EventTypes::UNKNOWN) {
			this->proccessEvent(event);
		}
	}
}

void GameplayEventFactory::proccessEvent(const MGL::Event &event) {
	switch (event.type) {
	case MGL::EventTypes::QUIT:
		quitApplication = true;
		break;

	case MGL::EventTypes::MOUSE_MOVED:
		if (isMouseInWindow) {
			this->updateMousePosition();
		}
		break;

	case MGL::EventTypes::MOUSE_WHEEL:
		this->changeScale(event.wheel.y);
		break;

	case MGL::EventTypes::WINDOW_ENTER:
		isMouseInWindow = true;
		break;
	case MGL::EventTypes::WINDOW_LEAVE:
		isMouseInWindow = false;
		screenMoveDirection = None;
		break;
	case MGL::EventTypes::KEY_PRESSED:
		this->keydownEvent(event.pressedKey);
		break;
	}

}

void GameplayEventFactory::updateMousePosition()
{
	float x, y;
	MGL::GetMouseState(&x, &y);
	mousePositionABS = { (int)x, (int)y };
	mousePosition = (MGL::PointF)(mousePositionABS + camera.getLocation()) / (float)Block::getSizeScaled();
	mousePositionABSText->setText(std::to_string((int)floor(mousePosition.x)) + ", " + std::to_string((int)floor(mousePosition.y)));

	bool mouseInArea = false;
	if ((mousePositionABS.y > 0) && (mousePositionABS.y < SCREEN_HEIGHT / 9)) {
		screenMoveDirection = Down;
		mouseInArea = true;
	}
	if (mousePositionABS.y > SCREEN_HEIGHT - (SCREEN_HEIGHT / 9)) {
		screenMoveDirection = Up;
		mouseInArea = true;
	}
	if ((mousePositionABS.x > 0) && (mousePositionABS.x < SCREEN_WIDTH / 16)) {
		screenMoveDirection = Left;
		mouseInArea = true;
	}
	if (mousePositionABS.x > SCREEN_WIDTH - (SCREEN_WIDTH / 16)) {
		screenMoveDirection = Right;
		mouseInArea = true;
	}
	if (!mouseInArea) {
		screenMoveDirection = None;
	}
}

void GameplayEventFactory::changeScale(int32_t mouseMovement)
{
	if (mouseMovement != 0) {
		float scaleDelta = 0.05;
		float before = camera.getScale();
		if (mouseMovement > 0) // scroll up
		{
			camera.addToScale(scaleDelta);
		}
		else if (mouseMovement < 0 && camera.getScale() > 0.2) // scroll down // TODO not have 0.2 hardcoded
		{
			camera.addToScale(-scaleDelta);
		}
		float after = camera.getScale();
		camera.move((MGL::PointI)round((MGL::PointF)(mousePositionABS + camera.getLocation()) * (1 - after / before)) * -1);

		mouseRect.w = Block::getSizeScaled();
		mouseRect.h = Block::getSizeScaled();
	}
}

void GameplayEventFactory::keydownEvent(MGL::KeyCodes key) {

	auto mousePos = MGL::PointI{ (int)floor(mousePosition.x), (int)floor(mousePosition.y) };
	switch (key)
	{
	case MGL::KeyCodes::W:
		chunkManager->setBlock(std::make_unique<Block>(mousePos, Sand), 1, mousePos);
		std::cout << "pressed W" << std::endl;
		break;
	case MGL::KeyCodes::E:
		treeStructure->place(mousePos);
		std::cout << "pressed E" << std::endl;
		break;
	}

}

void close() {
	std::cout << "beginning shutdown..." << std::endl;
	MGL::close();
	closeGameEngine();
}


void closeGameEngine()
{

}