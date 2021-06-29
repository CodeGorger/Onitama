#ifndef _GAMESTARTREQUESTMESSAGE_H_
#define _GAMESTARTREQUESTMESSAGE_H_

#include "../OnitamaMessage.h"

class GamestartRequestMessage :public OnitamaMessage
{
public:
	GamestartRequestMessage();

	void ParseContent(std::string inMessageContent);
	std::string ToString();
};

#endif
