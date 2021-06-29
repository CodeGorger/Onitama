#include "MoveInformation.h"

bool MoveInformation::ParseMove(std::string inTcpMove)
{
	if (inTcpMove.size() > 20)
	{
		//"Invalid inTcpMove string is exceeded the maximal allowed length"
		return false;
	}

	size_t indexOfFirstSemicolon = inTcpMove.find_first_of(";");
	_cardName=inTcpMove.substr(0, indexOfFirstSemicolon);

	_figureStartPosition.ParseFromChessString(
		inTcpMove.substr(indexOfFirstSemicolon,2));

	size_t indexOfFirstCharAfterSemicolon = indexOfFirstSemicolon + 2;
	_figureEndPosition.ParseFromChessString(
		inTcpMove.substr(indexOfFirstCharAfterSemicolon, 2));
				   

	_isInitialized = true;
	return true;
}


std::string MoveInformation::ToString()
{
	return 
		_cardName + ";" +
		_figureStartPosition.ToChessString() +
		_figureEndPosition.ToChessString();
}

