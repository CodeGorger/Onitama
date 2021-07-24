#include "AcceptThread.h"


AcceptThread::AcceptThread()
    : ThreadHandler()
    , _listenPort(13337)
{
    l = spdlog::stdout_color_mt("AcceptThread");
//#ifdef DEBUGLOGGING
//    l->set_level(spdlog::level::debug);
//#endif
    _outputQueue = ThreadSafeQueue<std::shared_ptr<ConnEntity>>();
}

ThreadSafeQueue<std::shared_ptr<ConnEntity>> AcceptThread::GetOutputQueue()
{
    return _outputQueue;
}


void AcceptThread::_do()
{
    l->info("Started Thread");
    _initTcpListenSocket();
    while (!_isShutdownRequested)
    {
        _tcpAcceptThreadMethod();
    }
    l->info("Stopped Thread");
}

int AcceptThread::_sockInit(void)
{
    l->debug("_sockInit");
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
    return 0;
#endif
}

int AcceptThread::_sockQuit(void)
{
    l->debug("_sockQuit");
#ifdef _WIN32
    return WSACleanup();
#else
    return 0;
#endif
}

int AcceptThread::_sockClose(SOCKET sock)
{
    l->debug("_sockClose");
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
    l->info("TCP Socket init started");
    if (0 != _sockInit())
    {
        l->error("Socket Init Failed! ({0})", WSAGetLastError());
        return 1;
    }
    else
    {
        l->debug("Socket Init Success!");
    }

    _listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == _listenSocket)
    {
        l->error("Socket Creation Failed! ({0})", WSAGetLastError());
        return 2;
    }
    else
    {
        l->debug("Socket Creation Success!");
    }

    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(SOCKADDR_IN));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_listenPort);
    addr.sin_addr.s_addr = ADDR_ANY;
    if (SOCKET_ERROR ==
        bind(_listenSocket,
            (SOCKADDR*)&addr,
            sizeof(SOCKADDR_IN)))
    {
        l->error("Socket Bind Failed! ({0})", WSAGetLastError());
        return 3;
    }
    else
    {
        l->debug("Socket Bind Success!");
    }

    if (SOCKET_ERROR == listen(_listenSocket, 10))
    {
        l->error("Socket Listen Failed! ({0})", WSAGetLastError());
        return 4;
    }
    else
    {
        l->debug("Socket Listen Success!");
    }
    return 0;
}


int AcceptThread::_tcpAcceptThreadMethod()
{
    l->debug("_tcpAcceptThreadMethod");
    // Needed for peer ip 
    struct sockaddr_in peer_addr;
    socklen_t peer_addrlen = sizeof(peer_addr);
    memset(&peer_addr, '\0', peer_addrlen);
    char str[INET_ADDRSTRLEN];

    // The actual accept ... 
    SOCKET connectedSocket = accept(
        _listenSocket, 
        (struct sockaddr*)&peer_addr, 
        &peer_addrlen);
    if (INVALID_SOCKET == connectedSocket)
    {
        l->error("Socket Accept Failed! ({0}; IP: {1})",
            WSAGetLastError(),
            inet_ntop(AF_INET,
                &peer_addr.sin_addr, 
                str,
                sizeof(str)));
        return 5;
    }
    else
    {
        l->debug("Socket Accept Success!");
    }

    l->info("Socket: {0}", connectedSocket);
    std::shared_ptr<ConnEntity> ec = std::make_shared<ConnEntity>(connectedSocket);
    ec->SetIp(inet_ntop(AF_INET,
        &peer_addr.sin_addr,
        str,
        sizeof(str)));
    ec->SetPort(std::to_string(ntohs(peer_addr.sin_port)));

    l->info("Connection established from {0}:{1}.",
        ec->GetIp(),
        ec->GetPort());

    _outputQueue.Enque(ec);
}
