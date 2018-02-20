#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "GameObjects\GameObject.h"
#include "GameObjects\Terrain.h"
#include "Physics\BSP_Tree.h"

class Player : public GameObject {
public:
	// Player motion consts
	const double acc = 0.046875;	// Acceleration
	const double dec = 0.5;			// Deceleration
	const double frc = 0.046875;	// Friction
	const double top = 6.0;			// Top speed
	const double tops = 10.0;		// Super top speed

	// Movement input states
	bool moveLeft;
	bool moveRight;
	// Player states
	bool InAir;
	bool InWater;
	bool Super;
	bool SuperShoes;

	SDL_Rect* CollisionSensor;
	SDL_Rect* BodyCollision;
	Line *A, *B, *C, *D, *L, *R;
	double valA, valB, valC, valD, valL, valR;
	Player();

	void CheckTerrainCollisions(BSP_Tree<Terrain>* terrainTree);

	// Sets
	void SetSensorVals();
	void SetXPos();
	void SetYPos();

	void TerrainSensorValue(Line* line, double* lineVal, Terrain::Vec collisions);
	
	void Update(Uint32 ticks);
	void UpdateMotion();

	double TopSpeed();
	double Accel();
	double Decel();
	double Friction();
};


#endif
