#include "pimpl.h"
#include "SetupFunctions.h"


namespace MGL {
	SDL_Rect convertRectToSDLRect(const Rect& rect) {
		return { rect.x, rect.y, rect.w, rect.h };
	}

	SDL_Color convertColorToSDLColor(const Color& color) {
		return { color.r, color.g, color.b, color.a };
	}

	Window::pimpl::pimpl(std::string name, int width, int height) :
		window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN))
	{
		if (window == nullptr)
		{
			throw MyGraphicsLibraryException("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
		}
	}

	Window::pimpl::pimpl::~pimpl() {
		SDL_DestroyWindow(window);
	}

	Renderer::pimpl::pimpl(Window::pimpl &window) :
		renderer(SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED))
	{
		if (renderer == nullptr)
		{
			throw MyGraphicsLibraryException("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));
		}

		SDL_RendererInfo info;
		SDL_GetRendererInfo(this->renderer, &info);
		if ((info.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
			throw MyGraphicsLibraryException("Renderer does not support target texture, and the game require that");
		}
	}


	Renderer::pimpl::~pimpl() {
		SDL_DestroyRenderer(renderer);
	}
	SDL_Renderer* renderer;

	void Renderer::pimpl::setRenderDrawColor(const Color& color) {
		SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
	}

	Color Renderer::pimpl::getRenderDrawColor() {
		Color color;
		SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
		return color;
	}

	void Renderer::pimpl::activeBlendMode() {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	}

	void Renderer::pimpl::deactiveBlendMode() {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	}

	void Renderer::pimpl::renderFillRect(const Rect& rect) {
		SDL_Rect sdl_rect = convertRectToSDLRect(rect);
		SDL_RenderFillRect(renderer, &sdl_rect);
	}

	void Renderer::pimpl::renderClear() {
		SDL_RenderClear(renderer);
	}

	void Renderer::pimpl::renderPresent() {
		SDL_RenderPresent(renderer);
	}

	Texture::pimpl Renderer::pimpl::getRenderTarget() {
		SDL_Texture* prevTarget = SDL_GetRenderTarget(this->renderer);
		return Texture::pimpl(prevTarget);
	}

	void Renderer::pimpl::setRenderTarget(Texture::pimpl &texture) {
		SDL_SetRenderTarget(this->renderer, texture.texture);
	}

	Texture::pimpl::pimpl(SDL_Texture* texture) :
		texture(texture)
	{
	}

	Texture::pimpl::~pimpl() {
		SDL_DestroyTexture(texture);
	}

	void Texture::pimpl::renderCopy(Renderer& renderer, const Rect& textureRect, const Rect& renderQuads) {

		SDL_Rect sdl_textureRect = convertRectToSDLRect(textureRect);
		SDL_Rect sdl_renderQuads = convertRectToSDLRect(renderQuads);
		SDL_RenderCopy(renderer.get()->renderer, texture, &sdl_textureRect, &sdl_renderQuads);
	}

	Texture::pimpl *Texture::pimpl::textureFromPath(Renderer& renderer, std::string path, Rect* textureRect) {
		SDL_Surface* textureSurface = IMG_Load(path.c_str());
		if (textureSurface == NULL) {
			throw MyGraphicsLibraryException("Unable to load image " + path + "! SDL_image Error: " + IMG_GetError());
		}

		SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(renderer.get()->renderer, textureSurface);
		if (!sdlTexture) {
			throw MyGraphicsLibraryException("Unable to load texture " + path + "! SDL_image Error: " + IMG_GetError());
		}

		if (textureRect->w == -1) {
			textureRect->w = textureSurface->w;
			textureRect->h = textureSurface->h;
		}

		SDL_FreeSurface(textureSurface);

		return new Texture::pimpl(sdlTexture);

	}

	Texture::pimpl *Texture::pimpl::createTargetTexture(Renderer& renderer, const Rect& textureRect) {
		SDL_Texture* texture = SDL_CreateTexture(renderer.get()->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, textureRect.w, textureRect.h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // TODO why
		return new Texture::pimpl(texture);
	}

	Texture::pimpl *Texture::pimpl::textureFromText(std::string text , Font &font, Color color, Renderer &renderer, Rect *outRect)
	{ //not efficient atm
		//Render text surface
		SDL_Surface* textureSurface = TTF_RenderText_Solid(font.get()->font, text.c_str(), convertColorToSDLColor(color));
		if (textureSurface == NULL)
		{
			std::cout << "Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()) << std::endl;
			throw MyGraphicsLibraryException("Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()) );
		}
		//Create texture from surface pixels
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.get()->renderer, textureSurface);
		if (texture == NULL)
		{
			throw MyGraphicsLibraryException("Unable to create texture from rendered text! SDL Error: " + std::string(SDL_GetError()) );
		}
		//Get image dimensions
		outRect->w = textureSurface->w;
		outRect->h = textureSurface->h;

		//Get rid of old surface
		SDL_FreeSurface(textureSurface);
		return new Texture::pimpl();
	}


	Font::pimpl::pimpl(TTF_Font* font) :
		font(font)
	{
	}

	Font::pimpl::~pimpl()
	{
		TTF_CloseFont(this->font);
	}

	Font::pimpl *Font::pimpl::fromPath(std::string path, int fontSize)
	{
		//Open the font
		//TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
		//TTF_Font* font = TTF_OpenFont("C:\\Users\\eitan\\Projects\\C++\\SDLUnnamedGame\\SDLUnnamedGame\\assets\\fonts\\Pixeled.ttf", fontSize);
		TTF_Font* font = TTF_OpenFont("C:\\Users\\eitan\\Projects\\C++\\SDLUnnamedGame\\SDLUnnamedGame\\assets\\fonts\\Pixeled.ttf", 28);
		if (font == NULL)
		{
			throw MyGraphicsLibraryException("Failed to load font! SDL_ttf Error: " + std::string(TTF_GetError()));
		}
		return new Font::pimpl(font);
	}



}