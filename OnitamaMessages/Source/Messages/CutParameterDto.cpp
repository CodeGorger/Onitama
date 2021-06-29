#include "CutParameterDto.h"

CutParameterDto::CutParameterDto()
	:_cutParameter("")
	,_contentRest("")
	,_status(false)
{
}

void CutParameterDto::SetParameter(std::string inCutParameter)
{
	_cutParameter=inCutParameter;
}

void CutParameterDto::SetContentRest(std::string inContentRest)
{
	_contentRest = inContentRest;
}

void CutParameterDto::SetSuccessStatus(bool inStatus)
{
	_status = inStatus;
}


std::string CutParameterDto::GetParameter()
{
	return _cutParameter;
}

std::string CutParameterDto::GetContentRest()
{
	return _contentRest;
}

bool CutParameterDto::GetSuccessStatus()
{
	return _status;
}