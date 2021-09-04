
#include "GameSession.h"


GameSession::GameSession()
{
	srand(time(NULL));

	std::string randomLoggerId = std::to_string(rand() % 1000000);
	std::string id =
		std::string(6 - randomLoggerId.length(), '0') + randomLoggerId;
	l = spdlog::stdout_color_mt("GameS" + id);
#ifdef DEBUGLOGGING
	l->set_level(spdlog::level::debug);
#endif
}

std::string GameSession::GetSessionName()
{
	return _sessionName;
}

void GameSession::SetSessionName(std::string inSessionName)
{
	_sessionName = inSessionName;
}

void GameSession::SetConnEntityRed(std::shared_ptr<ConnEntity> inConnectionEntity)
{
	l->debug("SetConnEntityRed");
	_connEntityRed = inConnectionEntity;
}

void GameSession::SetConnEntityBlue(std::shared_ptr<ConnEntity> inConnectionEntity)
{
	l->debug("SetConnEntityBlue");
	_connEntityBlue = inConnectionEntity;
}

//TODO(Simon): This should be an enum...
// -1 ... B wishes to leave the session
// -2 ... A wishes to leave the session
// -3 ... A & B wishes to leave the session
// -4 ... A wishes to start the session
//  1 ... Error
//  2 ... Error
//  3 ... Error
int GameSession::ReadStartRequestAndLeaveSessionMessages()
{
	if (!_connEntityRed && !_connEntityBlue)
	{
		return 1;
	}
	if (!_connEntityRed)
	{
		return 2;
	}

	int a = 1;
	int b = 1;
	if (_connEntityRed)
	{
		a= _connEntityRed->ReadStartRequestAndLeaveSessionMessage();
	}
	if (_connEntityBlue)
	{
		b= _connEntityBlue->ReadStartRequestAndLeaveSessionMessage();
	}

	// Check if they want to leave the session
	// Must be checked with both together, or else the
	// message might be lost.
	if (-1 == a && -1 == b)
	{
		return -3;
	}
	if (-1 == a)
	{
		return -2;
	}
	if (-1 == b)
	{
		return -1;
	}

	// Ok, no leaving requested. If started now the 
	// wishes for leaving are too late.
	if (-2 == a)
	{
		return -4;
	}
	return 3;
}


bool GameSession::HasTwoPlayer()
{
	bool si = false;
	bool oi = false;
	if (_connEntityRed)
	{
		si = _connEntityRed->IsInited();
	}
	if (_connEntityBlue)
	{
		oi = _connEntityBlue->IsInited();
	}
	return (si && oi);
}


// Returns a smartpointer to the red player.
std::shared_ptr<ConnEntity> GameSession::GetPlayerRed()
{
	return _connEntityRed;
}


// Returns a smartpointer to the blue player.
std::shared_ptr<ConnEntity> GameSession::GetPlayerBlue()
{
	return _connEntityBlue;
}


// Check if both connections are closed,
// then the GameSession object can also be removed
bool GameSession::CheckConnectionsIfClosed()
{
	bool a = true;
	bool b = true;

	if (_connEntityRed)
	{
		//l->debug("CheckConnectionsIfClosed A");
		a = _connEntityRed->IsClosed();
	}
	if (_connEntityBlue)
	{
		//l->debug("CheckConnectionsIfClosed B");
		b = _connEntityBlue->IsClosed();
	}
	return a && b;
}
