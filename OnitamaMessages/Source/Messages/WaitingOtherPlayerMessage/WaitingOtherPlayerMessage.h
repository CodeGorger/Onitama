#ifndef _WAITINGOTHERPLAYERMESSAGE_H_
#define _WAITINGOTHERPLAYERMESSAGE_H_

#include "../OnitamaMessage.h"

class WaitingOtherPlayerMessage :public OnitamaMessage
{
public:
	WaitingOtherPlayerMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void SetTimeLimitInS(int inTotalLimit);
	void SetTimeLeftInS(int inTimeLeft);
	int GetTimeLeftInS();

private:
	static StaticOnitamaMessageCtor _staticCtor;

	int _totalLimitInS;
	int _timeLeftInS;

};

#endif