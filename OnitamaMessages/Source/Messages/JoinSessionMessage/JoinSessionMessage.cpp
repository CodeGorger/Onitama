

#include "JoinSessionMessage.h"

JoinSessionMessage::JoinSessionMessage()
	:OnitamaMessage("JoinSession", 40)
{

}



std::string JoinSessionMessage::GetSessionName()
{
	return _sessionName;
}

void JoinSessionMessage::SetSessionName(std::string inSessionName)
{
	_sessionName = inSessionName;
}





void JoinSessionMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_sessionName = cp.GetParameter();
	//return cp.GetContentRest();
	return;
}

std::string JoinSessionMessage::ToString()
{
	return _messageName + ":" + _sessionName + ",;";
}