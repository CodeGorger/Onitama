#ifndef _CONNENTITY_H_
#define _CONNENTITY_H_

#include <string>
#include "ReadMoveInfoDto.h"
#include "ReadJoinSessionDto.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <nedb.h>
#include <unistd.h>
#endif

#define RECVLEN 1024

class ConnEntity 
{
public:
	ConnEntity();
	ConnEntity(SOCKET inS);
	int ReadGreetingMessage();
	ReadJoinSessionDto ReadJoinSessionMessage();
	int ReadStartRequestSessionMessage();
	ReadMoveInfoDto ReadMoveInfo();
	void Send(std::string inMessage);
	bool IsInited();

private:
	SOCKET _s;

	char _recvbuf[RECVLEN];
	int _recvbuflen;
	std::string _currentMessageBuffer;

	bool _hasGreeted;
	std::string _playerName;
	std::string _sessionName;
	unsigned int _connectedAtTime;

	bool _isInitedProperly;

	void _readIncomingTcp();
};

#endif
