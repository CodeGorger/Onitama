
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

void GameSession::SetConnEntityA(std::shared_ptr<ConnEntity> inConnectionEntity)
{
	_connEntityA = inConnectionEntity;
}

void GameSession::SetConnEntityB(std::shared_ptr<ConnEntity> inConnectionEntity)
{
	_connEntityB = inConnectionEntity;
}


bool GameSession::ReadStartRequestSessionMessage()
{
	return (0 == _connEntityA->ReadStartRequestSessionMessage());
}


bool GameSession::HasTwoPlayer()
{
	bool si = _connEntityA->IsInited();
	bool oi = _connEntityB->IsInited();
	return (si && oi);
}



std::shared_ptr<ConnEntity> GameSession::GetPlayerA()
{
	return _connEntityA;
}


std::shared_ptr<ConnEntity> GameSession::GetPlayerB()
{
	return _connEntityB;
}



bool GameSession::CheckConnectionsIfClosed()
{
	return _connEntityA->IsClosed() && _connEntityB->IsClosed();
}