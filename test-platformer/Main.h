#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

# ifndef _MSC_VER
# define SDL_MAIN_HANDLED
# endif

#define CAMERA_W 256
#define CAMERA_H 176

#include "SceneManager.h"

class Main {
private:
	// Running Flag
	bool            Running;

	// Timer Vars
	Uint32			currTick;
	Uint32			lastTick;
	Uint32			timeStep;

	// Scenes
	SceneManager scene;

public:
	Main();

	int OnExecute();
};

#endif
