#ifndef _POSITION_H_
#define _POSITION_H_

#include <vector>

class Position {
public:
	typedef std::vector<Position*> Vec;
	typedef Vec::iterator VecIter;

	double x, y, xspd, yspd, gspd, ang;

	Position();
	
	static double XYCrossProduct(Position pos1, Position pos2);
};

#endif
