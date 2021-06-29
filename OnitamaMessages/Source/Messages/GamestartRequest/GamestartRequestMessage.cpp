

#include "GamestartRequestMessage.h"

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