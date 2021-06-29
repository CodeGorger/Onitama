#ifndef _LOBBYTHREAD_H_
#define _LOBBYTHREAD_H_

#include "../Thread/ThreadHandler.h"
#include <vector>
#include "../ConnEntity/ConnEntity.h"
#include "../GameSession/GameSession.h"

class LobbyThread :public ThreadHandler
{

public:
	void SetConnectionInputQueue(
		std::shared_ptr<std::vector<ConnEntity>>
		inUngreetedConnectionsQueue);


private:
	void _do();

	// Takes new connections that have greeted properly
	void _checkUngreetedNewEntities();

	// Sends a list of all sessions to everyone in the lobby
	void _sendSessionList();

	// Handle join session requests
	void _handleJoinSession();

	// Handle start requests
	void _handleStartSession();

	int _addToExistingSession(
		std::string inSessionNameToJoin,
		int inLobbyId);

	void _createNewSession(
		std::string inSessionToJoin,
		int inConnectionIdInLobbyConnectionLost);

	void _handleOpenSessionTimeout();

	std::shared_ptr<std::vector<ConnEntity>>
		_ungreetedConnections;

	std::shared_ptr<std::vector<ConnEntity>>
		_lobbyConnections;

	std::shared_ptr<std::vector<GameSession>>
		_unstartedGameSessionList;

	std::shared_ptr<std::vector<GameSession>>
		_launchedGameSessionList;

};

#endif