#ifndef _ONITAMAMESSAGE_H_
#define _ONITAMAMESSAGE_H_

#include <string>

class OnitamaMessage
{
public:
	OnitamaMessage(std::string inMessageName, unsigned int inMaxLegalLength);
	bool IsValidateMessageString();

private:
	std::string _messageName;
	unsigned int _maxLegalLength;

	int _length;
	std::string _messageInformation;
};

#endif
