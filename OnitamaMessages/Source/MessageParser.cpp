
#include "MessageParser.h"

#include "Messages/OnitamaMessage.h"

#define MAX_MSG_NAME_LENGTH 30
#define MAX_MSG_LENGTH 1024


MessageParsedDTO::MessageParsedDTO()
:_result(MessageStringResult::MessageStringResult_NotInited)
{
}

void MessageParsedDTO::SetMessage(std::shared_ptr<OnitamaMessage> inMsg)
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

std::shared_ptr<OnitamaMessage>  MessageParsedDTO::GetOnitamaMessage()
{
	return _message;
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
	int firstSemicolonPos = inMessageString.find_first_of(';');
	if (-1 == firstSemicolonPos &&
		MAX_MSG_LENGTH > inMessageString.length())
	{
		ret.SetResult( MessageStringResult::MessageStringResult_PossibleBeginning);
		return ret;
	}

	// No endmessage symbol found but already over the maximal length
	if (-1 == firstSemicolonPos &&
		MAX_MSG_NAME_LENGTH <= inMessageString.length())
	{
		// Nothing found, but trash because too long string!
		ret.SetResult(MessageStringResult::MessageStringResult_TooLongNotComplete);
		return ret;
	}

	// It is certain now that we found a ';'

	int firstColonPos = inMessageString.find_first_of(':');
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
	// (which might be incomplete, wrong or any
	// number of later received messages).
	std::string restString =
		inMessageString.substr(
			firstSemicolonPos + 1);

	if (StaticOnitamaMessageCtor::HasMessage(tmpMessageName))
	{
		std::shared_ptr<OnitamaMessage> tmpMsg;
		tmpMsg = StaticOnitamaMessageCtor::GetMessageCreator(tmpMessageName)();
		ret.SetMessage(tmpMsg);
	}
	else
	{
		ret.SetResult(MessageStringResult::MessageStringResult_MessageNotKnown);
		return ret;
	}
	

	ret.GetOnitamaMessage()->ParseContent(tmpContent);
	ret.SetRest(restString);
	ret.SetResult(MessageStringResult::MessageStringResult_Complete);

	return ret;
}
