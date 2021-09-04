#include "MoveMessage.h"

StaticOnitamaMessageCtor MoveMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("Move"), MoveMessage::CreateSelf);


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

std::shared_ptr<OnitamaMessage> MoveMessage::CreateSelf()
{
	return std::make_shared<MoveMessage>();
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


