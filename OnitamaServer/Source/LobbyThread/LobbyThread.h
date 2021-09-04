#ifndef _LOBBYTHREAD_H_
#define _LOBBYTHREAD_H_

#include "../ThreadSafeQueue/ThreadSafeQueue.h"
#include "../Thread/ThreadHandler.h"
#include <vector>
#include "../ConnEntity/ConnEntity.h"
#include "../GameSession/GameSession.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Source/GameThread/GameThread.h>

class LobbyThread :public ThreadHandler
{

public:
	void SetConnectionInputQueue(
		ThreadSafeQueue< std::shared_ptr<ConnEntity>>
		inUngreetedConnectionsQueue);


private:
	void _do();
	void _timedLoop();
	void _timedDo();

	// Takes new connections that have greeted properly
	void _checkUngreetedNewEntities();

	// Sends a list of all sessions to everyone in the lobby
	void _sendSessionList();

	// Handle join session requests
	void _handleJoinSession();

	// Sends session information messages
	// to connections in sessions
	void _sendSessionInformation();

	// Handle start requests
	void _handleStartAndLeaveSession();

	int _addToExistingSession(
		std::string inSessionNameToJoin,
		int inLobbyId);

	void _createNewSession(
		std::string inSessionToJoin,
		int inConnectionIdInLobbyConnectionLost);

	// Will removed connections and maintain GameSession
	// with closed sockets
	void _removedClosedConnections();

	void _startStartableGames();

	void _handleOpenSessionTimeout();

	ThreadSafeQueue< std::shared_ptr<ConnEntity>>
		_ungreetedConnections;

	ThreadSafeQueue< std::shared_ptr<ConnEntity>>
		_lobbyConnections;

	ThreadSafeQueue< std::shared_ptr<GameSession>>
		_unstartedGameSessionList;

	ThreadSafeQueue< std::shared_ptr<GameSession>>
		_startableGameSessionList;

	ThreadSafeQueue< std::shared_ptr<GameThread>>
		_startedGamesList;

	std::shared_ptr<spdlog::logger> l;
};

#endif

