#include "DoAccept.h"
#include "EntityConnection.h"


DoAccept::DoAccept()
	:IDoable()
{

}

void DoAccept::Do()
{
    _initTcpListenSocket();
	while (!isShutdownRequested)
	{
        _tcpAcceptThreadMethod();
		//std::cout << "Eat" << std::endl;
		//std::cout << "Poop" << std::endl;
		//std::cout << "Sleep" << std::endl;
	}
}


int DoAccept::_sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

int DoAccept::_sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

int DoAccept::_sockClose(SOCKET sock)
{
    int status = 0;

#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { status = closesocket(sock); }
#else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0) { status = close(sock); }
    return 0;
#endif
    return status;
}

int DoAccept::_initTcpListenSocket()
{
    if (0 != _sockInit())
    {
        std::cout << "Socket Init Failed! (" <<
            WSAGetLastError() << ")" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Socket Init Success!" << std::endl;
    }

    _listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == _listenSocket)
    {
        std::cout << "Socket Creation Failed! (" <<
            WSAGetLastError() << ")" << std::endl;
        return 2;
    }
    else
    {
        std::cout << "Socket Creation Success!" << std::endl;
    }

    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(SOCKADDR_IN));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = ADDR_ANY;
    if (SOCKET_ERROR == 
        bind(_listenSocket, 
            (SOCKADDR*)&addr, 
            sizeof(SOCKADDR_IN)))
    {
        std::cout << "Socket Bind Failed! (" <<
            WSAGetLastError() << ")" << std::endl;
        return 3;
    }
    else
    {
        std::cout << "Socket Bind Success!" << std::endl;
    }

    if (SOCKET_ERROR == listen(_listenSocket, 10))
    {
        std::cout << "Socket Listen Failed! (" <<
            WSAGetLastError() << ")" << std::endl;
        return 4;
    }
    else
    {
        std::cout << "Socket Listen Success!" << std::endl;
    }
    return 0;
}


int DoAccept::_tcpAcceptThreadMethod()
{

    SOCKET connectedSocket;
    connectedSocket = accept(_listenSocket, NULL, NULL);
    if (INVALID_SOCKET == connectedSocket)
    {
        std::cout << "Socket Accept Failed! (" <<
            WSAGetLastError() << ")" << std::endl;
        //threadHadNoProblem = true;
        return 5;
    }
    else
    {
        std::cout << "Socket Accept Success!" << std::endl;
    }

    EntityConnection ec = EntityConnection(connectedSocket);
    _enqueueOutput(std::make_unique<EntityConnection>(ec));
    //char buf[256];
    //if (INVALID_SOCKET == recv(connectedSocket, buf, 256, 0))
    //{
    //    std::cout << "Socket Recv Failed! (" <<
    //        WSAGetLastError() << ")" << std::endl;
    //    //threadHadNoProblem = true;
    //    return 6;
    //}
    //else
    //{
    //    std::cout << "Socket Recv Success!" << std::endl;
    //    std::cout << "Recv:" << buf << std::endl;
    //}
}
