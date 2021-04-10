#ifndef _CARD_H_
#define _CARD_H_

#include <string>
#include <vector>
#include "Point2D.h"

class Card
{
private:
	std::vector<Point2D> _jumpOffsetOption;
	std::string _name;
	bool _isRedStartPlayer;
	std::vector<Point2D> _jumpOffsetOptionRotated;

public:
	Card(std::string inName,	bool inIsRedStartPlayer);
	void AddJumpOption(Point2D inOption);
	std::string GetName();
	std::vector<Point2D> GetJumpOptions(bool inIsRedPlayer);
	//TODO(Simon): Implement this if really neccessary
	//void GiveOptionenRotated();

};

#endif


