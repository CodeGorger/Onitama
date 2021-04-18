#include "Card.h"





Card::Card(std::string inName, bool inIsRedStartPlayer)
	:_name(inName), _isRedStartPlayer(inIsRedStartPlayer)
{
	_jumpOffsetOption = std::vector<Point2D>();
	_jumpOffsetOptionRotated = std::vector<Point2D>();
}

void Card::AddJumpOption(Point2D inOption)
{
	_jumpOffsetOption.push_back(inOption);
	_jumpOffsetOptionRotated.push_back(inOption.GetRotated());
}

std::string Card::GetName()
{
	return _name;
}

std::vector<Point2D> Card::GetJumpOptions(bool inIsRedPlayer)
{
	if (inIsRedPlayer)
	{
		return _jumpOffsetOption;
	}
	else
	{
		return _jumpOffsetOptionRotated;
	}
}


