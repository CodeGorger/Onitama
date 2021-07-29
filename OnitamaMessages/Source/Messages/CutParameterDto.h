#ifndef _CUTPARAMETERDTO_H_
#define _CUTPARAMETERDTO_H_

#include <string>

class CutParameterDto
{
public:
	CutParameterDto();
	void SetParameter(std::string inCutParameter);
	void SetContentRest(std::string inContentRest);
	void SetSuccessStatus(bool inStatus);

	std::string GetParameter();
	std::string GetContentRest();
	bool GetSuccessStatus();

private:
	// The cut away parameter string of the message
	std::string _cutParameter;

	// The message rest that has been cut away from
	std::string _contentRest;

	// A general return code about success of failure
	// true ... success
	// false ... failure
	bool _status;

};

#endif
