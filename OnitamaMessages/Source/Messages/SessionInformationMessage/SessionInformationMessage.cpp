

#include "SessionInformationMessage.h"

StaticOnitamaMessageCtor SessionInformationMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("SessionInformation"), SessionInformationMessage::CreateSelf);

SessionInformationMessage::SessionInformationMessage()
	:OnitamaMessage("SessionInformation", 40)
{

}

void SessionInformationMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_oppoName = cp.GetParameter();

	CutParameterDto cp2 = CutNextParameter(cp.GetContentRest());
	if (!cp2.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_isHost = (cp2.GetParameter() == "Host");

	return;
}


std::string SessionInformationMessage::ToString()
{
	std::string ret = _messageName + ":";
	ret += _oppoName + ",";
	ret += (_isHost ? "Host" : "Guest");
	ret += ",;";
	return ret;
}


std::shared_ptr<OnitamaMessage> SessionInformationMessage::CreateSelf()
{
	return std::make_shared<SessionInformationMessage>();
}



std::string SessionInformationMessage::GetOppoName()
{
	return _oppoName;
}
void SessionInformationMessage::SetOppoName(std::string inOppoName)
{
	_oppoName = inOppoName;
}

bool SessionInformationMessage::IsHost()
{
	return _isHost;
}
void SessionInformationMessage::SetIsHost(bool inIsHost)
{
	_isHost = inIsHost;
}

