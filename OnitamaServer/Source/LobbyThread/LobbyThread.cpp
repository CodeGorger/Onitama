
#include "LobbyThread.h"
#include <iostream>
#include <OnitamaMessages.h>
#include <Messages/SessionInformation/SessionInformationMessage.h>

void LobbyThread::SetConnectionInputQueue(
    ThreadSafeQueue<std::shared_ptr<ConnEntity>>
    inUngreetedConnectionsQueue)
{
    l = spdlog::stdout_color_mt("LobbyThread");
#ifdef DEBUGLOGGING
    //l->set_level(spdlog::level::debug);
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

    // Will send the session info to connections in sessions
    _sendSessionInformation();
    
    // Handle start requests
    _handleStartAndLeaveSession();

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

    //m.AddSessionName("Test");
    //m.AddSessionName("TestXXX");

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
        l->debug("Created a SessionListMessage with {0} entries. Sent it to {1} lobby connections. ",
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

// TODO(Simon): Check what the server does if PlayerA leaves and
//              the game hasn't started. Will PlayerB be moved to
//              PlayerA? Will the session be closed properly if there is no B?

// TODO(Simon): Players may not be called "Empty"

// TODO(Simon): Any player or gamesession may not have a ';', ':' or ','
//              in its name

void LobbyThread::_sendSessionInformation()
{
    l->debug("_unstartedGameSessionList");
    for (unsigned int is = 0; is < _unstartedGameSessionList.Size(); is++)
    {
        std::string playerAName = "Empty";
        std::string playerBName = "Empty";
        std::shared_ptr<GameSession> gs = _unstartedGameSessionList.Get(is);
        SessionInformationMessage simsg = SessionInformationMessage();
        // PlayerA ist always host ... 
        if (gs->GetPlayerA())
        {
            playerAName = gs->GetPlayerA()->GetPlayername();
        }
        if (gs->GetPlayerB())
        {
            simsg.SetIsHost(false);
            simsg.SetOppoName(playerAName);
            gs->GetPlayerB()->Send(simsg.ToString());
            playerBName = gs->GetPlayerB()->GetPlayername();
        }
        if (gs->GetPlayerA())
        {
            simsg.SetIsHost(true);
            simsg.SetOppoName(playerBName);
            gs->GetPlayerA()->Send(simsg.ToString());
        }
    }
}


void LobbyThread::_handleStartAndLeaveSession()
{
    l->debug("_handleStartSession");
    for (unsigned int is = 0; is < _unstartedGameSessionList.Size(); is++)
    {
        std::shared_ptr<GameSession> gs = _unstartedGameSessionList.Get(is);
        int result = gs->ReadStartRequestAndLeaveSessionMessages();

        switch (result)
        {
        case -1:// B wishes to leave the session
            l->info("User {0} (B) left session {1}.",
                gs->GetPlayerB()->GetPlayername(),
                gs->GetSessionName());
            _lobbyConnections.Enque(gs->GetPlayerB());

            gs->SetConnEntityB(nullptr);
            break;

        case -2:// A wishes to leave the session
            l->info("User {0} (A) left session {1}.",
                gs->GetPlayerA()->GetPlayername(),
                gs->GetSessionName());
            _lobbyConnections.Enque(gs->GetPlayerA());
            gs->SetConnEntityA(nullptr);

            // Player B will be moved to slot A in _removedClosedConnections()
            // Session will evtl be removed in _removedClosedConnections()
            break;

        case -3:// A & B wishes to leave the session
            l->info("Session {0} will be closed, user {1} and {2} left.",
                gs->GetSessionName(),
                gs->GetPlayerA()->GetPlayername(),
                gs->GetPlayerB()->GetPlayername());
            _lobbyConnections.Enque(gs->GetPlayerA());
            _lobbyConnections.Enque(gs->GetPlayerB());
            _unstartedGameSessionList.Remove(is);
            is--;
            break;

        case -4:// A wishes to start the session
            l->info("Session {0} with user {1} and {2} has been started.",
                gs->GetSessionName(),
                gs->GetPlayerA()->GetPlayername(),
                gs->GetPlayerB()->GetPlayername());
            _launchedGameSessionList.Enque(gs);
            _unstartedGameSessionList.Remove(is);
            is--;
            // TODO(Simon): GameThread must be started here !!!

            break;
        default:
            break;
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

            _unstartedGameSessionList.Get(is)->SetConnEntityB(
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
    newGameSession = std::make_shared<GameSession>();
    newGameSession->SetSessionName(inSessionToJoin);
    newGameSession->SetConnEntityA(
        _lobbyConnections.Get(inConnectionIdInLobbyConnectionLost));
    _unstartedGameSessionList.Enque(newGameSession);
    _lobbyConnections.Remove(
        inConnectionIdInLobbyConnectionLost);
}

void LobbyThread::_removedClosedConnections()
{
    // Remove all unproperly closed connections
    // that haven't greeted yet
    for (unsigned int i = 0; i < _ungreetedConnections.Size(); i++)
    {
        if (_ungreetedConnections.Get(i)->IsClosed())
        {
            l->info("Removing user {0}.", 
                _ungreetedConnections.Get(i)->GetPlayername());
            _ungreetedConnections.Remove(i);
            i--;
        }
    }

    // Remove all unproperly closed connections
    // that resided in the lobby
    for (unsigned int i = 0; i < _lobbyConnections.Size(); i++)
    {
        if (_lobbyConnections.Get(i)->IsClosed())
        {
            l->info("Removing user {0}.",
                _lobbyConnections.Get(i)->GetPlayername());
            _lobbyConnections.Remove(i);
            i--;
        }
    }

    // Remove all closed sessions
    for (unsigned int i = 0; i < _unstartedGameSessionList.Size(); i++)
    {
        std::shared_ptr<GameSession> gs = _unstartedGameSessionList.Get(i);
        if (gs->CheckConnectionsIfClosed())
        {
            l->info("Removing session {0}.",
                gs->GetSessionName());
            _unstartedGameSessionList.Remove(i);
            i--;
        }
    }

    // Remove all unproperly closed connections in sessions
    for (unsigned int i = 0; i < _unstartedGameSessionList.Size(); i++)
    {
        std::shared_ptr<GameSession> gs = _unstartedGameSessionList.Get(i);
        std::shared_ptr<ConnEntity> a = gs->GetPlayerA();
        std::shared_ptr<ConnEntity> b = gs->GetPlayerB();
        if (a && a->IsClosed())
        {
            l->info("Removing user {0} from session {1} and server.",
                a->GetPlayername(),
                gs->GetSessionName());
            gs->SetConnEntityA(nullptr);
        }
        if (b && b->IsClosed())
        {
            l->info("Removing user {0} from session {1} and server.",
                b->GetPlayername(),
                gs->GetSessionName());
            gs->SetConnEntityB(nullptr);
        }
    }

    // Move a B player to slot A if A is empty
    for (unsigned int i = 0; i < _unstartedGameSessionList.Size(); i++)
    {
        std::shared_ptr<GameSession> gs = _unstartedGameSessionList.Get(i);
        if (nullptr == gs->GetPlayerA())
        {
            l->info("Promoting user {0} to the host of session {1}.",
                gs->GetPlayerB()->GetPlayername(),
                gs->GetSessionName());
            // Guest is now host.
            gs->SetConnEntityA(gs->GetPlayerB());
            gs->SetConnEntityB(nullptr);
        }
    }

    // TODO(Simon): What if a A (or B) player left and B hasnt been moved to
    // Slot A yet. And in that moment a third player will try to join?

}

void LobbyThread::_handleOpenSessionTimeout()
{
    //TODO(Simon): Needs to be written.
}