#ifndef _GAMESTARTMAMESSAGE_H_
#define _GAMESTARTMAMESSAGE_H_

#include "../OnitamaMessage.h"

class GamestartMessage :public OnitamaMessage
{
public:
	GamestartMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();

	void SetCard1(std::string inCard1);
	void SetCard2(std::string inCard2);
	void SetOppoCard1(std::string inOppoCard1);
	void SetOppoCard2(std::string inOppoCard2);
	void SetCenterCard(std::string inCenterCard);

	void SetStartingPlayer(bool inStartingPlayer);


private:
	bool _isStartingPlayer;

	std::string _card1;
	std::string _card2;
	std::string _oppoCard1;
	std::string _oppoCard2;
	std::string _centerCard;

};

#endif
