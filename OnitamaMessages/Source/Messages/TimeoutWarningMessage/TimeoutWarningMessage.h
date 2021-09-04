#ifndef _TIMEOUTWARNINGMESSAGE_H_
#define _TIMEOUTWARNINGMESSAGE_H_

#include "../OnitamaMessage.h"

class TimeoutWarningMessage :public OnitamaMessage
{
public:
	TimeoutWarningMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void SetTurnTimeLeftInS(int inTurnTimeLeftInS)
	{
		_turnTimeLeftInS = inTurnTimeLeftInS;
	}
	int GetTurnTimeLeftInS()
	{
		return _turnTimeLeftInS;
	}
	void SetTurnTimeLimitInS(int inTurnTimeLimitInS)
	{
		_turnTimeLimitInS = inTurnTimeLimitInS;
	}
	void SetGameTimeLeftInS(int inGameTimeLeftInS)
	{
		_gameTimeLeftInS = inGameTimeLeftInS;
	}
	void SetGameTimeLimitInS(int inGameTimeLimitInS)
	{
		_gameTimeLimitInS = inGameTimeLimitInS;
	}

private:
	static StaticOnitamaMessageCtor _staticCtor;

	int _turnTimeLeftInS;
	int _turnTimeLimitInS;
	int _gameTimeLeftInS;
	int _gameTimeLimitInS;

};

#endif