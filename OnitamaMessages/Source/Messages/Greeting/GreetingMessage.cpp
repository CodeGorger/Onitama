

#include "GreetingMessage.h"

GreetingMessage::GreetingMessage()
	:OnitamaMessage("Greeting", 40)
	,_playerName("")
{

}


void GreetingMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp=CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_playerName = cp.GetParameter();
	//return cp.GetContentRest();
	return;
}


std::string GreetingMessage::GetPlayerName()
{
	return _playerName;
}


std::string GreetingMessage::ToString()
{
	return _messageName + ":" + _playerName + ",;";
}