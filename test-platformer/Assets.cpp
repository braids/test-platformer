#include "Assets.h"

// Assets instance
Assets* Assets::sInstance = NULL;

// Assets instance ctor
Assets* Assets::Instance() {
	if (sInstance == NULL)
		sInstance = new Assets();

	return sInstance;
}

// Assets cleanup
void Assets::Release() {
	delete sInstance;
	sInstance = NULL;
}

void Assets::LoadAssets() {

}

// Assets ctor
Assets::Assets() {

}

// Assets dtor. Frees all texture memory.
Assets::~Assets() {
	for (auto tex : mTextures) {
		if (tex.second != NULL)
			SDL_DestroyTexture(tex.second);
	}

	mTextures.clear();
}

// Load texture from file if not in texture map, then return pointer to texture in texture map.
SDL_Texture* Assets::GetTexture(std::string name) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("res/img/" + name);

	if (mTextures[fullPath] == NULL)
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);

	return mTextures[fullPath];
}

Mix_Chunk* Assets::GetSound(std::string name) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("res/snd/" + name);

	return Mix_LoadWAV(fullPath.c_str());
}

Mix_Music* Assets::GetMusic(std::string name) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("res/snd/" + name);

	return Mix_LoadMUS(fullPath.c_str());
}

TTF_Font* Assets::GetFont(std::string name, int size) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("res/font/" + name);
	std::string fullPathSize = fullPath;
	fullPathSize.append(std::to_string(size));

	if (mFonts[fullPathSize] == NULL)
		mFonts[fullPathSize] = Graphics::Instance()->LoadFont(fullPath, size);

	return mFonts[fullPathSize];
}