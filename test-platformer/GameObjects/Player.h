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
	const double jmp = -6.5;		// Jump speed
	const double jmpend = -4.0;		// Jump speed when letting go early
	const double grv = 0.21875;		// Gravity

	// Movement input states
	bool inputLeft;		// Move left input is active
	bool inputRight;	// Move right input is active
	bool inputDown;		// Down input is active
	bool inputJump;		// Jump input is active
	// Player states
	bool Jumping;		// Player is jumping
	bool Rolling;		// Player is rolling
	bool InAir;			// Player is in air
	bool InWater;		// Player is underwater
	bool Super;			// Player is super player
	bool SuperShoes;	// Player has super shoes on
	// Terrain/Collision
	Terrain::Tree* TerrainTree;	// Pointer to current terrain tree
	SDL_Rect* CollisionSensor;		// Collision sensor rect
	SDL_Rect* BodyCollision;		// Body collision rect
	// Sensors
	Line *A, *B, *C, *D, *L, *R;				// Sensor line
	double valA, valB, valC, valD, valL, valR;	// Sensor line value

	//// Constructor

	// Default player Ctor.
	Player();	

	//// Initialization
	
	// Set active terrain tree.
	void SetTerrainTree(BSP_Tree<Terrain*>* terrainTree) { this->TerrainTree = terrainTree; }
	// Initialize sensor values to defaults.
	void InitSensorVals();

	//// Input
	void ClearInput();
	void UpdateInput();
	void MovementCheck();
	void JumpingCheck();


	//// Terrain Checks
	
	// Check active terrain tree for terrain that could collide with player.
	void CheckTerrainCollisions(BSP_Tree<Terrain*>* terrainTree);
	// Get terrain collision sensor values.
	void TerrainSensorValue(Line* line, double* lineVal, Terrain::Vec collisions);

	void UpdateAirState();

	//// Updates

	void Update(Uint32 ticks);	// Update player.
	
	// Motion Update
	
	void UpdateMotion(Uint32 ticks);	// Update player acceleration based on input events.

	// Position Update
	
	void UpdatePosition(Uint32 ticks);	// Move position of player using acceleration.
	void MoveXPos(Uint32 ticks);		// Move X position of player using acceleration.
	void MoveYPos(Uint32 ticks);		// Move Y position of player using acceleration.

	void TranslateCollision();	// Move collision rects relative to position.
	void TranslateSensors();	// Move sensors relative to position.

	void CorrectPosition();	// Corrections to position of player using sensors.
	void CorrectXPos();		// Correct X position of player using sensors.
	void CorrectYPos();		// Correct Y position of player using sensors.

	//// Motion properties

	double TopSpeed();	// Return player top speed based on active states.
	double Accel();		// Return player acceleration based on active states.
	double Decel();		// Return player deceleration based on active states.
	double Friction();	// Return player friction based on active states.

	//// Sensor checks

	bool A_Hit() { return this->valA < 36.0; }	// Sensor A detecting collision
	bool B_Hit() { return this->valB < 36.0; }	// Sensor B detecting collision
	bool C_Hit() { return this->valC < 36.0; }	// Sensor C detecting collision
	bool D_Hit() { return this->valD < 36.0; }	// Sensor D detecting collision
	bool L_Hit() { return this->valL < 10.0; }	// Sensor L detecting collision
	bool R_Hit() { return this->valR < 10.0; }	// Sensor R detecting collision
};


#endif
