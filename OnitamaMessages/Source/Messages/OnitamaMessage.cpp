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
	size_t firstComma = inMessageContent.find_first_of(',');
	std::string cutParameter = inMessageContent.substr(0, firstComma);
	std::string contentRest = inMessageContent.substr(
		firstComma - 1,
		cutParameter.length() - firstComma);

	CutParameterDto ret;

	ret.SetParameter(cutParameter);
	ret.SetContentRest(contentRest);
	ret.SetSuccessStatus(true);

	return ret;
}

















