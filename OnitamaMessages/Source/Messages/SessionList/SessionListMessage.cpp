

#include "SessionListMessage.h"

SessionListMessage::SessionListMessage()
	:OnitamaMessage("SessionList", 40)
{

}


void SessionListMessage::AddSessionName(std::string inSession)
{
	_sessionNames.push_back(inSession);
}

std::string SessionListMessage::ToString()
{
	std::string ret;
	for (int i = 0; i < _sessionNames.size(); i++)
	{
		ret+=_sessionNames[i]+",";
	}
	return ret;
}


void SessionListMessage::ParseContent(std::string inMessageContent)
{
	//TODO(Simon): Write this!
	return ;
}