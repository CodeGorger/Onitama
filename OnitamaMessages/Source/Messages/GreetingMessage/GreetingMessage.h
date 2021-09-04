#ifndef _GREETINGMESSAGE_H_
#define _GREETINGMESSAGE_H_

#include "../OnitamaMessage.h"

class GreetingMessage :public OnitamaMessage
{
public:
	GreetingMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	std::string GetPlayerName();
	void SetPlayerName(std::string);

private:
	static StaticOnitamaMessageCtor _staticCtor;
	std::string _playerName;

};

#endif
