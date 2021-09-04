#ifndef _GAMESTARTREQUESTMESSAGE_H_
#define _GAMESTARTREQUESTMESSAGE_H_

#include "../OnitamaMessage.h"

class GamestartRequestMessage :public OnitamaMessage
{
public:
	GamestartRequestMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();


private:
	static StaticOnitamaMessageCtor _staticCtor;

};

#endif


