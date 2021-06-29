#ifndef _JOINSESSIONMESSAGE_H_
#define _JOINSESSIONMESSAGE_H_

#include "../OnitamaMessage.h"

class JoinSessionMessage :public OnitamaMessage
{
public:
	JoinSessionMessage();
	void ParseContent(std::string inMessageContent);

	std::string GetSessionName();

private:
	std::string _sessionName;
};

#endif
