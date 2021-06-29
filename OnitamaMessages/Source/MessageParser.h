#ifndef _MESSAGEPARSER_H_
#define _MESSAGEPARSER_H_

#include <memory>
#include <string>

class OnitamaMessage;

enum class MessageStringResult
{
	MessageStringResult_Complete,
	MessageStringResult_Trash,
	MessageStringResult_PossibleBeginning,
	MessageStringResult_TooLongNotComplete
};

class MessageParsedDTO
{
private:
	MessageStringResult _result;
	std::unique_ptr<OnitamaMessage> _message;
	std::string _messageRest;

public:
	MessageParsedDTO();
	void SetMessage(std::unique_ptr<OnitamaMessage> inMsg);
	void SetRest(std::string inMessageRest);
	void SetResult(MessageStringResult inResult);

	OnitamaMessage* GetOnitamaMessage();
	MessageStringResult GetResult();
	std::string GetRest();
};

MessageParsedDTO ParseMessage(std::string inMessageString);

#endif 