
#include "MoveInformation.h"

bool MoveInformation::ParseMove(std::string inTcpMove)
{
	if (inTcpMove.size() > 20)
	{
		//"Invalid inTcpMove string is exceeded the maximal allowed length"
		return false;
	}

	int indexOfFirstSemicolon = inTcpMove.find_first_of(";");
	_cardName=inTcpMove.substr(0, indexOfFirstSemicolon);

	_figureStartPosition.ParseFromChessString(
		inTcpMove.substr(indexOfFirstSemicolon,2));

	_figureEndPosition.ParseFromChessString(
		inTcpMove.substr(indexOfFirstSemicolon+2, 2));
	
	//TODO(Simon): Mal �berlegen ob es nicht cooler w�re wenn
	//			   

	_isInitialized = true;
}