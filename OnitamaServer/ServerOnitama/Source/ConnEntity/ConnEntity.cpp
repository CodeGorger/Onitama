
#include "ConnEntity.h"
#include <iostream>

ConnEntity::ConnEntity(SOCKET inS)
{
    _s = inS;
}


bool ConnEntity::ReadGreetingMessage()
{
    _s ;
    char* recvbuf = _ungreetedConnections.get()[i].GetRecvBuffer();
    int recvbuflen = _ungreetedConnections.get()[i].GetRecvBufferLen();

    int result = recv(_s, recvbuf, recvbuflen, 0);

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



