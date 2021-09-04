#ifndef _MOVEMESSAGE_H_
#define _MOVEMESSAGE_H_

#include "../OnitamaMessage.h"

class MoveMessage :public OnitamaMessage
{
public:
	MoveMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	void SetTheMove(std::string inMoveInformation);

	std::string GetMove();

private:
	static StaticOnitamaMessageCtor _staticCtor;
	std::string _move;

};

#endif
