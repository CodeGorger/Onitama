#ifndef _WAITINGOTHERPLAYERMESSAGE_H_
#define _WAITINGOTHERPLAYERMESSAGE_H_

#include "../OnitamaMessage.h"

class WaitingOtherPlayerMessage :public OnitamaMessage
{
public:
	WaitingOtherPlayerMessage();

	virtual void ParseContent(std::string inMessageContent);

	std::string ToString();

	void SetTimeLimitInS(int inTotalLimit);
	void SetTimeLeftInS(int inTimeLeft);

private:
	int _totalLimitInS;
	int _timeLeftInS;

};

#endif