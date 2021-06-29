#ifndef _READJOINSESSIONDTO_H_
#define _READJOINSESSIONDTO_H_

#include <string>

class ReadJoinSessionDto
{
public:

	ReadJoinSessionDto()
		: _retStatus(999)
	{
	}

	ReadJoinSessionDto(
		int inRetStatus)
		: _retStatus(inRetStatus)
	{
	}

	ReadJoinSessionDto(
		int inRetStatus,
		std::string inSessionName)
		: _sessionName(inSessionName)
		, _retStatus(inRetStatus)
	{
	}

	std::string GetSessionName()
	{
		return _sessionName;
	}

	int GetReturnStatus()
	{
		return _retStatus;
	}

private:
	std::string _sessionName;
	int _retStatus;


};


#endif