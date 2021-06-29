#ifndef _POINT2D_H_
#define _POINT2D_H_

#include <string>

class Point2D
{
private:
	int _x;
	int _y;

	bool _isEqual(Point2D rhs) const;
	Point2D _add(Point2D rhs) const;

public:
	Point2D(int inX, int inY)
		:_x(inX), _y(inY) {}

	std::string ToXyString();
	std::string ToChessString();
	bool ParseFromChessString(std::string inChessFormattedMove);
	Point2D GetRotated();

	bool operator== (Point2D second) const;
	Point2D operator+ (Point2D second) const;

	int GetX() { return _x; }
	int GetY() { return _y; }
	
};


#endif