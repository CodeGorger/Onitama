#ifndef _DOACCEPT_H_
#define _DOACCEPT_H_

#include <iostream>
#include "IDoable.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <nedb.h>
#include <unistd.h>
#endif

class DoAccept :public IDoable
{
public:
	DoAccept();
	void Do();

private:
	int _sockInit(void);
	int _sockQuit(void);
	int _sockClose(SOCKET sock);
	int _initTcpListenSocket();
	int _tcpAcceptThreadMethod();

	SOCKET _listenSocket;

};

#endif

