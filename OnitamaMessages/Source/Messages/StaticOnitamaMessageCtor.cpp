
#include "StaticOnitamaMessageCtor.h"



StaticOnitamaMessageCtor::StaticOnitamaMessageCtor(
	std::string inName, 
	CreateSelfLambda inSelfCreator)
{
	std::map<std::string, CreateSelfLambda> & l =
		StaticOnitamaMessageCtor::GetMessageList();
	l[inName] = inSelfCreator;
}

// Will check if the according message exists
bool StaticOnitamaMessageCtor::HasMessage(std::string inMsgName)
{
	std::map<std::string, CreateSelfLambda> & l =
		StaticOnitamaMessageCtor::GetMessageList();
	//return (l.find(inMsgName) != l.end());
	return (l.count(inMsgName) == 1);
}

// Will return the according message
CreateSelfLambda StaticOnitamaMessageCtor::GetMessageCreator(std::string inMsgName)
{
	std::map<std::string, CreateSelfLambda> & l =
		StaticOnitamaMessageCtor::GetMessageList();
	return l[inMsgName];
}

std::map<std::string, CreateSelfLambda> & StaticOnitamaMessageCtor::GetMessageList()
{
	static std::map<std::string, CreateSelfLambda> list
		= std::map<std::string, CreateSelfLambda>();
	return list;
}
