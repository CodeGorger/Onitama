

#include "GreetingMessage.h"

GreetingMessage::GreetingMessage()
	:OnitamaMessage("Greeting", 40)
	,_playerName("")
{

}



std::string GreetingMessage::GetPlayerName()
{
	return _playerName;
}

void GreetingMessage::SetPlayerName(std::string inPlayerName)
{
	_playerName = inPlayerName;
}

std::string GreetingMessage::ToString()
{
	return _messageName + ":" + _playerName + ",;";
}


void GreetingMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_playerName = cp.GetParameter();
	//return cp.GetContentRest();
	return;
}