#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <vector>
#include <SDL2\SDL.h>
#include "Assets.h"
#include "Graphics.h"
#include "Physics\Position.h"
#include "Timer.h"

// Forward dec classes
class GameObject;

enum ObjectID {
	Object_Player
};

class GameObject {
protected:
	Position	mPosition;
	ObjectID	mObjectId;
	ImageData	mImageData;
	
public:
	typedef std::vector<GameObject*> Vec;
	typedef Vec::iterator VecIter;

	GameObject();
	~GameObject();

	Position* GetPosition() { return &this->mPosition; }
	ImageData* GetImageData() { return &this->mImageData; }
	ObjectID GetObjectID() { return this->mObjectId; }
	void SetDrawPos(Uint32 _x, Uint32 _y);
	
	virtual void Update(Uint32 ticks) = 0;	
};

#endif