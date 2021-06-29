
#include "ConnEntity.h"
#include <iostream>
#include <OnitamaMessages.h>


ConnEntity::ConnEntity()
    :_isInitedProperly(false)
{
}

ConnEntity::ConnEntity(SOCKET inS)
    : _isInitedProperly(true)
    , _s(inS)
{
    _recvbuflen = RECVLEN;
    _currentMessageBuffer = "";
}

//return 0: Success
//       1: No success no failure
//       2: Failure, drop connection, stop thread
int ConnEntity::ReadGreetingMessage()
{
    _readIncomingTcp();

    MessageParsedDTO mesResult=ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:

        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return 1;
        break;
    default:
    //case MessageStringResult::MessageStringResult_Trash:
    //case MessageStringResult::MessageStringResult_TooLong:
        closesocket(_s);
        return 2;
        break;
    }

    GreetingMessage * gMes = dynamic_cast<GreetingMessage*>(mesResult.GetOnitamaMessage());
    if (0==gMes)
    {
        return 3;
    }
    _hasGreeted = true;
    _playerName = gMes->GetPlayerName();
    _currentMessageBuffer = mesResult.GetRest();
    return 0;
}


//return 0: Success
//       1: No success no failure
//       2: Failure, drop connection, stop thread
ReadJoinSessionDto ConnEntity::ReadJoinSessionMessage()
{
    _readIncomingTcp();

    MessageParsedDTO mesResult = ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:

        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return ReadJoinSessionDto(1);
        break;
    default:
        //case MessageStringResult::MessageStringResult_Trash:
        //case MessageStringResult::MessageStringResult_TooLong:
        closesocket(_s);
        return ReadJoinSessionDto(2);
        break;
    }

    JoinSessionMessage* jSMes = 
        dynamic_cast<JoinSessionMessage*>(mesResult.GetOnitamaMessage());
    if (0 == jSMes)
    {
        return ReadJoinSessionDto(3);
    }

    return ReadJoinSessionDto(0, jSMes->GetSessionName());
}



//return 0: Success
//       1: No success no failure
//       2: Failure, drop connection, stop thread
int ConnEntity::ReadStartRequestSessionMessage()
{
    _readIncomingTcp();

    MessageParsedDTO mesResult = ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:

        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return 1;
        break;
    default:
        //case MessageStringResult::MessageStringResult_Trash:
        //case MessageStringResult::MessageStringResult_TooLong:
        closesocket(_s);
        return 2;
        break;
    }

    GamestartRequestMessage* gMes = dynamic_cast<GamestartRequestMessage*>(mesResult.GetOnitamaMessage());
    if (0 == gMes)
    {
        return 3;
    }
    return 0;
}

ReadMoveInfoDto ConnEntity::ReadMoveInfo()
{
    _readIncomingTcp();

    MessageParsedDTO mesResult = ParseMessage(_currentMessageBuffer);

    switch (mesResult.GetResult())
    {
    case MessageStringResult::MessageStringResult_Complete:

        break;
    case MessageStringResult::MessageStringResult_PossibleBeginning:
        // Do nothing ...
        return ReadMoveInfoDto(1);
        break;
    default:
        //case MessageStringResult::MessageStringResult_Trash:
        //case MessageStringResult::MessageStringResult_TooLong:
        closesocket(_s);
        return ReadMoveInfoDto(2);
        break;
    }

    MoveMessage* gMes = dynamic_cast<MoveMessage*>(mesResult.GetOnitamaMessage());
    if (0 == gMes)
    {
        return ReadMoveInfoDto(3);
    }

    MoveInformation mi;
    if (!mi.ParseMove(gMes->GetMove()))
    {
        return ReadMoveInfoDto(4);
    }

    return ReadMoveInfoDto(0, mi);
}


void ConnEntity::Send(std::string inMessage)
{

    int result = send(_s, inMessage.c_str(), inMessage.length(), 0);


}


bool ConnEntity::IsInited()
{
    return _isInitedProperly;
}




void ConnEntity::_readIncomingTcp()
{
    int result = recv(_s, _recvbuf, _recvbuflen, 0);

    if (result == 0)
    {
        //_ungreetedConnections.get()->remove(i--);
    }
    else if (result < 0)
    {
        std::cout << "recv failed with error: " <<
            WSAGetLastError() << std::endl;
    }
    else if (result > 0)
    {
        _currentMessageBuffer += _recvbuf;
    }
}