#ifndef _GAMEOVERMESSAGE_H_
#define _GAMEOVERMESSAGE_H_

#include "../OnitamaMessage.h"


enum class EnumGameoverReason
{
	EGR_ThroneOccupied,
	EGR_MasterTaken,
	EGR_TurnTimeout,
	EGR_GameTimeout,
	EGR_Disconnect,
	EGR_Haeaeaeae
};

class GameoverMessage :public OnitamaMessage
{
public:
	GameoverMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void SetHasLost(bool inLost);
	void SetReason(EnumGameoverReason inReason);

private:
	static StaticOnitamaMessageCtor _staticCtor;

	bool _hasLost;
	EnumGameoverReason _reason;
};

#endif