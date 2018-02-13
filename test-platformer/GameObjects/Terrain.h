#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include "GameObjects\GameObject.h"
#include "Physics\Sensor.h"

class Terrain : public GameObject {
public:
	LineSensor<Terrain> *line;

	Terrain();


};

#endif

