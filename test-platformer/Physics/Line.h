#ifndef _LINE_H_
#define _LINE_H_

#include <vector>
#include <SDL2\SDL.h>
#include "Physics\Position.h"

class Line {
public:
	typedef std::vector <Line*> Vec;
	typedef Vec::iterator VecIter;

	Position::Vec		Points;
	Position*	Begin;
	Position*	End;

	Line();
	Line(double _x1, double _y1, double _x2, double _y2);
	void InitPoints();
	void SetPoints(double _x1, double _y1, double _x2, double _y2);
	void Translate(double _x, double _y);
	double Intercept();
	double Length();
	Position * LengthVec();
	double Slope();
	SDL_Rect* Rect();

	static bool HasIntersection(Line* line1, Line* line2);
	static Position* IntersectAt(Line* line1, Line* line2);
};


#endif
