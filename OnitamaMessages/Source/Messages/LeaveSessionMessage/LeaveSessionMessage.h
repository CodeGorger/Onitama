#ifndef _LEAVESESSIONMESSAGE_H_
#define _LEAVESESSIONMESSAGE_H_

#include "../OnitamaMessage.h"

class LeaveSessionMessage :public OnitamaMessage
{
public:
	LeaveSessionMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

private:
	static StaticOnitamaMessageCtor _staticCtor;

};

#endif
