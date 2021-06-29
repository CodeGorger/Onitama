
#include "MessageParser.h"

#include "Messages/OnitamaMessage.h"
#include "Messages/Greeting/GreetingMessage.h"
#include "Messages/GamestartRequest/GamestartRequestMessage.h"
#include "Messages/Gamestart/GamestartMessage.h"
#include "Messages/InvalidMove/InvalidMoveMessage.h"
#include "Messages/Gameover/GameoverMessage.h"
#include "Messages/Move/MoveMessage.h"

#define MAX_MSG_NAME_LENGTH 30
#define MAX_MSG_LENGTH 1024


MessageParsedDTO::MessageParsedDTO() {}
void MessageParsedDTO::SetMessage(std::unique_ptr<OnitamaMessage> inMsg)
{
	_message = std::move(inMsg);
}

void MessageParsedDTO::SetRest(std::string inMessageRest)
{
	_messageRest = inMessageRest;
}

void MessageParsedDTO::SetResult(MessageStringResult inResult)
{
	_result = inResult;
}

OnitamaMessage* MessageParsedDTO::GetOnitamaMessage()
{
	return _message.get();
}

MessageStringResult MessageParsedDTO::GetResult()
{
	return _result;
}

std::string MessageParsedDTO::GetRest()
{
	return _messageRest;
}

// Will take a string and try to split of a message from it.
// It will return three things
// 1. Success / Fail (Status)
// 2. The message
// 3. The rest of the of the string
//
// "Greeting:Simon,;"
MessageParsedDTO ParseMessage(std::string inMessageString)
{
	MessageParsedDTO ret;

	// No endmessage symbol found but not yet at the maximal length
	size_t firstSemicolonPos = inMessageString.find_first_of(';');
	if (-1 == firstSemicolonPos &&
		MAX_MSG_LENGTH <= inMessageString.length())
	{
		ret.SetResult( MessageStringResult::MessageStringResult_PossibleBeginning);
		return ret;
	}

	// No endmessage symbol found but already over the maximal length
	if (-1 == firstSemicolonPos &&
		MAX_MSG_NAME_LENGTH > inMessageString.length())
	{
		// Nothing found, but trash because too long string!
		ret.SetResult(MessageStringResult::MessageStringResult_TooLongNotComplete);
		return ret;
	}


	size_t firstColonPos = inMessageString.find_first_of(':');
	if (-1 == firstColonPos)
	{
		//There should be a colon if there is a semicolon
		ret.SetResult(MessageStringResult::MessageStringResult_Trash);
		return ret;
	}

	if(firstColonPos > firstSemicolonPos)
	{
		//There should be a colon before the any semicolon
		ret.SetResult(MessageStringResult::MessageStringResult_Trash);
		return ret;
	}

	//Parse the msg name and the msg content (seperately)
	std::string tmpMessageName = inMessageString.substr(0, firstColonPos);
	std::string tmpContent = 
		inMessageString.substr(
			firstColonPos + 1, 
			firstSemicolonPos - firstColonPos);

	// Also already cut of the rest of the message 
	// (which might be imcomplete, wrong or any
	// number of later received messages).
	std::string restString =
		inMessageString.substr(
			firstSemicolonPos + 1);

	if (tmpMessageName == "Greeting")
	{
		ret.SetMessage(
			std::make_unique<GreetingMessage>(
				GreetingMessage()));
	}
	else if (tmpMessageName == "GamestartRequest")
	{
		ret.SetMessage(
			std::make_unique<GamestartRequestMessage>(
				GamestartRequestMessage()));
	}
	else if (tmpMessageName == "Gamestart")
	{
		ret.SetMessage(
			std::make_unique<GamestartMessage>(
				GamestartMessage()));
	}
	else if (tmpMessageName == "InvalidMove")
	{
		ret.SetMessage(
			std::make_unique<InvalidMoveMessage>(
				InvalidMoveMessage()));
	}
	else if (tmpMessageName == "Move")
	{
		ret.SetMessage(
			std::make_unique<MoveMessage>(
				MoveMessage()));
	}
	else if (tmpMessageName == "Gameover")
	{
		ret.SetMessage(
			std::make_unique<GameoverMessage>(
				GameoverMessage()));
	}

	ret.GetOnitamaMessage()->ParseContent(tmpContent);
	ret.SetRest(restString);
	ret.SetResult(MessageStringResult::MessageStringResult_Complete);

	return ret;
}
