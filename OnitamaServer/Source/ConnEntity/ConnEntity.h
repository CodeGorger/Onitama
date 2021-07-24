#ifndef _CONNENTITY_H_
#define _CONNENTITY_H_

#include <string>
#include "ReadMoveInfoDto.h"
#include "ReadJoinSessionDto.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

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
	ConnEntity(const ConnEntity&);
	int ReadGreetingMessage();
	ReadJoinSessionDto ReadJoinSessionMessage();
	int ReadStartRequestSessionMessage();
	ReadMoveInfoDto ReadMoveInfo();
	void Send(std::string inMessage);
	bool IsInited();

	void SetIp(std::string inIp)
	{
		_ip = inIp;
	}

	void SetPort(std::string inPort)
	{
		_port = inPort;
	}

	std::string GetIp()
	{
		return _ip;
	}

	std::string GetPort()
	{
		return _port;
	}

	std::string GetPlayername()
	{
		return _playerName;
	}

	bool IsClosed()
	{
		return _isClosed;
	}
	

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

	std::string _ip;
	std::string _port;

	std::shared_ptr<spdlog::logger> l;

	bool _isClosed;
};

#endif
