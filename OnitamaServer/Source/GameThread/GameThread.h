#ifndef _GAMETHREAD_H_
#define _GAMETHREAD_H_

#include <OnitamaEngine/OnitamaEngine.h>
#include "../GameSession/GameSession.h"
#include "../Thread/ThreadHandler.h"


class GameThread :public ThreadHandler
{
public:
	GameThread(GameSession inGameSession);
	void SetLobbyConnections(
		std::shared_ptr<std::vector<ConnEntity>> inLobbyConnections);

private:
	void _do();
	GameSession _sessionInformation;
	OnitamaEngine _engine;

	// Local instance that signals a game is over
	bool _isGameOver;

	// Which player is required to make a move
	bool _redsTurn;

	// Total time a turn may take
	int _turnTimeLimit;

	// Timestamp when the current turn started
	// required to determine timeouts
	int _turnStartTime;

	std::shared_ptr<std::vector<ConnEntity>>
		_lobbyConnections;

	void _sendPlayerACardsState(
		Card inR1,
		Card inR2,
		Card inB1,
		Card inB2,
		Card inC);

	void _sendPlayerBCardsState(
		Card inR1,
		Card inR2,
		Card inB1,
		Card inB2,
		Card inC);

	// Will execute _timedDo() maximally 1 each second
	void _timedLoop();

	// Will only be executed once a second, if the previous
	// iteration was fast: wait. If it was slower, immediately
	// start next iteration
	void _timedDo();
	void _processActivePlayer();
	void _checkForGameover();
	void _sendUnactivePlayerNotification();
	void _sendActivePlayerTimeoutWarning();

	void _sendActivePlayerInvalidMove(
		std::string inInvalidMoveReason,
		std::string inMoveInformation);

	void _sendUnactivePlayerMoveInformation(
		std::string inMoveInformation);

	void _sendGameoverMessageToBothPlayers(
		bool inIsGameTimeout,
		bool inIsTurnTimeout,
		bool isDisconnected);

	void _sendPlayersBackToLobby();
	void _terminate();
};


#endif

