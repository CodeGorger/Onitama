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
	bool _isInited;

public:
	Card();
	Card(std::string inName, bool inIsRedStartPlayer);
	void AddJumpOption(Point2D inOption);
	std::string GetName();
	std::vector<Point2D> GetJumpOptions(bool inIsRedPlayer);

	std::vector<std::vector<char>> GetGridRed();
	std::string GetGridStringRed();
	std::vector<std::vector<char>> GetGridBlue();
	std::string GetGridStringBlue();

	bool IsRedStartPlayer() { return _isRedStartPlayer; }
};

#endif


