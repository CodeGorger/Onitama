
#include "LobbyThread.h"
#include <iostream>
#include <OnitamaMessages.h>

void LobbyThread::SetConnectionInputQueue(
    ThreadSafeQueue<std::shared_ptr<ConnEntity>>
    inUngreetedConnectionsQueue)
{
    l = spdlog::stdout_color_mt("LobbyThread");
#ifdef DEBUGLOGGING
    l->set_level(spdlog::level::debug);
#endif
    _ungreetedConnections = inUngreetedConnectionsQueue;
    _lobbyConnections = ThreadSafeQueue< std::shared_ptr<ConnEntity>>();
}


void LobbyThread::_do()
{
    l->info("Started Thread");
    _timedLoop();
    l->info("Stopped Thread");
}


// Will execute _timedDo() maximally 1 each second
void LobbyThread::_timedLoop()
{
    clock_t loopStart;
    clock_t loopEnd;
    clock_t loopDuration;
    unsigned int loopDurationInMs;
    while (!_isShutdownRequested)
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
            l->warn("Loop stalled for {0} ms.", loopDurationInMs);
        }
        else
        {
            Sleep(1000 - loopDurationInMs);
        }
    }
}


// Will execute _timedDo() maximally 1 each second
void LobbyThread::_timedDo()
{
    // Takes new connections that have greeted properly
    _checkUngreetedNewEntities();

    // Sends a list of all sessions to everyone in the lobby
    _sendSessionList();

    // Handle join session requests
    _handleJoinSession();

    // Handle start requests
    _handleStartSession();

    // Remove closed connections
    _removedClosedConnections();
}


void LobbyThread::_checkUngreetedNewEntities()
{
    l->debug("_checkUngreetedNewEntities");
    for (unsigned int i = 0; i < _ungreetedConnections.Size(); i++)
    {
        bool properGreeted =
            (0 == _ungreetedConnections.Get(i)->ReadGreetingMessage());
        if (properGreeted)
        {
            l->info("IP {0}:{1} has greeted properly as {2}.",
                _ungreetedConnections.Get(i)->GetIp(),
                _ungreetedConnections.Get(i)->GetPort(),
                _ungreetedConnections.Get(i)->GetPlayername());
            _lobbyConnections.Enque(
                _ungreetedConnections.Get(i));
            _ungreetedConnections.Remove(i);
            //TODO(Simon): Don't just remove, remember to be removed 
            // and do this at end. Alternative make a map and handle it this.
        }
    }
}


void LobbyThread::_sendSessionList()
{
    l->debug("_sendSessionList");
    SessionListMessage m = SessionListMessage();

    for (unsigned int i = 0; i < _unstartedGameSessionList.Size(); i++)
    {
        //TODO(Simon): What is the limit for sessions in one message?
        m.AddSessionName(_unstartedGameSessionList.Get(i)->GetSessionName());
    }
    for (unsigned int i = 0; i < _lobbyConnections.Size(); i++)
    {
        _lobbyConnections.Get(i)->Send(m.ToString());
    }
    if (0 < _lobbyConnections.Size())
    {
        l->info("Created a SessionListMessage with {0} entries. Sent it to {1} lobby connections. ",
            _unstartedGameSessionList.Size(),
            _lobbyConnections.Size());
    }
}


// Will go through all session-less lobbyConnections
// and try to read a JoinSessionMessage
// if such a message could be read the player will try to be
// put into that session
// if the session doesn't exist, the session will be created
void LobbyThread::_handleJoinSession()
{
    l->debug("_handleJoinSession");
    // go through each connection
    for (unsigned int i = 0; i < _lobbyConnections.Size(); i++)
    {
        // try to read a join session msg
        ReadJoinSessionDto rjsd =
            _lobbyConnections.Get(i)->ReadJoinSessionMessage();

        if (0 == rjsd.GetReturnStatus())
        {
            // A join session msg was read successfully,
            // try to add it to an existing session
            int r = _addToExistingSession(
                rjsd.GetSessionName(), i);
            if (1 == r)
            {
                l->info("User {0} tried to join session {1}, it will be created.",
                    _lobbyConnections.Get(i)->GetPlayername(),
                    rjsd.GetSessionName());

                // couldnt find such a session
                // create the session
                _createNewSession(
                    rjsd.GetSessionName(), i);
            }
            else if (0 == r)
            {
                l->info("User {0} joined session {1}.",
                    _lobbyConnections.Get(i)->GetPlayername(),
                    rjsd.GetSessionName());
            }
            else if (2 == r)
            {
                l->info("User {0} tried to join session {1}, but it is already full.",
                    _lobbyConnections.Get(i)->GetPlayername(),
                    rjsd.GetSessionName());
            }
            else
            {
                l->info("User {0} tried to join session {1}, but it didn't work because of an unknown reason.",
                    _lobbyConnections.Get(i)->GetPlayername(),
                    rjsd.GetSessionName());
            }
        }
    }
}


void LobbyThread::_handleStartSession()
{
    l->debug("_handleStartSession");
    for (unsigned int is = 0; is < _unstartedGameSessionList.Size(); is++)
    {
        std::shared_ptr<GameSession> gs = _unstartedGameSessionList.Get(is);
        bool ssession = gs->ReadStartRequestSessionMessage();
        if (ssession)
        {
            l->info("Session {0} with User {1} and {2} has been started.",
                gs->GetSessionName(),
                gs->GetPlayerA()->GetPlayername(),
                gs->GetPlayerB()->GetPlayername());
            _launchedGameSessionList.Enque(gs);
            _unstartedGameSessionList.Remove(is);
            is--;

            //TODO(Simon): GameThread must be started here !!!
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
    l->debug("_addToExistingSession");
    for (unsigned int is = 0; is < _unstartedGameSessionList.Size(); is++)
    {
        if (inSessionToJoin == _unstartedGameSessionList.Get(is)->GetSessionName())
        {
            if (_unstartedGameSessionList.Get(is)->HasTwoPlayer())
            {
                return 2;
            }

            _unstartedGameSessionList.Get(is)->SetConnEntityA(
                _lobbyConnections.Get(inConnectionIdInLobbyConnectionLost));

            _lobbyConnections.Remove(inConnectionIdInLobbyConnectionLost);

            return 0;
        }
    }
    return 1;
}


void LobbyThread::_createNewSession(
    std::string inSessionToJoin,
    int inConnectionIdInLobbyConnectionLost)
{
    l->debug("_createNewSession");
    std::shared_ptr<GameSession> newGameSession;
    newGameSession->SetSessionName(inSessionToJoin);
    newGameSession->SetConnEntityB(
        _lobbyConnections.Get(inConnectionIdInLobbyConnectionLost));
    _unstartedGameSessionList.Enque(newGameSession);
    _lobbyConnections.Remove(
        inConnectionIdInLobbyConnectionLost);
}

void LobbyThread::_removedClosedConnections()
{
    for (int i = 0; i < _ungreetedConnections.Size(); i++)
    {
        if (_ungreetedConnections.Get(i)->IsClosed())
        {
            _ungreetedConnections.Remove(i);
            i--;
        }
    }

    for (int i = 0; i < _lobbyConnections.Size(); i++)
    {
        if (_lobbyConnections.Get(i)->IsClosed())
        {
            _lobbyConnections.Remove(i);
            i--;
        }
    }

    for (int i = 0; i < _unstartedGameSessionList.Size(); i++)
    {
        if (_unstartedGameSessionList.Get(i)->CheckConnectionsIfClosed())
        {
            _unstartedGameSessionList.Remove(i);
            i--;
        }
    }
}

void LobbyThread::_handleOpenSessionTimeout()
{
    //TODO(Simon): Needs to be written.
}