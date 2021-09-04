#include "GamestartRequestMessage.h"
#include <iostream>

StaticOnitamaMessageCtor GamestartRequestMessage::_staticCtor =
StaticOnitamaMessageCtor(std::string("GamestartRequest"), GamestartRequestMessage::CreateSelf);


GamestartRequestMessage::GamestartRequestMessage()
	:OnitamaMessage("GamestartRequest", 40)
{

}

void GamestartRequestMessage::ParseContent(std::string inMessageContent)
{

}

std::string GamestartRequestMessage::ToString()
{
	return _messageName + ":,;";
}

std::shared_ptr<OnitamaMessage> GamestartRequestMessage::CreateSelf()
{
	return std::make_shared<GamestartRequestMessage>();
}
