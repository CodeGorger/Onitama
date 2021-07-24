#include "GameThread.h"
#include <Messages/Gamestart/GamestartMessage.h>
#include <Messages/Gameover/GameoverMessage.h>
#include <Messages/WaitingOtherPlayerMessage/WaitingOtherPlayerMessage.h>
#include <iostream>
#include <Messages/TimeoutWarningMessage/TimeoutWarningMessage.h>
#include <Messages/InvalidMove/InvalidMoveMessage.h>
#include <Messages/Move/MoveMessage.h>
#include "../ConnEntity/ReadMoveInfoDto.h"

GameThread::GameThread(GameSession inGameSession)
	:_sessionInformation(inGameSession)
	,_turnTimeLimit(40)
{
	_engine = OnitamaEngine();
	_sendPlayerACardsState(
		_engine.GetCurrentCardsRed()[0],
		_engine.GetCurrentCardsRed()[1],
		_engine.GetCurrentCardsBlue()[0],
		_engine.GetCurrentCardsBlue()[1],
		_engine.GetCenterCard());
	_sendPlayerBCardsState(
		_engine.GetCurrentCardsBlue()[0],
		_engine.GetCurrentCardsBlue()[1],
		_engine.GetCurrentCardsRed()[0],
		_engine.GetCurrentCardsRed()[1],
		_engine.GetCenterCard());
}


void GameThread::SetLobbyConnections(
	std::shared_ptr<std::vector<std::shared_ptr<ConnEntity>>> inLobbyConnections)
{
	_lobbyConnections = inLobbyConnections;
}


// This is the entry point of the thread
void GameThread::_do()
{
	_timedLoop();
	_sendPlayersBackToLobby();
}


void GameThread::_sendPlayerACardsState(
	Card inR1,
	Card inR2,
	Card inB1,
	Card inB2,
	Card inC)
{

	GamestartMessage gsMes;
	//gsMes = GamestartMessage();

	gsMes.SetCard1(inR1.GetName());
	gsMes.SetCard2(inR2.GetName());
	gsMes.SetOppoCard1(inB1.GetName());
	gsMes.SetOppoCard2(inB2.GetName());
	gsMes.SetCenterCard(inC.GetName());

	gsMes.SetStartingPlayer(inC.IsRedStartPlayer());
	_sessionInformation.GetPlayerA()->Send(gsMes.ToString());
}


void GameThread::_sendPlayerBCardsState(
	Card inB1,
	Card inB2,
	Card inR1,
	Card inR2,
	Card inC)
{

	GamestartMessage gsMes;
	//gsMes = GamestartMessage();

	gsMes.SetCard1(inR1.GetName());
	gsMes.SetCard2(inR2.GetName());
	gsMes.SetOppoCard1(inB1.GetName());
	gsMes.SetOppoCard2(inB2.GetName());
	gsMes.SetCenterCard(inC.GetName());

	gsMes.SetStartingPlayer(!inC.IsRedStartPlayer());
	_sessionInformation.GetPlayerB()->Send(gsMes.ToString());
}

// Will execute _timedDo() maximally 1 each second
void GameThread::_timedLoop()
{
	clock_t loopStart;
	clock_t loopEnd;
	clock_t loopDuration;
	unsigned int loopDurationInMs;
	while (!_isShutdownRequested && !_isGameOver)
	{
		loopStart = clock();
		{
			_timedDo();
		}

		loopEnd = clock();
		loopDuration = loopEnd - loopStart;
		loopDurationInMs = (loopDuration * 1000) / CLOCKS_PER_SEC;

		//loopStartInMs = ((loopStart - globalStart) * 1000) / CLOCKS_PER_SEC;
		//std::cout << "Start: " << loopStartInMs << "; Took: " 
		// << loopDurationInMs << " ms" << std::endl;

		if (loopDurationInMs > 1000)
		{
			std::cout << "Loop stalled: " << 
				loopDurationInMs << " ms" << std::endl;
		}
		else
		{
			Sleep(1000 - loopDurationInMs);
		}
	}
}


// Will execute _timedDo() maximally 1 each second
void GameThread::_timedDo()
{
	_sendUnactivePlayerNotification();
	_sendActivePlayerTimeoutWarning();
	_processActivePlayer();
	_checkForGameover();
}



void GameThread::_processActivePlayer()
{
	ReadMoveInfoDto rmid;
	if (_redsTurn)
	{
		rmid = _sessionInformation.GetPlayerA()->ReadMoveInfo();
	}
	else
	{
		rmid = _sessionInformation.GetPlayerB()->ReadMoveInfo();
	}

	if (0 != rmid.GetReturnStatus())
	{
		return;
	}

	if (!_engine.ValidateMove(_redsTurn, rmid.GetMoveInfo()))
	{
		std::string invalidMoveReason = _engine.GetEngineStatus();
		_sendActivePlayerInvalidMove(
			invalidMoveReason, 
			rmid.GetMoveInfo().ToString());
		_turnStartTime = clock();
		return;
	}
	
	_sendUnactivePlayerMoveInformation(rmid.GetMoveInfo().ToString());
	_engine.ApplyMove(rmid.GetMoveInfo().ToString());
}



void GameThread::_checkForGameover()
{
	bool isTurnTimeout = 
		_turnTimeLimit < ((clock() - _turnStartTime) / CLOCKS_PER_SEC);

	//TODO(Simon): Accumulate time somewhere and check here
	bool isGameTimeout = false;

	//TODO(Simon): Check if one is disconnected and inform the other
	bool isDisconnected = false;
	
	if (_engine.IsGameOver() ||
		isGameTimeout ||
		isTurnTimeout ||
		isDisconnected)
	{
		_sendGameoverMessageToBothPlayers(
			isGameTimeout,
			isTurnTimeout,
			isDisconnected);

		_isGameOver = true;
	}
}

void GameThread::_sendUnactivePlayerNotification()
{
	WaitingOtherPlayerMessage wopMes = WaitingOtherPlayerMessage();
	wopMes.SetTimeLimitInS(_turnTimeLimit);
	int timeLeftInSecs = (clock() - _turnStartTime) / CLOCKS_PER_SEC;
	wopMes.SetTimeLeftInS(timeLeftInSecs);
	if (_redsTurn)
	{
		_sessionInformation.GetPlayerB()->Send(wopMes.ToString());
	}
	else
	{
		_sessionInformation.GetPlayerA()->Send(wopMes.ToString());
	}
}

void GameThread::_sendActivePlayerTimeoutWarning()
{
	TimeoutWarningMessage toMes = TimeoutWarningMessage();
}

void GameThread::_sendActivePlayerInvalidMove(
	std::string inInvalidMoveReason,
	std::string inMoveInformation)
{
	InvalidMoveMessage imMes = InvalidMoveMessage();
	imMes.SetTheMove(inMoveInformation);
	imMes.SetReason(inInvalidMoveReason);
}

void GameThread::_sendUnactivePlayerMoveInformation(
	std::string inMoveInformation)
{
	MoveMessage mMes = MoveMessage();
	mMes.SetTheMove(inMoveInformation);

	if (_redsTurn)
	{
		_sessionInformation.GetPlayerB()->Send(mMes.ToString());
	}
	else
	{
		_sessionInformation.GetPlayerA()->Send(mMes.ToString());
	}
}

void GameThread::_sendGameoverMessageToBothPlayers(
	bool inIsGameTimeout,
	bool inIsTurnTimeout,
	bool isDisconnected)
{
	GameoverMessage goMesWin = GameoverMessage();
	GameoverMessage goMesLoss = GameoverMessage();
	
	// Timeout, Master Dead, Throne occupied
	EnumGameoverReason gor;

	if (inIsGameTimeout)
	{
		gor = EnumGameoverReason::EGR_GameTimeout;
	}
	else if (inIsTurnTimeout)
	{
		gor = EnumGameoverReason::EGR_TurnTimeout;
	}
	else if (isDisconnected)
	{
		gor = EnumGameoverReason::EGR_Disconnect;
	}
	else
	{	
		// normal gameover
		if (_engine.HasBlueLost_MasterTaken() ||
			_engine.HasRedLost_MasterTaken())
		{
			gor = EnumGameoverReason::EGR_MasterTaken;
		}
		else if (_engine.HasBlueLost_ThroneTaken() ||
		         _engine.HasRedLost_ThroneTaken())
		{
			gor = EnumGameoverReason::EGR_ThroneOccupied;
		}
		else
		{
			gor = EnumGameoverReason::EGR_Haeaeaeae;
		}
	}

	goMesWin.SetReason(gor);
	goMesLoss.SetReason(gor);
	goMesWin.SetHasLost(true);

	goMesLoss.SetHasLost(false);

	if (_engine.HasRedLost())
	{
		_sessionInformation.GetPlayerA()->Send(goMesWin.ToString());
		_sessionInformation.GetPlayerB()->Send(goMesLoss.ToString());
	}
	else
	{
		_sessionInformation.GetPlayerA()->Send(goMesLoss.ToString());
		_sessionInformation.GetPlayerB()->Send(goMesWin.ToString());
	}
}

void GameThread::_sendPlayersBackToLobby()
{
	_lobbyConnections->push_back(_sessionInformation.GetPlayerA());
	_lobbyConnections->push_back(_sessionInformation.GetPlayerB());
}

