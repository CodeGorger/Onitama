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
	MessageStringResult_TooLongNotComplete,
	MessageStringResult_NotInited
};

class MessageParsedDTO
{
private:
	MessageStringResult _result;
	std::shared_ptr<OnitamaMessage> _message;
	std::string _messageRest;

public:
	MessageParsedDTO();
	void SetMessage(std::shared_ptr<OnitamaMessage> inMsg);
	void SetRest(std::string inMessageRest);
	void SetResult(MessageStringResult inResult);

	std::shared_ptr<OnitamaMessage>  GetOnitamaMessage();
	MessageStringResult GetResult();
	std::string GetRest();
};

MessageParsedDTO ParseMessage(std::string inMessageString);

#endif 