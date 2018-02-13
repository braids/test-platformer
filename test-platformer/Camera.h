#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Assets.h"
#include "Graphics.h"
#include "GameObjects\GameObject.h"

class Camera {
public:
	SDL_Rect* viewport;
	GameObject* target;

	Camera();

	void Init(SDL_Rect* _viewport);
	Uint32 CameraOffsetX();
	Uint32 CameraOffsetY();
	void SetTargetGameObject(GameObject* _target);
	void CenterOnTarget();
};

#endif