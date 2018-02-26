#include "Graphics.h"
#include "Line.h"

Line::Line() {
	this->InitPoints();
}

Line::Line(double _x1, double _y1, double _x2, double _y2) {
	this->InitPoints();
	this->Begin->x = _x1;
	this->Begin->y = _y1;
	this->End->x = _x2;
	this->End->y = _y2;
}

void Line::InitPoints() {
	this->Points.push_back(new Position());
	this->Points.push_back(new Position());
	this->Begin = *this->Points.begin();
	this->End = *this->Points.end();
}

void Line::SetPoints(double _x1, double _y1, double _x2, double _y2) {
	this->Begin->x = _x1;
	this->Begin->y = _y1;
	this->End->x = _x2;
	this->End->y = _y2;
}

void Line::Translate(double _x, double _y) {
	// Get line length
	Position length = *this->LengthVec();
	// Move begin point to position
	this->Begin->x = _x;
	this->Begin->y = _y;
	// Move end point to position offset by line length
	this->End->x = _x + length.x;
	this->End->y = _y + length.y;
}

double Line::Intercept() {
	return this->Begin->y - (this->Slope() * this->Begin->x);
}

double Line::Length() {
	return sqrt(pow(this->End->x - this->Begin->x, 2) + pow(this->End->y - this->Begin->y, 2));
}

Position* Line::LengthVec() {
	Position* lengthVec = new Position();
	
	lengthVec->x = (this->End->x - this->Begin->x);
	lengthVec->y = (this->End->y - this->Begin->y);

	return lengthVec;
}

double Line::Slope() {
	return (this->End->y - this->Begin->y) / (this->End->x - this->Begin->x);
}

SDL_Rect* Line::Rect()
{
	Position* length = this->LengthVec();
	return Graphics::CreateRect(length->x, length->y, this->Begin->x, this->Begin->y);
}

bool Line::HasIntersection(Line* lineA, Line* lineB) {
	// Get distance betweeen start point of each line
	Position* linesBeginDist = new Position();
	linesBeginDist->x = lineB->Begin->x - lineA->Begin->x;
	linesBeginDist->y = lineB->Begin->y - lineA->Begin->y;
	
	// Get cross product of line vectors
	double LengthCross = Position::XYCrossProduct(lineA->LengthVec(), lineB->LengthVec());

	// Get intersections
	double t = Position::XYCrossProduct(linesBeginDist, lineB->LengthVec()) / LengthCross;
	double u = Position::XYCrossProduct(linesBeginDist, lineA->LengthVec()) / LengthCross;

	// If both cross paths, return true
	if (LengthCross == 0 && t >= 0 && t <= 1 && u >= 0 && u <= 1)
		return true;
	// If they don't cross, return false
	else
		return false;
}

Position* Line::IntersectAt(Line* lineA, Line* lineB)
{
	// If slopes are parallel, return nullptr.
	if (lineA->Slope() - lineB->Slope() == 0)
		return nullptr;
	
	Position* pos = new Position();

	pos->x = (lineB->Intercept() - lineA->Intercept()) / (lineA->Slope() - lineA->Slope());
	pos->y = lineA->Slope() * pos->x + lineA->Intercept();
	
	/*
	pos->x = 
		(((lineA->Begin->x * lineA->End->y) - (lineA->Begin->y * lineA->End->x)) * (lineB->Begin->x - lineB->End->x) -
		((lineB->Begin->x * lineB->End->y) - (lineB->Begin->y * lineB->End->x)) * (lineA->Begin->x - lineA->End->x)) /
		((lineA->Begin->x - lineA->End->x) * (lineB->Begin->y - lineB->End->y) - 
		(lineA->Begin->y - lineA->End->y) * (lineB->Begin->x - lineB->End->x));

	pos->y = 
		(((lineA->Begin->x * lineA->End->y) - (lineA->Begin->y * lineA->End->x)) * (lineB->Begin->y - lineB->End->y) -
		((lineB->Begin->x * lineB->End->y) - (lineB->Begin->y * lineB->End->x)) * (lineA->Begin->y - lineA->End->y)) /
			((lineA->Begin->x - lineA->End->x) * (lineB->Begin->y - lineB->End->y) -
		(lineA->Begin->y - lineA->End->y) * (lineB->Begin->x - lineB->End->x));
	*/

	return pos;
}



