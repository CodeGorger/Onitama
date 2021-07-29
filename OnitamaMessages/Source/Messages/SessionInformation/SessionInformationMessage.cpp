

#include "SessionInformationMessage.h"

SessionInformationMessage::SessionInformationMessage()
	:OnitamaMessage("SessionInformation", 40)
{

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
	_isHost = (cp2.GetParameter()=="Host");

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

