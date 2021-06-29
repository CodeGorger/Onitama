#include "Card.h"



Card::Card()
	: _isInited(false)
	, _isRedStartPlayer(true)
{
	
}


Card::Card(std::string inName, bool inIsRedStartPlayer)
	: _name(inName)
	, _isRedStartPlayer(inIsRedStartPlayer)
	, _isInited(true)
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

std::vector<std::vector<char>> Card::GetGridRed()
{
	//_jumpOffsetOption
	std::vector < std::vector <char>> grid;
	grid = std::vector < std::vector <char>>();
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid[2][2] = 'x';

	for(unsigned int i=0;i<_jumpOffsetOption.size(); i++)
	{
		int xo = _jumpOffsetOption[i].GetX() + 2;
		int yo = _jumpOffsetOption[i].GetY() + 2;
		grid[yo][xo] = 'o';
	}
	return grid;
}
std::string Card::GetGridStringRed()
{
	std::vector<std::vector<char>> grid;
	grid = GetGridRed();

	std::string ret = "";

	//TODO(Simon): _boardSize must be defined somewhere global
	int _boardSize = 5;
	for (int yy = _boardSize, y = _boardSize-1; yy > 0; yy--, y--)
	{
		for (int x = 0; x < _boardSize; x++)
		{
			ret += grid[y][x];
		}
		ret += "\n";
	}

	return ret;
}


std::vector<std::vector<char>> Card::GetGridBlue()
{
	std::vector < std::vector <char>> grid;
	grid = std::vector < std::vector <char>>();
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid.push_back({
			'.', '.', '.', '.', '.'
		});
	grid[2][2] = 'x';

	for (unsigned int i = 0; i < _jumpOffsetOptionRotated.size(); i++)
	{
		int xo = _jumpOffsetOptionRotated[i].GetX() + 2;
		int yo = _jumpOffsetOptionRotated[i].GetY() + 2;
		grid[yo][xo] = 'o';
	}
	return grid;
}


std::string Card::GetGridStringBlue()
{
	std::vector<std::vector<char>> grid;
	grid = GetGridBlue();

	std::string ret = "";

	//TODO(Simon): _boardSize must be defined somewhere global
	int _boardSize = 5;
	for (int yy = _boardSize, y = _boardSize-1; yy > 0; yy--, y--)
	{
		for (int x = 0; x < _boardSize; x++)
		{
			ret += grid[y][x];
		}
		ret += "\n";
	}

	return ret;
}

