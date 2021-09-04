#ifndef _JOINSESSIONMESSAGE_H_
#define _JOINSESSIONMESSAGE_H_

#include "../OnitamaMessage.h"

class JoinSessionMessage :public OnitamaMessage
{
public:
	JoinSessionMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	std::string GetSessionName();
	void SetSessionName(std::string inSessionName);

private:
	static StaticOnitamaMessageCtor _staticCtor;
	std::string _sessionName;

};

#endif
