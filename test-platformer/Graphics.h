#pragma once
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <cstdio>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Graphics {
private:
	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window* mWindow;
	SDL_Surface* mBackBuffer;

	SDL_Renderer* mRenderer;

	Graphics();
	~Graphics();
	bool Init();

	static float DScaleXRatio() { return ((float)SCREEN_WIDTH) / ((float)GAMEAREA_WIDTH); }
	static float DScaleYRatio() { return ((float)SCREEN_HEIGHT) / ((float)GAMEAREA_HEIGHT); }

public:
	static const int GAMEAREA_WIDTH = 280;
	static const int GAMEAREA_HEIGHT = 192;
	static const int SCREEN_WIDTH = GAMEAREA_WIDTH * 4;
	static const int SCREEN_HEIGHT = GAMEAREA_HEIGHT * 4;

	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	SDL_Texture* LoadTexture(std::string filePath);
	SDL_Texture* LoadText(TTF_Font* font, std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	TTF_Font* LoadFont(std::string filePath, int size);

	void ClearBackBuffer();
	void ResetDrawColor();

	static SDL_Rect* CreateRect(int w, int h, int x, int y);
	void Fullscreen(bool _setFullscreen);
	static SDL_Rect* FullscreenRect();

	static SDL_Rect* TextureRectXY(SDL_Texture* texture, int x, int y);
	static SDL_Rect* CenterTextureRectX(SDL_Texture* texture, int y);
	
	// Position
	static SDL_Point GlobalCenterPoint(SDL_Rect* _rect);

	void DrawTexture(SDL_Texture* texture);
	void DrawTexture(SDL_Texture* texture, SDL_Rect* rect);
	void DrawTexture(SDL_Texture* texture, SDL_Rect* rect, double angle);
	void DrawTextureAtLocation(SDL_Texture* texture, SDL_Rect* spriterect, SDL_Rect* rect, double angle);

	void DrawLine(int r, int g, int b, int x1, int y1, int x2, int y2);

	void Render();
};

#endif
