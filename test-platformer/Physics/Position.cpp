#include "Physics\Position.h"

Position::Position() {
	this->x = 0.0;
	this->y = 0.0;
	this->dx = 0.0;
	this->dy = 0.0;
	this->ang = 0.0;
	this->dang = 0.0;
}

double Position::XYCrossProduct(Position* pos1, Position* pos2) {
	return (pos1->x * pos2->y) - (pos1->y * pos2->x);
}