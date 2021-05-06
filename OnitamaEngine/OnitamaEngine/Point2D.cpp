#include "Point2D.h"



bool Point2D::operator== (Point2D second) const
{
	return _isEqual(second);
}
bool Point2D::_isEqual(Point2D rhs) const
{
	if ((_x == rhs._x) && (_y == rhs._y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Point2D Point2D::operator+ (Point2D second) const
{
	return _add(second);
}
Point2D Point2D::_add(Point2D rhs) const
{
	return Point2D(_x + rhs._x, _y + rhs._y);
}



std::string Point2D::ToXyString()
{
	return std::string(std::to_string(_x) + ";" + std::to_string(_y));
}

std::string Point2D::ToChessString()
{
	return std::string(('A' + _x) + ";" + std::to_string(_y));
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
	_x = inChessFormattedMove[0] - 'A';
	_y = inChessFormattedMove[1] - '0';
	return true;
}

Point2D Point2D::GetRotated()
{
	return Point2D(-1 * _x, -1 * _y);
}

