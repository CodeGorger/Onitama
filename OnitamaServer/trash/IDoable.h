
#ifndef _IDOABLE_H_
#define _IDOABLE_H_

#include <queue>
#include <memory>
#include "IThreadQueueHandler.h"


class IDoable
{
public:
	IDoable();
	virtual void Do() = 0;
	void RequestShutdown();
	bool IsShutdownRequested();

	//void SetOutQueue(OutputList inOutputQueue);
	void SetOutputer(std::shared_ptr<IThreadQueueHandler> inOutputer);

	
protected:
	bool isShutdownRequested;
	std::shared_ptr<IThreadQueueHandler> _outputer;

	//void _enqueueOutput(std::unique_ptr<IThreadOutputElement> inElement);
};
#endif

