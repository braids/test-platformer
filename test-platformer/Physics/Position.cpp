#include "Physics\Position.h"

Position::Position() {
	this->x = 0.0;
	this->y = 0.0;
	this->xspd = 0.0;
	this->yspd = 0.0;
	this->gspd = 0.0;
	this->ang = 0.0;
}

double Position::XYCrossProduct(Position pos1, Position pos2) {
	return (pos1.x * pos2.y) - (pos1.y * pos2.x);
}