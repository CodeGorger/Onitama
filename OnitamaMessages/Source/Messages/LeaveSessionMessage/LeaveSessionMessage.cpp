

#include "LeaveSessionMessage.h"

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
