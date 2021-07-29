#ifndef _LEAVESESSIONMESSAGE_H_
#define _LEAVESESSIONMESSAGE_H_

#include "../OnitamaMessage.h"

class LeaveSessionMessage :public OnitamaMessage
{
public:
	LeaveSessionMessage();
	void ParseContent(std::string inMessageContent);
	std::string ToString();

private:
};

#endif
