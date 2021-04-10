#ifndef _POINT2D_H_
#define _POINT2D_H_


struct Point2D
{
	Point2D(int inX, int inY)
		:X(inX), Y(inY) {}
	int X;
	int Y;
};

#endif