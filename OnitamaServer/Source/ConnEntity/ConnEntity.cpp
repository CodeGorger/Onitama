
#include "ConnEntity.h"
#include <iostream>
#include <OnitamaMessages.h>
#include <Messages/LeaveSessionMessage/LeaveSessionMessage.h>


ConnEntity::ConnEntity()
    :_isInitedProperly(false)
{
    std::string randomLoggerId = std::to_string(rand() % 1000000);
    std::string id=
        std::string(6 - randomLoggerId.length(), '0') + randomLoggerId;
    l = spdlog::stdout_color_mt("ConnE"+id);
#ifdef DEBUGLOGGING
    l->set_level(spdlog::level::debug);
#endif
    l->debug("ConnEntity()");
}

ConnEntity::ConnEntity(SOCKET inS)
    : _isInitedProperly(true)
    , _s(inS)
    , _isClosed(false)
{
    std::string randomLoggerId = std::to_string(rand() % 1000000);
    std::string id =
        std::string(6 - randomLoggerId.length(), '0') + randomLoggerId;
    l = spdlog::stdout_color_mt("ConnE" + id);
#ifdef DEBUGLOGGING
    l->set_level(spdlog::level::debug);
#endif
    l->debug("ConnEntity(SOCKET)");

    _recvbuflen = RECVLEN;
    _currentMessageBuffer = "";

    //-------------------------
    // Set the socket I/O mode: In this case FIONBIO
    // enables or disables the blocking mode for the 
    // socket based on the numerical value of iMode.
    // If iMode = 0, blocking is enabled; 
    // If iMode != 0, non-blocking mode is enabled.

    int iResult;
    u_long iMode = 1; // 0 := blocking; 1 := non-blocking
    iResult = ioctlsocket(_s, FIONBIO, &iMode);
    if (iResult != NO_ERROR)
    {
        l->error( "ioctlsocket failed with error: {0}.", iResult );
    }
}

ConnEntity::ConnEntity(const ConnEntity& rhs)
    :_s(rhs._s)
    //,_recvbuf(rhs._recvbuf)
    , _recvbuflen(rhs._recvbuflen)
    , _currentMessageBuffer(rhs._currentMessageBuffer)
    , _hasGreeted(rhs._hasGreeted)
    , _playerName(rhs._playerName)
    , _sessionName(rhs._sessionName)
    , _connectedAtTime(rhs._connectedAtTime)
    , _isInitedProperly(rhs._isInitedProperly)
    , _ip(rhs._ip)
    , _port(rhs._port)
    , l(rhs.l)
    , _isClosed(rhs._isClosed)
{
    l->debug("ConnEntity(const ConnEntity& rhs)");
}

//return 0: Success
//       1: No success no failure
//       2: Failure, drop connection, stop thread
int ConnEntity::ReadGreetingMessage()
{
    if (_readIncomingTcp())
    {
        l->warn("3 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return 2;
    }

    MessageParsedDTO mesResult=ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:
        _currentMessageBuffer = mesResult.GetRest();
        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return 1;
        break;
    default:
    //case MessageStringResult::MessageStringResult_Trash:
    //case MessageStringResult::MessageStringResult_TooLong:
        l->warn("4 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return 2;
        break;
    }

    OnitamaMessage* oMes = mesResult.GetOnitamaMessage().get();
    GreetingMessage* gMes =
        dynamic_cast<GreetingMessage*>(oMes);
    if (0==gMes)
    {
        return 3;
    }
    _hasGreeted = true;
    _playerName = gMes->GetPlayerName();
    return 0;
}


//return 0: Success
//       1: No success no failure
//       2: Failure, drop connection, stop thread
ReadJoinSessionDto ConnEntity::ReadJoinSessionMessage()
{
    if (_readIncomingTcp())
    {
        l->warn("1 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return ReadJoinSessionDto(2);
    }

    MessageParsedDTO mesResult = ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:
        _currentMessageBuffer = mesResult.GetRest();
        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return ReadJoinSessionDto(1);
        break;
    default:
        //case MessageStringResult::MessageStringResult_Trash:
        //case MessageStringResult::MessageStringResult_TooLong:
        l->warn("2 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return ReadJoinSessionDto(2);
        break;
    }

    OnitamaMessage* oMes = mesResult.GetOnitamaMessage().get();
    JoinSessionMessage* jSMes =
        dynamic_cast<JoinSessionMessage*>(oMes);
    if (0 == jSMes)
    {
        return ReadJoinSessionDto(3);
    }

    return ReadJoinSessionDto(0, jSMes->GetSessionName());
}



//TODO(Simon): This should be an enum...
//return -2: Success, Gamestart Request
//       -1: Success, Leave Session 
//        1: No success no failure
//        2: Failure, drop connection, stop thread
int ConnEntity::ReadStartRequestAndLeaveSessionMessage()
{
    if (_readIncomingTcp())
    {
        l->warn("5 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return 2;
    }

    MessageParsedDTO mesResult = ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:
        _currentMessageBuffer = mesResult.GetRest();
        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return 1;
        break;
    default:
        //case MessageStringResult::MessageStringResult_Trash:
        //case MessageStringResult::MessageStringResult_TooLong:
        l->warn("6 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return 2;
        break;
    }

    OnitamaMessage* oMes = mesResult.GetOnitamaMessage().get();
    GamestartRequestMessage* gMes =
        dynamic_cast<GamestartRequestMessage*>(oMes);
    LeaveSessionMessage* lMes =
        dynamic_cast<LeaveSessionMessage*>(oMes);
    if (0 != gMes)
    {
        return -2;
    }
    if (0 != lMes)
    {
        return -1;
    }
    return 3;
}

ReadMoveInfoDto ConnEntity::ReadMoveInfo()
{
    if (_readIncomingTcp())
    {
        l->warn("7 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return ReadMoveInfoDto(2);
    }

    MessageParsedDTO mesResult = ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:
        _currentMessageBuffer = mesResult.GetRest();
        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return ReadMoveInfoDto(1);
        break;
    default:
        //case MessageStringResult::MessageStringResult_Trash:
        //case MessageStringResult::MessageStringResult_TooLong:
        l->warn("8 Closing socket {0}.", _s);
        _isClosed = true;
        closesocket(_s);
        return ReadMoveInfoDto(2);
        break;
    }

    OnitamaMessage* oMes = mesResult.GetOnitamaMessage().get();
    MoveMessage* mMes =
        dynamic_cast<MoveMessage*>(oMes);
    if (0 == mMes)
    {
        return ReadMoveInfoDto(3);
    }

    MoveInformation mi;
    if (!mi.ParseMove(mMes->GetMove()))
    {
        return ReadMoveInfoDto(4);
    }

    return ReadMoveInfoDto(0, mi);
}


void ConnEntity::Send(std::string inMessage)
{
    int result = send(_s, inMessage.c_str(), (int)inMessage.length(), 0);
}


bool ConnEntity::IsInited()
{
    return _isInitedProperly;
}



// Will return true if the socket was closed somehow
bool ConnEntity::_readIncomingTcp()
{
    bool ret = false;
    std::fill_n(_recvbuf, _recvbuflen, 0);
    int result = recv(_s, _recvbuf, _recvbuflen, 0);

    if (result == 0)
    {
        l->warn("Socket was closed.");
        ret = true;
    }
    else if (result < 0)
    {
        // WSAEWOULDBLOCK   10035
        // WSAENOTSOCK      10038
        // WSAEADDRINUSE    10048
        // WSAECONNRESET    10054
        // WSAENOBUFS       10055
        // WSAEISCONN       10056
        // WSAENOTCONN      10057
        // WSAESHUTDOWN     10058
        int err_num = WSAGetLastError();
        switch (err_num)
        {
        case 10035:
            break;
        case 10038:
            l->warn("Socket was closed (10038 - WSAENOTSOCK).");
            ret = true;
            break;
        case 10053:
            l->warn("Socket was closed (10053 - WSAECONNABORTED).");
            ret = true;
            break;
        case 10054:
            l->warn("Socket was closed (10054 - WSAECONNRESET).");
            ret = true;
            break;
        default:
            l->warn("recv failed with error: {0}.",
                err_num);
            break;
        }
    }
    else if (result > 0)
    {
        _currentMessageBuffer += _recvbuf;
    }
    return ret;
}