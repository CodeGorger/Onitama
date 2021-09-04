#ifndef _SESSIONINFORMATIONMESSAGE_H_
#define _SESSIONINFORMATIONMESSAGE_H_

#include "../OnitamaMessage.h"

class SessionInformationMessage :public OnitamaMessage
{
public:
	SessionInformationMessage();
	virtual void ParseContent(std::string inMessageContent);
	virtual std::string ToString();
	static std::shared_ptr<OnitamaMessage> CreateSelf();

	std::string GetOppoName();
	void SetOppoName(std::string inOppoName);

	bool IsHost();
	void SetIsHost(bool inIsHost);

private:
	static StaticOnitamaMessageCtor _staticCtor;
	std::string _oppoName;
	bool _isHost;

};

#endif
