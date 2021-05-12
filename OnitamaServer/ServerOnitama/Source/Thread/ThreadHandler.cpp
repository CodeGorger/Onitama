#include "ThreadHandler.h"


ThreadHandler::ThreadHandler()
:_thread(std::thread())
, _isRunning(false)
, _isShutdownRequested(false)
{
}


void ThreadHandler::Start()
{
	_thread = std::thread(&ThreadHandler::_do, this);
	_isRunning = true;
}


void ThreadHandler::Shutdown()
{
	if (_thread.joinable())
	{
		_thread.join();
	}
	_isRunning = false;
}


bool ThreadHandler::IsRunning()
{
	return _isRunning;
}

bool ThreadHandler::IsShutdownRequested()
{
	return _isShutdownRequested;
}
