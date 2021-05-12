#ifndef _CONNENTITY_H_
#define _CONNENTITY_H_

#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <nedb.h>
#include <unistd.h>
#endif

class ConnEntity 
{
public:
	ConnEntity(SOCKET inS);
	bool ReadGreetingMessage();

private:
	SOCKET _s;
	bool _hasGreeted;
	std::string _playerName;
	std::string _sessionName;
	unsigned int _connectedAtTime;


};

#endif
