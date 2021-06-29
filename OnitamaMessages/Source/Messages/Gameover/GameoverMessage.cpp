

#include "GameoverMessage.h"

GameoverMessage::GameoverMessage()
	:OnitamaMessage("Gameover", 40)
	, _hasLost(true)
	, _reason(EnumGameoverReason::EGR_Haeaeaeae)

{

}

void GameoverMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_hasLost = cp.GetParameter()=="Defeat";

	CutParameterDto cp2 = CutNextParameter(cp.GetContentRest());
	if (!cp2.GetSuccessStatus())
	{
		//return "";
		return;
	}
	if ("ThroneOccupied" == cp2.GetParameter())
	{
		_reason = EnumGameoverReason::EGR_ThroneOccupied;
	}
	else if ("MasterTaken" == cp2.GetParameter())
	{
		_reason = EnumGameoverReason::EGR_MasterTaken;
	}
	else if ("TurnTimeout" == cp2.GetParameter())
	{
		_reason = EnumGameoverReason::EGR_TurnTimeout;
	}
	else if ("GameTimeout" == cp2.GetParameter())
	{
		_reason = EnumGameoverReason::EGR_GameTimeout;
	}
	else if ("Disconnect" == cp2.GetParameter())
	{
		_reason = EnumGameoverReason::EGR_Disconnect;
	}

	return;
}

std::string GameoverMessage::ToString()
{
	std::string ret = _messageName + ":";
	if (_hasLost)
	{
		ret += "Defeat,";
	}
	else
	{
		ret += "Victory,";
	}
	switch (_reason)
	{
	case EnumGameoverReason::EGR_ThroneOccupied:
		ret += "ThroneOccupied,";
		break;
	case EnumGameoverReason::EGR_MasterTaken:
		ret += "MasterTaken,";
		break;
	case EnumGameoverReason::EGR_TurnTimeout:
		ret += "TurnTimeout,";
		break;
	case EnumGameoverReason::EGR_GameTimeout:
		ret += "GameTimeout,";
		break;
	case EnumGameoverReason::EGR_Disconnect:
		ret += "Disconnect,";
		break;
	}
	return ret;
}


void GameoverMessage::SetHasLost(bool inLost)
{
	_hasLost = inLost;
}

void GameoverMessage::SetReason(EnumGameoverReason inReason)
{
	_reason = inReason;
}