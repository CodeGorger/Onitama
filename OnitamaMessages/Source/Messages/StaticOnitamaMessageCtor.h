#ifndef _STATICONITAMAMESSAGECTOR_H_
#define _STATICONITAMAMESSAGECTOR_H_

#include <string>
#include <map>
#include <memory>

//#include "OnitamaMessage.h"
class OnitamaMessage;
typedef std::shared_ptr<OnitamaMessage>(*CreateSelfLambda)(void);



class StaticOnitamaMessageCtor
{
public:
	StaticOnitamaMessageCtor(std::string inName, CreateSelfLambda inSelfCreator);

	// Will check if the according message exists
	static bool HasMessage(std::string inMsgName);

	// Will return the according message
	static CreateSelfLambda GetMessageCreator(std::string inMsgName);

	// Will hold all known OnitamaMessages.
	static std::map<std::string, CreateSelfLambda> & GetMessageList();

private:
	//std::string _name;
	//CreateSelfLambda _selfCreator;
};



#endif