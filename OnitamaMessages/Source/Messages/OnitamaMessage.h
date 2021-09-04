#ifndef _ONITAMAMESSAGE_H_
#define _ONITAMAMESSAGE_H_

#include <string>
#include "CutParameterDto.h"
#include "StaticOnitamaMessageCtor.h"



class OnitamaMessage
{
public:
	OnitamaMessage(std::string inMessageName, unsigned int inMaxLegalLength);

	// Will get the string content of a message, 
	// example: "Greeting:Simon,;" The string from ':' to ';'
	//          so "Simon,"
	virtual void ParseContent(std::string inMessageContent) = 0;

	// Will return the message in form of a string
	// msg-name+":":+para1+","+ ... + ";"
	// "Greeting:Simon,;"
	virtual std::string ToString() = 0;

protected:
	CutParameterDto CutNextParameter(std::string inMessageContent);
	std::string _messageName;

	static std::shared_ptr<OnitamaMessage> CreateSelf();


private:
	unsigned int _maxLegalLength;

	int _length;
	std::string _messageInformation;


};



#endif
