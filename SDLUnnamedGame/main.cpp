#include "main.h"

int main( int argc, char* args[] ) {
	initlialize();
	gameLoop();
	close();
	return 1;
}

void initlialize() {
	MGL::initialize();
	initlializeGameEngine();
	initlializeGame();
}


void initlializeGameEngine()
{
	window = std::make_shared<MGL::Window>("Game", SCREEN_WIDTH, SCREEN_HEIGHT );
	renderer = std::make_shared<MGL::Renderer>( *window );
	renderer->setBackgroundColor(colors.Black);
	setUpTextures(*renderer);

	font = MGL::initializeFont("assets\\fonts\\Pixeled.ttf");
	
	Chunk::SetRenderer(renderer);
	chunkManager = std::make_unique<ChunkManager>(&(camera)); //TODO shared ptr?

	mousePositionABSText = std::make_unique<MGL::Text>("-1, -1", colors.White, *font, *renderer);
	fpsText = std::make_unique<MGL::Text>("fps: -1", colors.White, *font, *renderer);

	eventFactory = std::make_unique<EventFactoryImpl>(EventFactoryImpl());
	

	cameraMovmentsTimer = MGL::Timer();

	fpsTimer = MGL::Timer();

	std::srand(1);
}

void initlializeGame() {
	camera.addObserver(std::bind(&ChunkManager::cameraMoved, chunkManager.get(), std::placeholders::_1));
	camera.addObserver(Block::update);

	cameraMovmentsTimer.Start();

	fpsTimer.Start();
	fpsCount = 0;
}

EventFactoryImpl::EventFactoryImpl() {
	this->updateMousePosition();
}

void gameLoop() {
	while (!quitApplication)
	{
		updateFpsCount();
		moveScreen();
		eventFactory->runEvents();
		render();
		renderer->present();
	}
};

void updateFpsCount() {
	fpsCount++;
	if (fpsTimer.GetTime() >= 1000) {
		fpsText.get()->setText("fps: " + std::to_string(fpsCount));
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
	mousePositionABSText.get()->renderABS(10, 0);
	fpsText.get()->renderABS(SCREEN_WIDTH - fpsText.get()->getRect().w - 10, 0);
	renderMouseRect();
}

void renderMouseRect()
{
	if (isMouseInWindow) {
		mouseRect.setPosition((MGL::PointI)floor(mousePosition) * Block::getSizeScaled() - camera.getLocation());
		renderer->renderRectABS(mouseRect);
	}
}

void EventFactoryImpl::runEvents() { 
	MGL::Event event;
	while (MGL::GetEvent(&event) != 0)
	{
		this->proccessEvent(event);
	}
}

void EventFactoryImpl::proccessEvent(MGL::Event event) {
	switch (event.type) {
	case static_cast<uint32_t>(MGL::Events::QUIT):
		quitApplication = true;
		break;

		case static_cast<uint32_t>(MGL::Events::MOUSEMOTION):
		if (isMouseInWindow) {
			this->updateMousePosition();
		}
		break;

		case static_cast<uint32_t>(MGL::Events::MOUSEWHEEL): //on mouse scroll
		this->changeScale(event.wheel.y);
		break;

	case static_cast<uint32_t>(MGL::Events::WINDOWEVENT):
		this->windowEvent(event.window.event);
		break;

	case static_cast<uint32_t>(MGL::Events::KEYDOWN):
		this->keydownEvent(static_cast<MGL::Events_KeyCode>(event.key.keysym.sym));
		break;
	}

}

void EventFactoryImpl::updateMousePosition()
{
	int x, y;
	MGL::GetMouseState(&x, &y);
	mousePositionABS = { x, y };
	mousePosition = (MGL::PointF)(mousePositionABS + camera.getLocation()) / (float)Block::getSizeScaled();
	mousePositionABSText.get()->setText(std::to_string((int)floor(mousePosition.x)) + ", " + std::to_string((int)floor(mousePosition.y)));

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

void EventFactoryImpl::changeScale(int32_t mouseMovement)
{
	if (mouseMovement != 0) {
		float scaleDelta = 0.05;
		float before = camera.getScale();
		if (mouseMovement > 0) // scroll up
		{
			camera.addToScale(scaleDelta);
		}
		else if (mouseMovement < 0) // scroll down
		{
			camera.addToScale(-scaleDelta);
		}
		float after = camera.getScale();
		camera.move((MGL::PointI)round((MGL::PointF)(mousePositionABS + camera.getLocation()) * (1 - after / before)) * -1);

		mouseRect.w = Block::getSizeScaled();
		mouseRect.h = Block::getSizeScaled();
	}
}

void EventFactoryImpl::windowEvent(uint8_t event) {
	switch (event)
	{
	case static_cast<int>(MGL::Events_Window::WINDOWEVENT_ENTER):
		isMouseInWindow = true;
		break;
	case static_cast<int>(MGL::Events_Window::WINDOWEVENT_LEAVE):
		isMouseInWindow = false;
		screenMoveDirection = None;
		break;
	}

}

void EventFactoryImpl::keydownEvent(MGL::Events_KeyCode key) {

	switch (key)
	{
	case MGL::Events_KeyCode::w :
		chunkManager->setBlock(std::make_unique<Block>(mousePosition, blockTextures[Sand], Sand), 1, mousePosition);
		std::cout << "pressed W" << std::endl;
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