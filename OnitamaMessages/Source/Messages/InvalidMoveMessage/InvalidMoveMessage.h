#ifndef _INVALIDMOVEMAMESSAGE_H_
#define _INVALIDMOVEMAMESSAGE_H_

#include "../OnitamaMessage.h"

class InvalidMoveMessage :public OnitamaMessage
{
public:
	InvalidMoveMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void SetTheMove(std::string inMoveInformation);
	std::string GetTheMove();
	void SetReason(std::string inInvalidMoveReason);
	std::string GetReason();

private:
	static StaticOnitamaMessageCtor _staticCtor;
	std::string _move;
	std::string _reason;

};

#endif
