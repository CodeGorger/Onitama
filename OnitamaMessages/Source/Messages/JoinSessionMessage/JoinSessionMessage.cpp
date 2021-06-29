

#include "JoinSessionMessage.h"

JoinSessionMessage::JoinSessionMessage()
	:OnitamaMessage("JoinSession", 40)
{

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

std::string JoinSessionMessage::GetSessionName()
{
	return _sessionName;
}
