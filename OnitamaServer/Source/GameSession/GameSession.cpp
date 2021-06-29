
#include "GameSession.h"


GameSession::GameSession()
{

}

std::string GameSession::GetSessionName()
{
	return _sessionName;
}

void GameSession::SetSessionName(std::string inSessionName)
{
	_sessionName = inSessionName;
}

void GameSession::SetConnEntityA(ConnEntity inConnectionEntity)
{
	_connEntityA = inConnectionEntity;
}

void GameSession::SetConnEntityB(ConnEntity inConnectionEntity)
{
	_connEntityB = inConnectionEntity;
}


bool GameSession::ReadStartRequestSessionMessage()
{
	return (0 == _connEntityA.ReadStartRequestSessionMessage());
}


bool GameSession::HasTwoPlayer()
{
	bool si = _connEntityA.IsInited();
	bool oi = _connEntityB.IsInited();
	return (si && oi);
}



ConnEntity GameSession::GetPlayerA()
{
	return _connEntityA;
}


ConnEntity GameSession::GetPlayerB()
{
	return _connEntityB;
}


