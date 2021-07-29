#ifndef _SESSIONINFORMATIONMESSAGE_H_
#define _SESSIONINFORMATIONMESSAGE_H_

#include "../OnitamaMessage.h"

class SessionInformationMessage :public OnitamaMessage
{
public:
	SessionInformationMessage();
	void ParseContent(std::string inMessageContent);
	std::string ToString();

	std::string GetOppoName();
	void SetOppoName(std::string inOppoName);

	bool IsHost();
	void SetIsHost(bool inIsHost);

private:
	std::string _oppoName;
	bool _isHost;
};

#endif
