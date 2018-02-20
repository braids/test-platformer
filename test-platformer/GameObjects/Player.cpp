#include <algorithm>
#include "GameObjects\Player.h"

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
	this->R = new Line(  9.0,  0.0, 10.0,  4.0);
}

void Player::CheckTerrainCollisions(BSP_Tree<Terrain>* terrainTree) {
	// Init the list of terrain collisions
	Terrain::Vec terrainCollisions;
	// Get all terrain on or near the collision sensor
	terrainTree->FindItems(&terrainCollisions, CollisionSensor);

	// Bail if there's no terrain nearby
	if (terrainCollisions.size() == 0)
		return;

	// Check all terrain sensors against terrain that is nearby
	this->TerrainSensorValue(this->A, &this->valA, terrainCollisions);
	this->TerrainSensorValue(this->B, &this->valB, terrainCollisions);
	this->TerrainSensorValue(this->C, &this->valC, terrainCollisions);
	this->TerrainSensorValue(this->D, &this->valD, terrainCollisions);
	this->TerrainSensorValue(this->L, &this->valL, terrainCollisions);
	this->TerrainSensorValue(this->R, &this->valR, terrainCollisions);
}

void Player::SetSensorVals() {
	valA = 36;
	valB = 36;
	valC = 36;
	valD = 36;
	valL = 10;
	valR = 10;
}

void Player::SetXPos() {
	if (valL < 10)
		this->mPosition.x = (this->L->Begin->x - this->valL) + 11.0;
	if (valR < 10)
		this->mPosition.x = (this->R->Begin->x + this->valR) - 11.0;
}

void Player::SetYPos() {
	//// Ceiling check
	// If either ceiling sensor is touching terrain, check to see which one is higher
	if (valC < 36.0 || valD < 36.0) {
		// If C sensor value is less than D sensor, move Y pos based on C sensor value
		if (valC < valD && valC <= 20)
			this->mPosition.y = (this->C->Begin->y - this->valC) + 20.0;
		// If D sensor value is less than C sensor, move Y pos based on D sensor value
		else if (valD < valC && valD <= 20)
			this->mPosition.y = (this->D->Begin->y - this->valD) + 20.0;
	}

	//// Floor check
	// If either floor sensor is touching terrain, check to see which one is higher
	if (valA < 36.0 || valB < 36.0) {
		// If A sensor value is less than B sensor, move Y pos based on A sensor value
		if (valA < valB)
			this->mPosition.y = (this->A->Begin->y + this->valA) - 20.0;
		// If B sensor value is less than A sensor, move Y pos based on B sensor value
		else
			this->mPosition.y = (this->B->Begin->y + this->valB) - 20.0;
	}
}

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

void Player::Update(Uint32 ticks) {

}

void Player::UpdateMotion() {
	//// Horizontal movement update
	// If input to move left and speed is less than top, subtract speed from xspeed
	if (moveLeft && this->mPosition.xspd > -this->TopSpeed())
		this->mPosition.xspd -= signbit(this->mPosition.xspd) ? this->Accel() : this->Decel();
	
	// If input to move right and speed is less than top, add speed to xspeed
	if (moveRight && this->mPosition.xspd < this->top)
		this->mPosition.xspd += signbit(this->mPosition.xspd) ? this->Accel() : this->Decel();

	// If not moving, reduce xspeed by friction times the sign of xspeed (that's what this is) and 0 if slow enough
	if (!moveLeft && !moveRight) 
		this->mPosition.xspd -= std::min(abs(this->mPosition.xspd), this->Friction()) * signbit(this->mPosition.xspd);

	//// Vertical motion update

}

double Player::TopSpeed() {
	// Set super top speed or regular top speed
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

double Player::Accel() {
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

double Player::Decel() {
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

double Player::Friction() {
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
