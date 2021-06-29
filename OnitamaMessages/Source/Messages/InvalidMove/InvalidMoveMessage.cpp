#include "InvalidMoveMessage.h"


InvalidMoveMessage::InvalidMoveMessage()
	:OnitamaMessage("InvalidMove", 40)
{

}


void InvalidMoveMessage::ParseContent(
	std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_move = cp.GetParameter();

	CutParameterDto cp2 = CutNextParameter(cp.GetContentRest());
	if (!cp2.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_reason = cp2.GetParameter();
}


std::string InvalidMoveMessage::ToString()
{
	return 
		_messageName + ":" +
		_move+","+
		_reason +",;";
}


void InvalidMoveMessage::SetTheMove(
	std::string inMoveInformation)
{
	_move = inMoveInformation;
}


void InvalidMoveMessage::SetReason(
	std::string inInvalidMoveReason)
{
	_reason = inInvalidMoveReason;
}

