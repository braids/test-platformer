#include "Assets.h"
#include "Graphics.h"
#include "SceneManager.h"
#include "Scenes\Scene.h"
#include "Scenes\SceneList.h"

SceneManager::SceneManager() {
	// Set SDL Graphics NULL on creation
	this->mGraphics = NULL;
	this->mAssets = NULL;
	// We're not quitting yet
	this->quitGame = false;
	//Set fullscreen off
	this->Fullscreen = false;

	// Set timer values
	currTick = 0;
	lastTick = 0;
	timeStep = 0;
}

SceneManager::~SceneManager() {
	// Quit SDL_Mixer
	Mix_Quit();
	// Release/free SDL Graphics
	Graphics::Release();
	Assets::Release();
	this->mGraphics = NULL;
	this->mAssets = NULL;
}

bool SceneManager::Init() {
	printf("Init\n");

	// Initialize SDL Graphics
	this->mGraphics = Graphics::Instance();
	this->mAssets = Assets::Instance();
	
	// Initialize sound
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(16);
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
	// Load assets
	mAssets->LoadAssets();
	
	// Add scenes
	Scene::Vec scenes = *SceneList::GetSceneList();
	this->sceneList.insert(this->sceneList.end(), scenes.begin(), scenes.end());

	// Initialize scenes
	for (Scene* scene : this->sceneList)
		scene->Init(this);

	// Set initial scene
	this->StartScene(Scene_Default);

	// Init succeeded
	return true;
}

void SceneManager::Event(SDL_Event* Event) {
	if (Event->type == SDL_QUIT) 
		this->quitGame = true;
	else
		this->GetScene()->HandleEvent(Event);
}

void SceneManager::Render() {
	// Clear draw buffer
	this->mGraphics->ClearBackBuffer();

	// Run scene rendering func
	this->GetScene()->Render();

	// Render buffer to scene
	this->mGraphics->Render();
}

void SceneManager::StartScene(SceneName scene) {
	// Cleanup current scene if one exists
	if(this->GetScene() != nullptr)
		this->GetScene()->Cleanup();

	// Get next scene
	this->mNext = this->sceneList[scene];
	
	// Run scene start func
	this->mNext->SceneStart();
	
	// Set next scene as current
	this->mCurrent = this->mNext;
	
	// Clear next scene
	this->mNext = nullptr;

	// Run scene update
	this->Update();
}

void SceneManager::UpdateTicks() {
	// Update timeStep by # of ticks from last cycle
	this->lastTick = this->currTick;
	this->currTick = SDL_GetTicks();
	this->timeStep = this->currTick - this->lastTick;
}
