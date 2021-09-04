
#include "TimeoutWarningMessage.h"

StaticOnitamaMessageCtor TimeoutWarningMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("TimeoutWarning"), TimeoutWarningMessage::CreateSelf);

TimeoutWarningMessage::TimeoutWarningMessage()
	:OnitamaMessage("TimeoutWarning", 40)
	, _turnTimeLeftInS(60)
	, _turnTimeLimitInS(60)
	, _gameTimeLeftInS(600)
	, _gameTimeLimitInS(600)
{
}

void TimeoutWarningMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_turnTimeLeftInS = stoi(cp.GetParameter());

	CutParameterDto cp2 = CutNextParameter(cp.GetContentRest());
	if (!cp2.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_turnTimeLimitInS = stoi(cp2.GetParameter());

	CutParameterDto cp3 = CutNextParameter(cp2.GetContentRest());
	if (!cp3.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_gameTimeLeftInS = stoi(cp3.GetParameter());

	CutParameterDto cp4 = CutNextParameter(cp3.GetContentRest());
	if (!cp4.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_gameTimeLimitInS = stoi(cp4.GetParameter());

	return;
}

std::string TimeoutWarningMessage::ToString()
{
	std::string ret = _messageName + ":";
	ret += std::to_string(_turnTimeLeftInS ) + ",";
	ret += std::to_string(_turnTimeLimitInS) + ",";
	ret += std::to_string(_gameTimeLeftInS ) + ",";
	ret += std::to_string(_gameTimeLimitInS) + ",;";
	return ret;
}

std::shared_ptr<OnitamaMessage> TimeoutWarningMessage::CreateSelf()
{
	return std::make_shared<TimeoutWarningMessage>();
}



