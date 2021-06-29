#ifndef _ACCEPTTHREAD_H_
#define _ACCEPTTHREAD_H_

#include <vector>
#include <iostream>
#include "../Thread/ThreadHandler.h"
#include "../ConnEntity/ConnEntity.h"

class AcceptThread :public ThreadHandler
{
public:
	AcceptThread();
	std::shared_ptr<std::vector<ConnEntity>> GetOutputQueue();

private:
	void _do();

	std::shared_ptr<std::vector<ConnEntity>> _outputQueue;

	SOCKET _listenSocket;

	int _sockInit(void);
	int _sockQuit(void);
	int _sockClose(SOCKET sock);
	int _initTcpListenSocket();
	int _tcpAcceptThreadMethod();


};


#endif