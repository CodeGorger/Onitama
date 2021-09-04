#include "GameThread.h"
#include <Messages/GamestartMessage/GamestartMessage.h>
#include <Messages/GameoverMessage/GameoverMessage.h>
#include <Messages/WaitingOtherPlayerMessage/WaitingOtherPlayerMessage.h>
#include <iostream>
#include <Messages/TimeoutWarningMessage/TimeoutWarningMessage.h>
#include <Messages/InvalidMoveMessage/InvalidMoveMessage.h>
#include <Messages/MoveMessage/MoveMessage.h>
#include "../ConnEntity/ReadMoveInfoDto.h"

GameThread::GameThread(std::shared_ptr<GameSession> inGameSession)
	:_sessionInformation(inGameSession)
	,_turnTimeLimit(40)
	,_isGameOver(false)
{
	srand(time(NULL));

	l = spdlog::stdout_color_mt("GameThread");
#ifdef DEBUGLOGGING
	l->set_level(spdlog::level::debug);
#endif

	l->info("Created GameThread (red: {0}; blue: {1}).",
		_sessionInformation->GetPlayerRed()->GetPlayername(),
		_sessionInformation->GetPlayerBlue()->GetPlayername());

	_engine = OnitamaEngine();
	_sendPlayerACardsState(
		_engine.GetCurrentCardsRed()[0],
		_engine.GetCurrentCardsRed()[1],
		_engine.GetCurrentCardsBlue()[0],
		_engine.GetCurrentCardsBlue()[1],
		_engine.GetCenterCard());
	_sendPlayerBCardsState(
		_engine.GetCurrentCardsRed()[0],
		_engine.GetCurrentCardsRed()[1],
		_engine.GetCurrentCardsBlue()[0],
		_engine.GetCurrentCardsBlue()[1],
		_engine.GetCenterCard());

	// The first player gets an additional 5s
	_turnStartTime = clock();
	if (_turnStartTime >= 5 * CLOCKS_PER_SEC)
	{
		_turnStartTime -= 5 * CLOCKS_PER_SEC;
	}
	else
	{
		_turnStartTime = 0;
	}
}


void GameThread::SetLobbyConnections(
	ThreadSafeQueue<std::shared_ptr<ConnEntity>> inLobbyConnections)
{
	_lobbyConnections = inLobbyConnections;
}


// This is the entry point of the thread
void GameThread::_do()
{
	l->info("Starting Thread");
	_timedLoop();
	_sendPlayersBackToLobby();
	l->info("Stopping Thread");
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
	

	//TODO(Simon): Nullptr checking doesn't hurt. 
	//             This todo applies to here and the entire program.
	gsMes.SetOppoName(_sessionInformation->GetPlayerBlue()->GetPlayername());
	_sessionInformation->GetPlayerRed()->Send(gsMes.ToString());
}


void GameThread::_sendPlayerBCardsState(
	Card inR1,
	Card inR2,
	Card inB1,
	Card inB2,
	Card inC)
{

	GamestartMessage gsMes;
	//gsMes = GamestartMessage();

	gsMes.SetCard1(inB1.GetName());
	gsMes.SetCard2(inB2.GetName());
	gsMes.SetOppoCard1(inR1.GetName());
	gsMes.SetOppoCard2(inR2.GetName());
	gsMes.SetCenterCard(inC.GetName());

	gsMes.SetStartingPlayer(!inC.IsRedStartPlayer());

	gsMes.SetOppoName(_sessionInformation->GetPlayerRed()->GetPlayername());
	_sessionInformation->GetPlayerBlue()->Send(gsMes.ToString());
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
			l->info("Loop stalled: {0} ms", loopDurationInMs);
		}
		else
		{
			Sleep(1000 - loopDurationInMs);
		}
	}
	if (_isGameOver)
	{
		l->info("Game is over.");
	}
	if (_isShutdownRequested)
	{
		l->info("Shutdown is requested.");
	}
}


// Will execute _timedDo() maximally 1 each second
void GameThread::_timedDo()
{
	l->debug("_sendUnactivePlayerNotification");
	_sendUnactivePlayerNotification();

	l->debug("_sendActivePlayerTimeoutWarning");
	_sendActivePlayerTimeoutWarning();

	l->debug("_processActivePlayer");
	_processActivePlayer();

	l->debug("_checkForGameover");
	_checkForGameover();
}



void GameThread::_processActivePlayer()
{
	ReadMoveInfoDto rmid;
	if (_redsTurn)
	{
		l->debug("Reds turn");
		rmid = _sessionInformation->GetPlayerRed()->ReadMoveInfo();
	}
	else
	{
		l->debug("Blues turn");
		rmid = _sessionInformation->GetPlayerBlue()->ReadMoveInfo();
	}

	if (0 != rmid.GetReturnStatus())
	{
		l->debug("No move information received.");
		return;
	}
	l->debug("Move information received.");

	if (!_engine.ValidateMove(_redsTurn, rmid.GetMoveInfo()))
	{
		l->debug("Invalid move.");

		std::string invalidMoveReason = _engine.GetEngineStatus();
		_sendActivePlayerInvalidMove(
			invalidMoveReason, 
			rmid.GetMoveInfo().ToString());
		_turnStartTime = clock();
		return;
	}
	l->debug("Valid move.");
	
	_sendUnactivePlayerMoveInformation(rmid.GetMoveInfo().ToString());
	_engine.ApplyMove(rmid.GetMoveInfo().ToString());
}



void GameThread::_checkForGameover()
{
	int timeSinceTurnStart = ((clock() - _turnStartTime) / CLOCKS_PER_SEC);
	bool isTurnTimeout = 
		_turnTimeLimit < timeSinceTurnStart;
	if (isTurnTimeout)
	{
		l->info(
			"Turn timeout. Time limit: {0}s; Time since turn start: {1}s",
			_turnTimeLimit, 
			timeSinceTurnStart);
	}
	else
	{
		l->debug(
			"Turn timeout. Time limit: {0}s; Time since turn start: {1}s",
			_turnTimeLimit,
			timeSinceTurnStart);
	}


	//TODO(Simon): Accumulate time somewhere and check here
	bool isGameTimeout = false;
	if (isGameTimeout)
	{
		l->debug("isGameTimeout");
	}


	//TODO(Simon): Check if one is disconnected and inform the other
	bool isDisconnected = false;
	if (isGameTimeout)
	{
		l->debug("isDisconnected");
	}


	if (_engine.IsGameOver())
	{
		l->debug("Gameover by engine.");
	}
	
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
		_sessionInformation->GetPlayerBlue()->Send(wopMes.ToString());
	}
	else
	{
		_sessionInformation->GetPlayerRed()->Send(wopMes.ToString());
	}
}

void GameThread::_sendActivePlayerTimeoutWarning()
{
	TimeoutWarningMessage toMes = TimeoutWarningMessage();
	toMes.SetTurnTimeLimitInS(_turnTimeLimit);
	int timeLeftInSecs = (clock() - _turnStartTime) / CLOCKS_PER_SEC;
	toMes.SetTurnTimeLeftInS(timeLeftInSecs);
	if (_redsTurn)
	{
		_sessionInformation->GetPlayerRed()->Send(toMes.ToString());
	}
	else
	{
		_sessionInformation->GetPlayerBlue()->Send(toMes.ToString());
	}
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
		_sessionInformation->GetPlayerBlue()->Send(mMes.ToString());
	}
	else
	{
		_sessionInformation->GetPlayerRed()->Send(mMes.ToString());
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
		_sessionInformation->GetPlayerRed()->Send(goMesWin.ToString());
		_sessionInformation->GetPlayerBlue()->Send(goMesLoss.ToString());
	}
	else
	{
		_sessionInformation->GetPlayerRed()->Send(goMesLoss.ToString());
		_sessionInformation->GetPlayerBlue()->Send(goMesWin.ToString());
	}
}

void GameThread::_sendPlayersBackToLobby()
{
	_lobbyConnections.Enque(_sessionInformation->GetPlayerRed());
	_lobbyConnections.Enque(_sessionInformation->GetPlayerBlue());
}

