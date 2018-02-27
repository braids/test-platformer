#include <algorithm>
#include <set>
#include <typeinfo>
#include "GameObjects\Player.h"

#pragma region Constructor
// Default player Ctor.
Player::Player() {
	// Collision sensor rect
	this->CollisionSensor = Graphics::CreateRect(20, 72, -10, -36);
	// Body collision rect
	this->BodyCollision = Graphics::CreateRect(20, 40, -10, -20);
	// Floor sensors
	this->A = new Line( -9.0,  0.0, -9.0, 36.0);
	this->B = new Line(  9.0,  0.0,  9.0, 36.0);
	// Ceiling sensors
	this->C = new Line( -9.0,  0.0, -9.0,-36.0);
	this->D = new Line(  9.0,  0.0, -9.0,-36.0);
	// Side sensors
	this->L = new Line(  0.0,  4.0,-10.0,  4.0);
	this->R = new Line(  0.0,  4.0, 10.0,  4.0);
}
#pragma endregion Constructor

#pragma region Init
//// Initialization ////

// Initialize sensor values to defaults.
void Player::InitSensorVals() {
	this->valA = 36;
	this->valB = 36;
	this->valC = 36;
	this->valD = 36;
	this->valL = 10;
	this->valR = 10;
}
#pragma endregion Init

#pragma region TerrainCheck
//// Terrain Checks ////

// Check active terrain tree for terrain that could collide with player.
void Player::CheckTerrainCollisions(BSP_Tree<Terrain>* terrainTree) {
	// Init sensor vals
	this->InitSensorVals();

	// Init the list of terrain collisions
	Terrain::Vec terrainCollisions;

	// Get all terrain on or near the collision sensor
	terrainTree->FindItems(&terrainCollisions, CollisionSensor);
	
	// Bail if there's no terrain nearby
	if (terrainCollisions.size() == 0)
		return;
	
	// Remove duplicates
	std::set<Terrain*> s(terrainCollisions.begin(), terrainCollisions.end());
	terrainCollisions.assign(s.begin(), s.end());

	// Check all terrain sensors against terrain that is nearby
	this->TerrainSensorValue(this->A, &this->valA, terrainCollisions);
	this->TerrainSensorValue(this->B, &this->valB, terrainCollisions);
	this->TerrainSensorValue(this->C, &this->valC, terrainCollisions);
	this->TerrainSensorValue(this->D, &this->valD, terrainCollisions);
	this->TerrainSensorValue(this->L, &this->valL, terrainCollisions);
	this->TerrainSensorValue(this->R, &this->valR, terrainCollisions);
}

// Get terrain collision sensor values.
void Player::TerrainSensorValue(Line* line, double* lineVal, Terrain::Vec collisions) {
	for (Terrain* terrain : collisions) {
		// If nearby terrain intersects with the sensor
		if (Line::HasIntersection(line, &terrain->CollisionLine)) {
			// Get position of intersection
			Position pos = *Line::IntersectAt(line, &terrain->CollisionLine);
			
			// Get distance from line sensor start to intersection
			Line intersectLine(line->Begin->x, line->Begin->y, pos.x, pos.y);
			double length = intersectLine.Length();
			
			// If distance is shorter than current sensor value, update sensor value
			if (length < *lineVal)
				*lineVal = length;
		}
	}
}
#pragma endregion TerrainCheck

#pragma region Update
//// Update ////

// Update player.
void Player::Update(Uint32 ticks) {
	// Set acceleration values
	this->UpdateMotion();

	// Move position
	this->UpdatePosition();

	// Check for terrain collisions
	this->CheckTerrainCollisions(this->TerrainTree);

	// Correct position
	this->CorrectPosition();
}

#pragma region MotionUpdate
// Motion Update //

// Update player acceleration based on input events.
void Player::UpdateMotion() {
	/// Horizontal movement update ///
	// If input to move left and speed is less than top, subtract speed from xspeed
	if (this->inputLeft && this->mPosition.xspd > -this->TopSpeed())
		this->mPosition.xspd -= signbit(this->mPosition.xspd) ? this->Accel() : this->Decel();
	
	// If input to move right and speed is less than top, add speed to xspeed
	if (this->inputRight && this->mPosition.xspd < this->TopSpeed())
		this->mPosition.xspd += signbit(this->mPosition.xspd) ? this->Accel() : this->Decel();

	// If not moving, reduce xspeed by friction times the sign of xspeed (that's what this is) and 0 if slow enough
	if (!this->inputLeft && !this->inputRight)
		this->mPosition.xspd -= std::min(abs(this->mPosition.xspd), this->Friction()) * signbit(this->mPosition.xspd);
	
	/// Air Drag ///
	// If in the air and moving upward AND moving fast enough horizontally, add drag
	if (this->InAir && this->mPosition.yspd < 0 && this->mPosition.yspd > -4)
		this->mPosition.xspd -= (double)((int)(this->mPosition.xspd * 8) / 256);

	/// Gravity ///
	// Add gravity to yspeed if in air
	if (this->InAir)
		this->mPosition.yspd += this->grv;

	// Restrict top yspeed
	if (this->mPosition.yspd > 16)
		this->mPosition.yspd = 16;

}
#pragma endregion MotionUpdate

#pragma region PositionUpdate
// Position Update //

// Move position of player using acceleration.
void Player::UpdatePosition() {
	// Set player x/y
	this->MoveXPos();
	this->MoveYPos();
	
	// Reposition collision rects
	this->TranslateCollision();

	// Reposition sensors
	this->TranslateSensors();
}

// Move X position of player using acceleration.
void Player::MoveXPos() {
	// Move based on xspeed
	this->mPosition.x += this->mPosition.xspd;
}

// Move Y position of player using acceleration.
void Player::MoveYPos() {
	// Move based on yspeed
	this->mPosition.y += this->mPosition.yspd;
}

// Move collision rects relative to position.
void Player::TranslateCollision() {
	this->CollisionSensor->x = this->mPosition.x - 10;
	this->CollisionSensor->y = this->mPosition.y - 36;
	this->BodyCollision->x = this->mPosition.x - 10;
	this->BodyCollision->y = this->mPosition.y - 20;
}

// Move sensors relative to position.
void Player::TranslateSensors() {
	this->A->Translate(this->mPosition.x - 9.0, this->mPosition.y);
	this->B->Translate(this->mPosition.x + 9.0, this->mPosition.y);
	this->C->Translate(this->mPosition.x - 9.0, this->mPosition.y);
	this->D->Translate(this->mPosition.x + 9.0, this->mPosition.y);
	this->L->Translate(this->mPosition.x, this->mPosition.y + 4);
	this->R->Translate(this->mPosition.x, this->mPosition.y + 4);
}

// Corrections to position of player using sensors.
void Player::CorrectPosition() {
	// Set player x/y
	this->CorrectXPos();
	this->CorrectYPos();

	// Reposition collision rects
	this->TranslateCollision();

	// Reposition sensors
	this->TranslateSensors();
}

// Correct X position of player using sensors.
void Player::CorrectXPos() {
	// Kill acceleration if wall hit
	if (L_Hit() || R_Hit())
		this->mPosition.xspd = 0.0;
	// If wall to the left, move outside of wall
	if (L_Hit())
		this->mPosition.x = (this->L->Begin->x - this->valL) + 11.0;
	// If wall to the right, move outside of wall
	else if (R_Hit())
		this->mPosition.x = (this->R->Begin->x + this->valR) - 11.0;
}

// Correct Y position of player using sensors.
void Player::CorrectYPos() {
	//// Ceiling check
	// If either ceiling sensor is touching terrain, check to see which one is higher
	if (C_Hit() || D_Hit()) {
		// If C sensor value is less than D sensor, move Y pos based on C sensor value
		if (this->valC < this->valD && this->valC <= 20.0)
			this->mPosition.y = (this->C->Begin->y - this->valC) + 20.0;
		// If D sensor value is less than C sensor, move Y pos based on D sensor value
		else if (this->valD < this->valC && this->valD <= 20.0)
			this->mPosition.y = (this->D->Begin->y - this->valD) + 20.0;
	}

	//// Floor check
	// If either floor sensor is touching terrain, check to see which one is higher
	if (A_Hit() || B_Hit()) {
		// If A sensor value is less than B sensor, move Y pos based on A sensor value
		if (this->valA < this->valB)
			this->mPosition.y = (this->A->Begin->y + this->valA) - 20.0;
		// If B sensor value is less than A sensor, move Y pos based on B sensor value
		else
			this->mPosition.y = (this->B->Begin->y + this->valB) - 20.0;
	}
}
#pragma endregion PositionUpdate

#pragma endregion Update

#pragma region MotionProperties
//// Motion Properties ////

// Return player top speed based on active states.
double Player::TopSpeed() {
	// Set to super top speed or regular top speed const
	double topSpeed = this->Super ? this->tops : this->top;

	// If super shoes, double top speed
	if (this->SuperShoes)
		topSpeed *= 2.0;

	// If in water, halve top speed
	if (this->InWater)
		topSpeed /= 2.0;

	// Return top speed
	return topSpeed;
}

// Return player acceleration based on active states.
double Player::Accel() {
	// Set to player acceleration const
	double accel = this->acc;

	// If super, quadruple acceleration
	if (this->Super)
		accel *= 4.0;
	// If not super and super shoes are on, double acceleration
	else if (this->SuperShoes)
		accel *= 2.0;

	// If in the air, double acceleration
	if (this->InAir)
		accel *= 2.0;

	// If in water, halve acceleration
	if (this->InWater)
		accel /= 2.0;

	return accel;
}

// Return player deceleration based on active states.
double Player::Decel() {
	// Set to player deceleration const
	double decel = this->dec;

	// If rolling, quarter deceleration
	if (this->Rolling)
		decel /= 4.0;
	// If not rolling...
	else {
		// If super, double deceleration
		if (this->Super)
			decel *= 2.0;

		// If in water, halve deceleration
		if (this->InWater)
			decel /= 2.0;
	}

	return 0.0;
}

// Return player friction based on active states.
double Player::Friction() {
	// Set to player friction const
	double friction = this->frc;

	// If super, leave friction unchanged unless...
	if (this->Super) {
		// If rolling and not in water, double friction
		if (this->Rolling && !this->InWater)
			friction *= 2.0;
	}
	else {
		// If rolling, halve friction
		if (this->Rolling)
			friction /= 2.0;

		// If in water, halve friction
		if (this->InWater)
			friction /= 2.0;
		
		// If super shoes are on, double friction
		else if (this->SuperShoes)
			friction *= 2.0;
	}

	// Return friction if not in air, otherwise return 0
	return (this->InAir) ? 0.0 : friction;
}
#pragma endregion MotionProperties
