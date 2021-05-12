
#include "LobbyThread.h"
#include <iostream>

void LobbyThread::SetConnectionInputQueue(
    std::shared_ptr<std::list<ConnEntity>>
    inUngreetedConnectionsQueue)
{
    _ungreetedConnections = inUngreetedConnectionsQueue;
}


void LobbyThread::_do()
{
	while (!_isShutdownRequested)
	{
        // Takes new connections that have greeted properly
        _checkUngreetedNewEntities();

        // Sends a list of all sessions to everyone in the lobby
        _sendSessionList();

        // Handle join session requests
        _handleJoinSession();

        // Handle start requests
        _handleStartSession();
	}
}




void LobbyThread::_checkUngreetedNewEntities()
{
    for (int i = 0; i < _ungreetedConnections->size(); i++)
    {
        bool properGreeted=
            _ungreetedConnections.get()[i].ReadGreetingMessage();

        SOCKET cs = _ungreetedConnections.get()[i].GetSocket();
        char* recvbuf = _ungreetedConnections.get()[i].GetRecvBuffer();
        int recvbuflen = _ungreetedConnections.get()[i].GetRecvBufferLen();

        int result = recv(cs, recvbuf, recvbuflen, 0);

        if (result == 0)
        {
            _ungreetedConnections.get()->remove(i--);
        }
        else if (result < 0)
        {
            std::cout << "recv failed with error: " << 
                WSAGetLastError() << std::endl;
        }
        else if (result > 0)
        {
            bool hasProperlyGreeted = 
                _ungreetedConnections.get()[i].VerifyGreetingMessage();
            if (hasProperlyGreeted)
            {
                _inLobbyConnections
            }
        }
    }
}