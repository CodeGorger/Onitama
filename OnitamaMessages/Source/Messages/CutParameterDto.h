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
	std::string _cutParameter;
	std::string _contentRest;
	bool _status;

};

#endif
