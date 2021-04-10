#ifndef _POINT2D_H_
#define _POINT2D_H_


struct Point2D
{
	Point2D(int inX, int inY)
		:X(inX), Y(inY) {}
	int X;
	int Y;
};

bool static inline operator== (Point2D first, Point2D second)
{
	if ((first.X == second.X) && (first.Y == second.Y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif