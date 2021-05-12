
#ifndef _THREADHANDLER_H_
#define _THREADHANDLER_H_

#include <thread>

class ThreadHandler
{
public:
	ThreadHandler();

	void Start();
	void Shutdown();

	bool IsRunning();
	bool IsShutdownRequested();

protected:
	std::thread _thread;
	bool _isRunning;
	bool _isShutdownRequested;

	virtual void _do() = 0;

};


#endif
