#include "GameObjects\Player.h"


Player::Player() {
	// Collision sensor
	this->CollisionBody = new RectSensor<Player>(this);
	// Floor sensors
	this->A = new LineSensor<Player>(this);
	this->B = new LineSensor<Player>(this);
	// Ceiling sensors
	this->C = new LineSensor<Player>(this);
	this->D = new LineSensor<Player>(this);
	// Side sensors
	this->L = new LineSensor<Player>(this);
	this->R = new LineSensor<Player>(this);
}

void Player::SetSensorPosition() {
	// Collision sensor
	this->CollisionBody->SetRect(20, 40, (int)this->mPosition.x - 10, (int)this->mPosition.y - 20);
	// Floor sensors
	this->A->SetPoints(this->mPosition.x - 9, this->mPosition.y, this->mPosition.x - 9, this->mPosition.y + 36);
	this->B->SetPoints(this->mPosition.x + 9, this->mPosition.y, this->mPosition.x + 9, this->mPosition.y + 36);
	// Ceiling sensors
	this->C->SetPoints(this->mPosition.x - 9, this->mPosition.y, this->mPosition.x - 9, this->mPosition.y - 36);
	this->D->SetPoints(this->mPosition.x + 9, this->mPosition.y, this->mPosition.x + 9, this->mPosition.y - 36);
	// Side sensors
	this->L->SetPoints(this->mPosition.x, this->mPosition.y + 4, this->mPosition.x - 10, this->mPosition.y + 4);
	this->R->SetPoints(this->mPosition.x, this->mPosition.y + 4, this->mPosition.x + 10, this->mPosition.y + 4);
}