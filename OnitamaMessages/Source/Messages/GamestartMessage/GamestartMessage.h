#ifndef _GAMESTARTMAMESSAGE_H_
#define _GAMESTARTMAMESSAGE_H_

#include "../OnitamaMessage.h"

class GamestartMessage :public OnitamaMessage
{
public:
	GamestartMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void SetCard1(std::string inCard1);
	void SetCard2(std::string inCard2);
	void SetOppoCard1(std::string inOppoCard1);
	void SetOppoCard2(std::string inOppoCard2);
	void SetCenterCard(std::string inCenterCard);
	void SetStartingPlayer(bool inStartingPlayer);
	void SetIsRedPlayer(bool inIsRedPlayer);
	void SetOppoName(std::string inOppoName);

	std::string GetCard1();
	std::string GetCard2();
	std::string GetOppoCard1();
	std::string GetOppoCard2();
	std::string GetCenterCard();
	bool GetStartingPlayer();
	bool GetIsRedPlayer();
	std::string GetOppoName();


private:
	static StaticOnitamaMessageCtor _staticCtor;

	bool _isStartingPlayer;
	bool _isRedPlayer;

	std::string _card1;
	std::string _card2;
	std::string _oppoCard1;
	std::string _oppoCard2;
	std::string _centerCard;
	std::string _oppoName;	

};

#endif
