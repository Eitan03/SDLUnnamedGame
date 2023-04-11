#include "main.h"


int main( int argc, char* args[] ) {
	initlialize();
	gameLoop();
	close();
	return 1;
}

void initlialize() {
	initlializeSDL();
	initlializeGameEngine();
}

void initlializeSDL()
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

	//Open the font
	font = TTF_OpenFont("assets\\fonts\\Pixeled.ttf", 28);
	if (font == NULL)
	{
		throw "Failed to load lazy font! SDL_ttf Error: " + std::string(TTF_GetError());
	}

}

void initlializeGameEngine()
{
	window = std::make_shared<Window>("Game", SCREEN_WIDTH, SCREEN_HEIGHT );
	renderer = std::make_shared<Renderer>( *window );
	renderer->setBackgroundColor(colors.Black);
	setUpTextures(*renderer);
	
	chunkManager = new ChunkManager(&(camera)); //TODO shared ptr?

	mousePositionABSText = std::make_unique<Text>("-1, -1", colors.White, *font, *renderer);
	fpsText = std::make_unique<Text>("fps: -1", colors.White, *font, *renderer);

	eventFactory = std::make_unique<EventFactoryImpl>(EventFactoryImpl());
	
	camera.addObserver(std::bind(&ChunkManager::cameraMoved, chunkManager, std::placeholders::_1));
	camera.addObserver(Block::update);

	cameraMovmentsTimer = Timer();
	cameraMovmentsTimer.Start();

	fpsTimer = Timer();
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
		moveScreenBasedOnTimePassed();
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
void moveScreenBasedOnTimePassed() {
	if (cameraMovmentsTimer.GetTime() >= 10) {
		int diffTime = cameraMovmentsTimer.GetTime();
		cameraMovmentsTimer.Start();
		moveScreen(diffTime);
	}
}

void moveScreen(int timeDiff) {
	if (isMouseInWindow) {
		int moveAmount = floor(0.2 * timeDiff);
		
		if ((mousePositionABS.y > 0) && (mousePositionABS.y < SCREEN_HEIGHT / 9)) {
			camera.move({ 0, -moveAmount });
		}
		if (mousePositionABS.y > SCREEN_HEIGHT - (SCREEN_HEIGHT / 9)) {
			camera.move({ 0, moveAmount });
		}
		if ((mousePositionABS.x > 0) && (mousePositionABS.x < SCREEN_WIDTH / 16)) {
			camera.move({ -moveAmount, 0 });
		}
		if (mousePositionABS.x > SCREEN_WIDTH - (SCREEN_WIDTH / 16)) {
			camera.move({ moveAmount, 0 });
		}
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
		mouseRect.setPosition(floor(mousePosition) * Block::getSizeScaled() - camera.getLocation());
		renderer->renderRectABS(mouseRect);
	}
}

void EventFactoryImpl::runEvents() { 
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		this->proccessEvent(event);
	}
}

void EventFactoryImpl::proccessEvent(SDL_Event event) {
	switch (event.type) {
	case SDL_QUIT:
		quitApplication = false;
		break;

	case SDL_MOUSEMOTION: //on mouse move
		if (isMouseInWindow) {
			this->updateMousePosition();
		}
		break;

	case (SDL_MOUSEWHEEL): //on mouse scroll
		this->changeScale(event.wheel.y);
		break;

	case SDL_WINDOWEVENT:
		this->windowEvent(event.window.event);
		break;

	case SDL_KEYDOWN:
		this->keydownEvent(event.key.keysym.sym);
		break;
	}

}

void EventFactoryImpl::updateMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePositionABS = { x, y };
	mousePosition = (PointF)(mousePositionABS + camera.getLocation()) / Block::getSizeScaled();
	mousePositionABSText.get()->setText(std::to_string((int)floor(mousePosition.x)) + ", " + std::to_string((int)floor(mousePosition.y)));
}

void EventFactoryImpl::changeScale(Sint32 mouseMovement)
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
		camera.move((PointI)round((mousePositionABS + camera.getLocation()) * (1 - after / before)) * -1);

		mouseRect.w = Block::getSizeScaled();
		mouseRect.h = Block::getSizeScaled();
	}
}

void EventFactoryImpl::windowEvent(Uint8 event) {
	switch (event)
	{
	case SDL_WINDOWEVENT_ENTER:
		isMouseInWindow = true;
		break;
	case SDL_WINDOWEVENT_LEAVE:
		isMouseInWindow = false;
		break;
	}

}

void EventFactoryImpl::keydownEvent(SDL_Keycode key) {

	switch (key)
	{
	case SDLK_w:
		std::cout << "pressed W" << std::endl;
		break;
	}

}

void close() {
	closeSDL();
	closeGameEngine();
}

void closeSDL()
{
	//Free global font
	TTF_CloseFont(font);
	font = NULL;
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void closeGameEngine()
{

}