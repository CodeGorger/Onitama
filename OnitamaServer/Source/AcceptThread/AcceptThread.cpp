#include "AcceptThread.h"



AcceptThread::AcceptThread()
    :ThreadHandler()
{
    _outputQueue = std::make_shared<std::vector<ConnEntity>>(std::vector<ConnEntity>());
}

std::shared_ptr<std::vector<ConnEntity>> AcceptThread::GetOutputQueue()
{
    return _outputQueue;
}


void AcceptThread::_do()
{
	_initTcpListenSocket();
	while (!_isShutdownRequested)
	{
		_tcpAcceptThreadMethod();
	}
}

int AcceptThread::_sockInit(void)
{
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

int AcceptThread::_sockQuit(void)
{
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

int AcceptThread::_sockClose(SOCKET sock)
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

int AcceptThread::_initTcpListenSocket()
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


int AcceptThread::_tcpAcceptThreadMethod()
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

    ConnEntity ec = ConnEntity(connectedSocket);
    _outputQueue->push_back(ec);
}
