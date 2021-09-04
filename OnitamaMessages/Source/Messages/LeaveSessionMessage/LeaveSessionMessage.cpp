

#include "LeaveSessionMessage.h"

StaticOnitamaMessageCtor LeaveSessionMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("LeaveSession"), LeaveSessionMessage::CreateSelf);

LeaveSessionMessage::LeaveSessionMessage()
	:OnitamaMessage("LeaveSession", 40)
{

}



void LeaveSessionMessage::ParseContent(std::string inMessageContent)
{
	//return cp.GetContentRest();
	return;
}

std::string LeaveSessionMessage::ToString()
{
	return _messageName + ":;";
}


std::shared_ptr<OnitamaMessage> LeaveSessionMessage::CreateSelf()
{
	return std::make_shared<LeaveSessionMessage>();
}
