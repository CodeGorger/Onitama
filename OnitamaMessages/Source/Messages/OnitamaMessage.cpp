#include "OnitamaMessage.h"


OnitamaMessage::OnitamaMessage(
	std::string inMessageName, 
	unsigned int inMaxLegalLength)
	:_messageName(inMessageName)
	,_maxLegalLength(inMaxLegalLength)
	,_length(0)
{

}


CutParameterDto OnitamaMessage::CutNextParameter(std::string inMessageContent)
{
	CutParameterDto ret;

	int firstComma = inMessageContent.find_first_of(',');
	if (-1 == firstComma)
	{
		ret.SetParameter("");
		ret.SetContentRest("");
		ret.SetSuccessStatus(false);
		return ret;
	}

	std::string cutParameter = inMessageContent.substr(0, firstComma);
	std::string contentRest = inMessageContent.substr(firstComma+1);

	ret.SetParameter(cutParameter);
	ret.SetContentRest(contentRest);
	ret.SetSuccessStatus(true);

	return ret;
}

std::shared_ptr<OnitamaMessage> OnitamaMessage::CreateSelf()
{
	exit(-100);
}











