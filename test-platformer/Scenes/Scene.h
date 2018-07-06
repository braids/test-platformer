#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Assets.h"
#include "Camera.h"
#include "GameObjects\GameObject.h"
#include "Timer.h"

// Forward dec the SceneManager
class SceneManager;
class Graphics;

// Class forward decs
class Scene;

//// Scene name enum
enum SceneName {
	Scene_Level1
};

//// Scene class
class Scene {
protected:
	SceneName		mSceneName; // Current scene name (pulled from enum)
	bool			mActive;	// Scene is active or inactive
	SceneManager*	mManager;	// Parent scene manager pointer
	Graphics*		mGraphics;	// Graphics instance pointer
	Camera			mCamera;
	ImageData::Vec	mImages;
	GameObject::Vec	mGameObjects;
	EventTimer::Vec	mEventTimers;

public:
	typedef std::vector<Scene*> Vec;
	typedef Vec::iterator VecIter;

	// Scene ctor/dtor
	Scene();
	~Scene();

	// Scene funcs
	void Init(SceneManager* manager);

	// Scene methods
	void SetActive(bool active) { this->mActive = active; }
	bool IsActive() const { return this->mActive; }
	void SetManager(SceneManager* manager) { this->mManager = manager; }
	void SetSceneName(SceneName name) { this->mSceneName = name; }
	ImageData* AddImage(Assets::Image* _image, int _x, int _y);
	ImageData* AddImage(ImageData* _imageData);
	ImageData* AddText(std::string _text, int _x, int _y);
	TextBox* AddTextBox(size_t _size, int _x, int _y);
	EventTimer* AddEventTimer(EventTimer* _eventTimer);
	
	void PauseTimers();
	void UnpauseTimers();
	void UpdateEventTimers();
	int KeycodeNumValue(SDL_Keycode _key);

	// Scene virtual funcs
	virtual void SceneStart() = 0;
	virtual void HandleEvent(SDL_Event* Event) = 0;
	virtual void Update(Uint32 timeStep) = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
};

#endif