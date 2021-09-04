#ifndef _SESSIONLISTMESSAGE_H_
#define _SESSIONLISTMESSAGE_H_

#include "../OnitamaMessage.h"

#include <vector>

class SessionListMessage :public OnitamaMessage
{
public:
	SessionListMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void AddSessionName(std::string inSession);

	std::vector<std::string> GetSessionNames();

private:
	static StaticOnitamaMessageCtor _staticCtor;
	std::vector<std::string> _sessionNames;

};

#endif
