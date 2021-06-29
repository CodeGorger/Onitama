#ifndef _MOVEMESSAGE_H_
#define _MOVEMESSAGE_H_

#include "../OnitamaMessage.h"

class MoveMessage :public OnitamaMessage
{
public:
	MoveMessage();
	void ParseContent(std::string inMessageContent);

	std::string ToString();

	void SetTheMove(std::string inMoveInformation);

	std::string GetMove();

private:
	std::string _move;

};

#endif
