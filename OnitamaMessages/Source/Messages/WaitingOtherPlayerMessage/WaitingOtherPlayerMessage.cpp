#include "WaitingOtherPlayerMessage.h"

StaticOnitamaMessageCtor WaitingOtherPlayerMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("WaitingOtherPlayer"), WaitingOtherPlayerMessage::CreateSelf);


WaitingOtherPlayerMessage::WaitingOtherPlayerMessage()
	:OnitamaMessage("WaitingOtherPlayer", 40)
	, _totalLimitInS(60)
	, _timeLeftInS(60)
{

}

void WaitingOtherPlayerMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_totalLimitInS = stoi(cp.GetParameter());

	CutParameterDto cp2 = CutNextParameter(cp.GetContentRest());
	if (!cp2.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_timeLeftInS = stoi(cp2.GetParameter());

	return;
}

std::string WaitingOtherPlayerMessage::ToString()
{
	std::string ret = _messageName + ":";
	ret += std::to_string(_totalLimitInS) + ",";
	ret += std::to_string(_timeLeftInS) + ",;";
	return ret;
}

std::shared_ptr<OnitamaMessage> WaitingOtherPlayerMessage::CreateSelf()
{
	return std::make_shared<WaitingOtherPlayerMessage>();
}




void WaitingOtherPlayerMessage::SetTimeLimitInS(int inTotalLimit)
{
	_totalLimitInS = inTotalLimit;
}


void WaitingOtherPlayerMessage::SetTimeLeftInS(int inTimeLeft)
{
	_timeLeftInS = inTimeLeft;
}

int WaitingOtherPlayerMessage::GetTimeLeftInS()
{
	return _timeLeftInS;
}

