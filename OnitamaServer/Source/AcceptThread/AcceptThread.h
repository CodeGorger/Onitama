#ifndef _ACCEPTTHREAD_H_
#define _ACCEPTTHREAD_H_

#include <vector>
#include <iostream>
#include "../Thread/ThreadHandler.h"
#include "../ConnEntity/ConnEntity.h"
#include "../ThreadSafeQueue/ThreadSafeQueue.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class AcceptThread :public ThreadHandler
{
public:
	AcceptThread();
	ThreadSafeQueue<std::shared_ptr<ConnEntity>> GetOutputQueue();

private:
	void _do();

	ThreadSafeQueue<std::shared_ptr<ConnEntity>> _outputQueue;

	SOCKET _listenSocket;

	int _sockInit(void);
	int _sockQuit(void);
	int _sockClose(SOCKET sock);
	int _initTcpListenSocket();
	int _tcpAcceptThreadMethod();

	int _listenPort;

	std::shared_ptr<spdlog::logger> l;
};


#endif
