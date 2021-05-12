
#include <memory>
#include "Messages/OnitamaMessage.h"
#include "Messages/Greeting/GreetingMessage.h"
#include "Messages/GamestartRequest/GamestartRequestMessage.h"
#include "Messages/Gamestart/GamestartMessage.h"
#include "Messages/InvalidMove/InvalidMoveMessage.h"
#include "Messages/Move/MoveMessage.h"
#include "Messages/Gameover/GameoverMessage.h"

std::unique_ptr<OnitamaMessage> ParseMessage(
	std::string inMessageString)
{
	size_t firstSemicolonPos = inMessageString.find_first_of(';');
	std::string tmpMessageName = inMessageString.substr(0, firstSemicolonPos);
	
	std::unique_ptr<OnitamaMessage> ret;
	if (tmpMessageName == "Greeting")
	{
		ret=std::make_unique<OnitamaMessage>(GreetingMessage());
	}
	else if (tmpMessageName == "WaitingOppoTimeoutIn")
	{
	}
	else if (tmpMessageName == "WaitingOppoTimeoutFail")
	{
	}
	else if (tmpMessageName == "GamestartRequest")
	{
		ret = std::make_unique<OnitamaMessage>(GamestartRequestMessage());
	}
	else if (tmpMessageName == "Gamestart")
	{
		ret = std::make_unique<OnitamaMessage>(GamestartMessage());
	}
	else if (tmpMessageName == "InvalidMove")
	{
		ret = std::make_unique<OnitamaMessage>(InvalidMoveMessage());
	}
	else if (tmpMessageName == "Move")
	{
		ret = std::make_unique<OnitamaMessage>(MoveMessage());
	}
	else if (tmpMessageName == "WaitingMoveTimeoutIn")
	{
	}
	else if (tmpMessageName == "WaitingOppoMoveTimeoutIn")
	{
	}
	else if (tmpMessageName == "Gameover")
	{
		ret = std::make_unique<OnitamaMessage>(GameoverMessage());
	}
}