

#include "GamestartMessage.h"

GamestartMessage::GamestartMessage()
	:OnitamaMessage("Gamestart", 40)
{

}


void GamestartMessage::SetCard1(std::string inCard1)
{
	_card1 = inCard1;
}

void GamestartMessage::SetCard2(std::string inCard2)
{
	_card2 = inCard2;
}

void GamestartMessage::SetOppoCard1(std::string inOppoCard1)
{
	_oppoCard1 = inOppoCard1;
}

void GamestartMessage::SetOppoCard2(std::string inOppoCard2)
{
	_oppoCard2 = inOppoCard2;
}

void GamestartMessage::SetCenterCard(std::string inCenterCard)
{
	_centerCard = inCenterCard;
}

void GamestartMessage::SetStartingPlayer(bool inStartingPlayer)
{
	_isStartingPlayer = inStartingPlayer;
}



void GamestartMessage::ParseContent(std::string inMessageContent)
{
	CutParameterDto cp = CutNextParameter(inMessageContent);
	if (!cp.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_isStartingPlayer = cp.GetParameter() == "First";

	CutParameterDto cp2 = CutNextParameter(cp.GetContentRest());
	if (!cp2.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_card1 = cp2.GetParameter();

	CutParameterDto cp3 = CutNextParameter(cp2.GetContentRest());
	if (!cp3.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_card2 = cp3.GetParameter();

	CutParameterDto cp4 = CutNextParameter(cp3.GetContentRest());
	if (!cp4.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_oppoCard1 = cp4.GetParameter();

	CutParameterDto cp5 = CutNextParameter(cp4.GetContentRest());
	if (!cp5.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_oppoCard2 = cp5.GetParameter();

	CutParameterDto cp6 = CutNextParameter(cp5.GetContentRest());
	if (!cp6.GetSuccessStatus())
	{
		//return "";
		return;
	}
	_centerCard = cp6.GetParameter();

	return ;	
}

std::string GamestartMessage::ToString()
{
	std::string ret = _messageName + ":";
	if (_isStartingPlayer)
	{
		ret += "First,";
	}
	else
	{
		ret += "Second,";
	}

	ret += _card1 + ",";
	ret += _card2 + ",";
	ret += _oppoCard1 + ",";
	ret += _oppoCard2 + ",";
	ret += _centerCard + ",;";
	return ret;
}