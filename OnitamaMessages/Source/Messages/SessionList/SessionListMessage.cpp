

#include "SessionListMessage.h"

SessionListMessage::SessionListMessage()
	:OnitamaMessage("SessionList", 40)
{

}


void SessionListMessage::AddSessionName(std::string inSession)
{
	_sessionNames.push_back(inSession);
}


std::vector<std::string> SessionListMessage::GetSessionNames()
{
	return _sessionNames;
}

std::string SessionListMessage::ToString()
{
	std::string ret  = _messageName+":";
	for (int i = 0; i < _sessionNames.size(); i++)
	{
		ret+=_sessionNames[i]+",";
	}
	ret += ";";
	return ret;
}


void SessionListMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	while(cp.GetSuccessStatus())
	{
		_sessionNames.push_back(cp.GetParameter());
		cp = CutNextParameter(cp.GetContentRest());		
	}

	return ;
}