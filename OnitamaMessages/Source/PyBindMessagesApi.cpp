// pybind11_wrapper.cpp
#include "MessageParser.h"
#include <iostream>
#include <iomanip>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Messages/Greeting/GreetingMessage.h"
#include "Messages/SessionList/SessionListMessage.h"


PYBIND11_MODULE(OnitamaMessages, m)
{
	m.doc() = "OnitamaMessages DLL";
	m.def("ParseMessage", &ParseMessage, 
		"Will parse a message-string and return a message object.");

	////TODO(Simon): Add doc for python
	//pybind11::class_<OnitamaEngine>(m, "OnitamaEngine")
	//	.def(pybind11::init<>())
	//	.def("ValidateMove", &OnitamaEngine::ValidateMove)
	//	.def("GetCurrentBoardState", &OnitamaEngine::GetCurrentBoardState)
	//	.def("PrintBoard", &OnitamaEngine::PrintBoard)
	//	.def("PrintBoardAndAxes", &OnitamaEngine::PrintBoardAndAxes)
	//	.def("GetCurrentCardsRed", &OnitamaEngine::GetCurrentCardsRed)
	//	.def("GetCurrentCardsBlue", &OnitamaEngine::GetCurrentCardsBlue)
	//	.def("GetCenterCard", &OnitamaEngine::GetCenterCard);
	//	//.def("GetAllPossibleMoves", &OnitamaEngine::GetAllPossibleMoves);



	pybind11::class_<MessageParsedDTO>(m, "MessageParsedDTO")
		.def(pybind11::init<>())
		.def("SetMessage", &MessageParsedDTO::SetMessage)
		.def("SetRest", &MessageParsedDTO::SetRest)
		.def("SetResult", &MessageParsedDTO::SetResult)
		.def("GetOnitamaMessage", &MessageParsedDTO::GetOnitamaMessage)
		.def("GetResult", &MessageParsedDTO::GetResult)
		.def("GetRest", &MessageParsedDTO::GetRest);
	

	pybind11::class_<GreetingMessage>(m, "GreetingMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &GreetingMessage::ParseContent)
		.def("ToString", &GreetingMessage::ToString)
		.def("GetPlayerName", &GreetingMessage::GetPlayerName)
		.def("SetPlayerName", &GreetingMessage::SetPlayerName);


	pybind11::class_<SessionListMessage>(m, "SessionListMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &SessionListMessage::ParseContent)
		.def("ToString", &SessionListMessage::ToString)
		.def("SetPlayGetSessionNameserName", &SessionListMessage::GetSessionNames);


	pybind11::enum_<MessageStringResult>(m, "MessageStringResult")
		.value(
			"MessageStringResult_Complete", 
			MessageStringResult::MessageStringResult_Complete)
		.value(
			"MessageStringResult_Trash", 
			MessageStringResult::MessageStringResult_Trash)
		.value(
			"MessageStringResult_PossibleBeginning", 
			MessageStringResult::MessageStringResult_PossibleBeginning)
		.value(
			"MessageStringResult_TooLong",
			MessageStringResult::MessageStringResult_TooLongNotComplete)
		.value(
			"MessageStringResult_NotInited",
			MessageStringResult::MessageStringResult_NotInited)
		.export_values();
}
	
