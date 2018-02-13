#include "Graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

Graphics::Graphics() {
	mBackBuffer = NULL;

	sInitialized = Init();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	// SDL Initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	// Create window
	if ((mWindow = SDL_CreateWindow("BASE_FRAMEWORK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		return false;

	// Create renderer
	if ((mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL)
		return false;

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		return false;

	if (TTF_Init() < 0)
		return false;

	mBackBuffer = SDL_GetWindowSurface(mWindow);

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string filePath) {
	SDL_Texture* texture = NULL;

	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (surface == NULL)
		return NULL;

	texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (texture == NULL)
		return NULL;

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* Graphics::LoadText(TTF_Font* font, std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_Texture* texture = NULL;

	SDL_Color color = { 255, 255, 255, 0 };
	
	color = { r, g, b, a };

	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, GAMEAREA_WIDTH - 7);

	if (surface == NULL)
		return NULL;

	texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (texture == NULL)
		return NULL;

	SDL_FreeSurface(surface);

	return texture;
}

TTF_Font* Graphics::LoadFont(std::string filePath, int size) {
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);

	if (font == NULL)
		return NULL;

	return font;
}


void Graphics::Render() {
	// Get window scale ratio
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(this->mWindow, &windowWidth, &windowHeight);
	float WScaleRatioX = (float)windowWidth / SCREEN_WIDTH;
	float WScaleRatioY = (float)windowHeight / SCREEN_HEIGHT;
	// Set render scale. Game area scaled to draw area (DScaleRatio), then scaled to window area (WScaleRatio).
	SDL_RenderSetScale(mRenderer, DScaleXRatio() * WScaleRatioX, DScaleYRatio() * WScaleRatioY);
	SDL_RenderPresent(mRenderer);
}

Graphics* Graphics::Instance() {
	if (sInstance == NULL)
		sInstance = new Graphics();

	return sInstance;
}

void Graphics::Release() {
	delete sInstance;
	sInstance = NULL;

	sInitialized = false;
}

bool Graphics::Initialized() {
	return sInitialized;
}

void Graphics::ClearBackBuffer() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
}

void Graphics::ResetDrawColor() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
}

SDL_Rect* Graphics::CreateRect(int w, int h, int x, int y) {
	SDL_Rect* rect = new SDL_Rect();

	rect->w = w;
	rect->h = h;
	rect->x = x;
	rect->y = y;

	return rect;
}

void Graphics::Fullscreen(bool _setFullscreen) {
	if(_setFullscreen)
		SDL_SetWindowFullscreen(this->mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(this->mWindow, 0);
}

SDL_Rect* Graphics::FullscreenRect()
{
	SDL_Rect* FullscreenRect = new SDL_Rect();

	FullscreenRect->x = 0;
	FullscreenRect->y = 0;
	FullscreenRect->w = Graphics::GAMEAREA_WIDTH;
	FullscreenRect->h = Graphics::GAMEAREA_HEIGHT;

	return FullscreenRect;
}

SDL_Rect* Graphics::TextureRectXY(SDL_Texture* texture, int x, int y)
{
	SDL_Rect* rect = new SDL_Rect();

	SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
	rect->x = x;
	rect->y = y;

	return rect;
}

SDL_Rect* Graphics::CenterTextureRectX(SDL_Texture* texture, int y)
{
	SDL_Rect* rect = new SDL_Rect();

	SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
	rect->x = (GAMEAREA_WIDTH / 2) - (rect->w / 2);
	rect->y = y;

	return rect;
}

SDL_Point Graphics::GlobalCenterPoint(SDL_Rect * _rect) {
	SDL_Point point;

	point.x = _rect->x + (_rect->w / 2);
	point.y = _rect->y + (_rect->h / 2);

	return point;
}

void Graphics::DrawTexture(SDL_Texture* texture) {
	Graphics::DrawTexture(texture, NULL, 0);
}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* rect) {
	Graphics::DrawTexture(texture, rect, 0);
}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* rect, double angle) {
	SDL_RenderCopyEx(mRenderer, texture, NULL, rect, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Graphics::DrawTextureAtLocation(SDL_Texture* texture, SDL_Rect* spriterect, SDL_Rect* rect, double angle) {
	SDL_RenderCopyEx(mRenderer, texture, spriterect, rect, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Graphics::DrawLine(int r, int g, int b, int x1, int y1, int x2, int y2) {
	SDL_SetRenderDrawColor(mRenderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(mRenderer, x1, y1, x2, y2);
	ResetDrawColor();
}
