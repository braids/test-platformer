#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "GameObjects\GameObject.h"
#include "Physics\Sensor.h"

class Player : public GameObject {
public:
	RectSensor<Player> *CollisionBody;
	LineSensor<Player> *A, *B, *C, *D, *L, *R;

	Player();

	void SetSensorPosition();
	
};


#endif
