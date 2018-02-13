#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <vector>
#include <SDL2\SDL.h>
#include "Graphics.h"
#include "Line.h"

template<class T> class Sensor {
public:
	typedef std::vector<Sensor<T>*> Vec;
	typedef Vec::iterator VecIter;

	T* parent;

	Sensor() { this->parent = nullptr; }

	virtual SDL_Rect* Rect() = 0;
};

template<class T> class LineSensor : public Sensor<T> {
public:
	typedef std::vector<LineSensor<T>*> Vec;
	typedef Vec::iterator VecIter;

	Line* line;

	LineSensor() { 
		this->line = new Line();
	}
	LineSensor(T* _parent) { 
		this->line = new Line(); 
		this->parent = _parent;
	}

	void SetPoints(double _x1, double _y1, double _x2, double _y2) {
		line->SetPoints(_x1, _y1, _x2, _y2);
	}

	SDL_Rect* Rect() { return this->line->Rect(); }
};

template<class T> class RectSensor : public Sensor<T> {
public:
	typedef std::vector<RectSensor<T>*> Vec;
	typedef Vec::iterator VecIter;

	SDL_Rect* rect;

	RectSensor() {
		this->rect = Graphics::CreateRect(0, 0, 0, 0);
	}
	RectSensor(T* _parent) {
		this->rect = Graphics::CreateRect(0, 0, 0, 0);
		this->parent = _parent;
	}

	void SetRect(int w, int h, int x, int y) {
		this->rect->w = w;
		this->rect->h = h;
		this->rect->x = x;
		this->rect->y = y;
	}

	SDL_Rect* Rect() { return this->rect; }
};

#endif
