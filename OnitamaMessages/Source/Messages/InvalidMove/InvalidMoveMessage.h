#ifndef _INVALIDMOVEMAMESSAGE_H_
#define _INVALIDMOVEMAMESSAGE_H_

#include "../OnitamaMessage.h"

class InvalidMoveMessage :public OnitamaMessage
{
public:
	InvalidMoveMessage();

	void ParseContent(std::string inMessageContent);

	std::string ToString();

	void SetTheMove(std::string inMoveInformation);
	void SetReason(std::string inInvalidMoveReason);

private:
	std::string _move;
	std::string _reason;

};

#endif
