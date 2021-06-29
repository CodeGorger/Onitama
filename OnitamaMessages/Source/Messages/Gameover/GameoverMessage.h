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

	void ParseContent(std::string inMessageContent);

	std::string ToString();

	void SetHasLost(bool inLost);
	void SetReason(EnumGameoverReason inReason);

private:
	bool _hasLost;
	EnumGameoverReason _reason;
};

#endif