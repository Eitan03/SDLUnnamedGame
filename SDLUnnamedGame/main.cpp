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

	//Open the font
	font = TTF_OpenFont("assets\\fonts\\Pixeled.ttf", 28);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		assert(false);
	}

}

void initlializeGameEngine()
{
	window = std::make_shared<Window>("Game", SCREEN_WIDTH, SCREEN_HEIGHT );
	renderer = std::make_shared<Renderer>( *window );
	renderer->setBackgroundColor(colors.Black);
	setUpTextures(*renderer);
	
	chunkManager = new ChunkManager(&(camera)); //TODO shared ptr?
	camera.addObserver((observer*)chunkManager);

	mousePositionABSText = std::make_unique<Text>("-1, -1", colors.White, *font, *renderer);

	eventFactory = std::make_unique<EventFactoryImpl>(EventFactoryImpl());
	
	SDL_AddTimer(10, moveScreen, NULL);
}

EventFactoryImpl::EventFactoryImpl() {
	this->updateMousePosition();
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



void gameLoop() {
	while (!quitApplication)
	{
		eventFactory->runEvents();
		render();
		renderMouseRect();
		renderer->present();
	}
};
void render() {
	renderer->clear();
	chunkManager->render();
	mousePositionABSText.get()->renderABS(0, 0);
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