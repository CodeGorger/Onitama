
#include "MoveInformation.h"


//TODO(Simon): Schreiben
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
				   

	_isInitialized = true;
}