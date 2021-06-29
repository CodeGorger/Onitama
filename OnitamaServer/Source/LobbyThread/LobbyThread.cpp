
#include "LobbyThread.h"
#include <iostream>
#include <OnitamaMessages.h>

void LobbyThread::SetConnectionInputQueue(
    std::shared_ptr<std::vector<ConnEntity>>
    inUngreetedConnectionsQueue)
{
    _ungreetedConnections = inUngreetedConnectionsQueue;
    _lobbyConnections = 
        std::make_shared<std::vector<ConnEntity>>(std::vector<ConnEntity>());
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
            (0==(*_ungreetedConnections.get())[i].ReadGreetingMessage());

        if (properGreeted)
        {
            _lobbyConnections->push_back(
                (*_ungreetedConnections.get())[i]);
            _ungreetedConnections.get()->erase(
                _ungreetedConnections.get()->begin() + i);
        }
    }
}


void LobbyThread::_sendSessionList()
{
    SessionListMessage m = SessionListMessage();
    
    for (int i = 0; i< _unstartedGameSessionList->size(); i++)
    {
        m.AddSessionName((*_unstartedGameSessionList.get())[i].GetSessionName());
    }
    for (int i = 0; i < _lobbyConnections->size(); i++)
    {
        (*_lobbyConnections.get())[i].Send(m.ToString());
    }
}


// Will go through all session-less lobbyConnections
// and try to read a JoinSessionMessage
// if such a message could be read the player will try to be
// put into that session
// if the session doesn't exist, the session will be created
void LobbyThread::_handleJoinSession()
{
    // go through each connection
    for (int i = 0; i < _lobbyConnections->size(); i++)
    {
        // try to read a join session msg
        ReadJoinSessionDto rjsd =
            (*_lobbyConnections.get())[i].ReadJoinSessionMessage();

        if (0 == rjsd.GetReturnStatus()) 
        {
            // A join session msg was read successfully,
            // try to add it to an existing session
            if (1==_addToExistingSession(
                       rjsd.GetSessionName(), i))
            {
                // couldnt find such a session
                // create the session
                _createNewSession(
                    rjsd.GetSessionName(), i);
            }
        }
    }
}


void LobbyThread::_handleStartSession()
{
    for (int is = 0; is < _unstartedGameSessionList->size(); is++)
    {
        GameSession gs = (*_unstartedGameSessionList.get())[is];
        bool ssession = gs.ReadStartRequestSessionMessage();
        if (ssession)
        {
            _launchedGameSessionList.get()->push_back(gs);

            _unstartedGameSessionList.get()->erase(
                _unstartedGameSessionList.get()->begin() + is);

            is--;
        }
    }
}

// Go through each session
// check if it is the name of the session to join
// if that session already has two player abort(code 2)
// add the player to the session as second player, and remove the 
// player from the sessionless lobby connections.
// if the loop ran through without hit, also return (code 1)
// Return 0: successfully added to existing session
//        1: didnt add to another session, because no session found
//        2: didnt add to another session, full session found
int LobbyThread::_addToExistingSession(
    std::string inSessionToJoin, 
    int inConnectionIdInLobbyConnectionLost)
{
    for (int is = 0; is < _unstartedGameSessionList->size(); is++)
    {
        if (inSessionToJoin ==(*_unstartedGameSessionList.get())[is].GetSessionName())
        {
            if ((*_unstartedGameSessionList.get())[is].HasTwoPlayer())
            {
                return 2;
            }

            (*_unstartedGameSessionList.get())[is].SetConnEntityA(
                (*_lobbyConnections.get())[inConnectionIdInLobbyConnectionLost]);

            _lobbyConnections.get()->erase(
                _lobbyConnections.get()->begin() + inConnectionIdInLobbyConnectionLost);

            return 0;
        }
    }
    return 1;
}


void LobbyThread::_createNewSession(
    std::string inSessionToJoin, 
    int inConnectionIdInLobbyConnectionLost)
{
    GameSession newGameSession;
    newGameSession.SetSessionName(inSessionToJoin);
    newGameSession.SetConnEntityB(
        (*_lobbyConnections.get())[inConnectionIdInLobbyConnectionLost]);
    _unstartedGameSessionList->push_back(newGameSession);
    _lobbyConnections.get()->erase(
        _lobbyConnections.get()->begin() + 
        inConnectionIdInLobbyConnectionLost);
}


void LobbyThread::_handleOpenSessionTimeout()
{
    //TODO(Simon): Needs to be written.
}