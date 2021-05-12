#ifndef _CONNENTITYTHREADQUEUE_H_
#define _CONNENTITYTHREADQUEUE_H_

#include "ThreadQueueHandler.h"
#include "ConnEntity.h"

class ConnEntityThreadQueue :public ThreadQueueHandler
{

	virtual void Enque(std::unique_ptr<IThreadQueueElement>&) = 0;
	virtual std::unique_ptr<IThreadQueueElement> Deque() = 0;

};

#endif