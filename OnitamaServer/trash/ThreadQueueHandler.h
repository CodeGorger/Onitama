#ifndef _THREADQUEUEHANDLER_H_
#define _THREADQUEUEHANDLER_H_


#include <memory>

template <class T>
class ThreadQueueHandler
{
public:
	ThreadQueueHandler();

	void Enque(std::unique_ptr<T> &);
	std::unique_ptr<T> Deque();


private:
	std::queue<T> _threadQueue;


};


#endif

