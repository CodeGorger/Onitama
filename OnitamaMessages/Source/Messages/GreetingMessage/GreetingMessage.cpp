

#include "GreetingMessage.h"

StaticOnitamaMessageCtor GreetingMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("Greeting"), GreetingMessage::CreateSelf);

GreetingMessage::GreetingMessage()
	:OnitamaMessage("Greeting", 40)
	,_playerName("")
{

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

std::string GreetingMessage::ToString()
{
	return _messageName + ":" + _playerName + ",;";
}

std::shared_ptr<OnitamaMessage> GreetingMessage::CreateSelf()
{
	return std::make_shared<GreetingMessage>();
}



std::string GreetingMessage::GetPlayerName()
{
	return _playerName;
}

void GreetingMessage::SetPlayerName(std::string inPlayerName)
{
	_playerName = inPlayerName;
}

