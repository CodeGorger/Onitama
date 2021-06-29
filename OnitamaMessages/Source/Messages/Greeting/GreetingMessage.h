#ifndef _GREETINGMESSAGE_H_
#define _GREETINGMESSAGE_H_

#include "../OnitamaMessage.h"

class GreetingMessage :public OnitamaMessage
{
public:
	GreetingMessage();
	virtual void ParseContent(std::string inMessageContent);

	std::string GetPlayerName();
	std::string ToString();

private:
	std::string _playerName;
};

#endif
