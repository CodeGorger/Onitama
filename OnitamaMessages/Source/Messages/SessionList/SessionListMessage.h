#ifndef _SESSIONLISTMESSAGE_H_
#define _SESSIONLISTMESSAGE_H_

#include "../OnitamaMessage.h"

#include <vector>

class SessionListMessage :public OnitamaMessage
{
public:
	SessionListMessage();
	void AddSessionName(std::string inSession);

	std::string ToString();
	void ParseContent(std::string inMessageContent);

private:
	std::vector<std::string> _sessionNames;
};

#endif
