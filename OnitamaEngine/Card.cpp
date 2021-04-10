#include "Card.h"





Card::Card(std::string inName, bool inIsRedStartPlayer)
	:_name(inName), _isRedStartPlayer(inIsRedStartPlayer)
{
	_jumpOffsetOption = std::vector<Point2D>();
}

void Card::AddJumpOption(Point2D inOption)
{
	_jumpOffsetOption.push_back(inOption);
}




