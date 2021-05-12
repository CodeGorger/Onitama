#include "IDoable.h"

IDoable::IDoable()
{
	isShutdownRequested = false;
}

void IDoable::RequestShutdown()
{
	isShutdownRequested = true;
}

bool IDoable::IsShutdownRequested()
{
	return isShutdownRequested;
}

