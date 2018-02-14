#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include "GameObjects\GameObject.h"
#include "Physics\BSP_Tree.h"
#include "Physics\Line.h"
#include "Physics\Sensor.h"

class Terrain : public GameObject {
public:
	typedef std::vector<Terrain*> Vec;
	typedef BSP_Tree<Terrain>::Node Node;
	typedef std::vector<Terrain::Node*> NodeVec;

	Line CollisionLine;

	Terrain();
	Terrain(double x1, double y1, double x2, double y2);

	void Update(Uint32 ticks);
	SDL_Rect* GetCollisionRect();
	NodeVec* GetCollisionNodes();
};

#endif

