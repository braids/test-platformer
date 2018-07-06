#include "Graphics.h"
#include "Line.h"

Line::Line() {
	this->InitPoints();
}

Line::~Line() {
	for (Position* point : this->Points)
		delete point;
}

Line::Line(double _x1, double _y1, double _x2, double _y2) {
	this->Points.push_back(new Position());
	this->Points.push_back(new Position());
	this->Begin = this->Points.front();
	this->End = this->Points.back();//.end();
	//this->InitPoints();
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
	Position length = this->LengthVec();
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

Position Line::LengthVec() {
	Position lengthVec;
	
	lengthVec.x = (this->End->x - this->Begin->x);
	lengthVec.y = (this->End->y - this->Begin->y);

	return lengthVec;
}

double Line::Slope() {
	return (this->End->y - this->Begin->y) / (this->End->x - this->Begin->x);
}

SDL_Rect* Line::Rect()
{
	Position length = this->LengthVec();
	return Graphics::CreateRect((int)length.x, (int)length.y, (int)this->Begin->x, (int)this->Begin->y);
}

bool Line::HasIntersection(Line* lineA, Line* lineB) {
	// Get distance betweeen start point of each line
	Position linesBeginDist;
	linesBeginDist.x = lineB->Begin->x - lineA->Begin->x;
	linesBeginDist.y = lineB->Begin->y - lineA->Begin->y;
	
	// Get cross product of line vectors
	double LengthCross = Position::XYCrossProduct(lineA->LengthVec(), lineB->LengthVec());

	// Return if LengthCross is 0. This means there's no intersection.
	if (LengthCross == 0.0)
		return false;

	// Get intersections
	Position intersect;
	intersect.x = Position::XYCrossProduct(linesBeginDist, lineB->LengthVec()) / LengthCross;
	intersect.y = Position::XYCrossProduct(linesBeginDist, lineA->LengthVec()) / LengthCross;

	// If both cross paths, return true
	if (intersect.x >= 0 && intersect.x <= 1 && intersect.y >= 0 && intersect.y <= 1)
		return true;
	// If they don't cross, return false
	else
		return false;
}

Position Line::IntersectAt(Line* lineA, Line* lineB)
{
	// If slopes are parallel, return nullptr.
	//if (lineA->Slope() - lineB->Slope() == 0)
	//	return nullptr;
	
	Position pos;
	
	pos.x = 0;
	pos.y = 0;
	
	// If slopes are parallel, return nullptr.
	if (lineA->Slope() - lineB->Slope() == 0)
		return pos;

	//pos->x = (lineB->Intercept() - lineA->Intercept()) / (lineA->Slope() - lineB->Slope());
	//pos->y = lineA->Slope() * pos->x + lineA->Intercept();
	
	
	pos.x = 
		(((lineA->Begin->x * lineA->End->y) - (lineA->Begin->y * lineA->End->x)) * (lineB->Begin->x - lineB->End->x) -
		((lineB->Begin->x * lineB->End->y) - (lineB->Begin->y * lineB->End->x)) * (lineA->Begin->x - lineA->End->x)) /
		((lineA->Begin->x - lineA->End->x) * (lineB->Begin->y - lineB->End->y) - 
		(lineA->Begin->y - lineA->End->y) * (lineB->Begin->x - lineB->End->x));

	pos.y = 
		(((lineA->Begin->x * lineA->End->y) - (lineA->Begin->y * lineA->End->x)) * (lineB->Begin->y - lineB->End->y) -
		((lineB->Begin->x * lineB->End->y) - (lineB->Begin->y * lineB->End->x)) * (lineA->Begin->y - lineA->End->y)) /
			((lineA->Begin->x - lineA->End->x) * (lineB->Begin->y - lineB->End->y) -
		(lineA->Begin->y - lineA->End->y) * (lineB->Begin->x - lineB->End->x));
	

	return pos;
}



