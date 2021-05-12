#ifndef _LOBBYTHREAD_H_
#define _LOBBYTHREAD_H_

#include "../Thread/ThreadHandler.h"
#include <list>
#include "../ConnEntity/ConnEntity.h"

class LobbyThread :public ThreadHandler
{

public:
	void SetConnectionInputQueue(
		std::shared_ptr<std::list<ConnEntity>> 
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

	std::shared_ptr<std::list<ConnEntity>>
		_ungreetedConnections;

	std::shared_ptr<std::list<ConnEntity>>
		_inLobbyConnections;
};

#endif