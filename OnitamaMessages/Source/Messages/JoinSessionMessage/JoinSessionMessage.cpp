

#include "JoinSessionMessage.h"

StaticOnitamaMessageCtor JoinSessionMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("JoinSession"), JoinSessionMessage::CreateSelf);

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

std::string JoinSessionMessage::ToString()
{
	return _messageName + ":" + _sessionName + ",;";
}

std::shared_ptr<OnitamaMessage> JoinSessionMessage::CreateSelf()
{
	return std::make_shared<JoinSessionMessage>();
}



std::string JoinSessionMessage::GetSessionName()
{
	return _sessionName;
}

void JoinSessionMessage::SetSessionName(std::string inSessionName)
{
	_sessionName = inSessionName;
}



