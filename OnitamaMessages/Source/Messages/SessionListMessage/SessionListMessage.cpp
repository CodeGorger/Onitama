

#include "SessionListMessage.h"

StaticOnitamaMessageCtor SessionListMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("SessionList"), SessionListMessage::CreateSelf);


SessionListMessage::SessionListMessage()
	:OnitamaMessage("SessionList", 40)
{

}

void SessionListMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	while (cp.GetSuccessStatus())
	{
		_sessionNames.push_back(cp.GetParameter());
		cp = CutNextParameter(cp.GetContentRest());
	}

	return;
}

std::string SessionListMessage::ToString()
{
	std::string ret = _messageName + ":";
	for (int i = 0; i < _sessionNames.size(); i++)
	{
		ret += _sessionNames[i] + ",";
	}
	ret += ";";
	return ret;
}

std::shared_ptr<OnitamaMessage> SessionListMessage::CreateSelf()
{
	return std::make_shared<SessionListMessage>();
}

void SessionListMessage::AddSessionName(std::string inSession)
{
	_sessionNames.push_back(inSession);
}


std::vector<std::string> SessionListMessage::GetSessionNames()
{
	return _sessionNames;
}


