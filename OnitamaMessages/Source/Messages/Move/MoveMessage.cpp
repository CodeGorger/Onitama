#include "MoveMessage.h"


MoveMessage::MoveMessage()
	:OnitamaMessage("Move", 40)
{

}


void MoveMessage::ParseContent(
	std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_move = cp.GetParameter();
}


std::string MoveMessage::ToString()
{
	return
		_messageName + ":" +
		_move + ",;";
}


void MoveMessage::SetTheMove(
	std::string inMoveInformation)
{
	_move = inMoveInformation;
}


std::string MoveMessage::GetMove()
{
	return _move;
}


