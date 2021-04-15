#ifndef _POINT2D_H_
#define _POINT2D_H_


struct Point2D
{
	Point2D(int inX, int inY)
		:X(inX), Y(inY) {}
	int X;
	int Y;

	std::string ToXyString();
	std::string ToChessString();
	bool ParseFromChessString(std::string inChessFormattedMove);
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

std::string Point2D::ToXyString()
{
	return std::string(std::to_string(X)+";"+std::to_string(Y));
}

std::string Point2D::ToChessString()
{
	return std::string(('A' + X) + ";" + std::to_string(Y));
}

bool Point2D::ParseFromChessString(std::string inChessFormattedMove)
{
	if (inChessFormattedMove.size() != 2)
	{
		//"Chess notation has exactly string length 2 (not "
		// + inChessFormattedMove.length() + ")."
		return false;
	}
	if (inChessFormattedMove[0] < 'A' || 'E' < inChessFormattedMove[0])
	{
		//"The x location must be between A and E (is "
		// + inChessFormattedMove[0] + ")."
		return false;
	}
	if (inChessFormattedMove[1] < '1' || '5' < inChessFormattedMove[1])
	{
		//"The x location must be between 1 and 5 (is "
		// + inChessFormattedMove[0] + ")."
		return false;
	}
	X = inChessFormattedMove[0] - 'A';
	Y = inChessFormattedMove[1] - '0';
	return true;
}

#endif