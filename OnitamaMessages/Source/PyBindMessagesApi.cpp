// pybind11_wrapper.cpp
#include "MessageParser.h"
#include <iostream>
#include <iomanip>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Messages/GreetingMessage/GreetingMessage.h"
#include "Messages/SessionListMessage/SessionListMessage.h"
#include "Messages/JoinSessionMessage/JoinSessionMessage.h"
#include "Messages/SessionInformationMessage/SessionInformationMessage.h"
#include "Messages/GamestartRequestMessage/GamestartRequestMessage.h"
#include "Messages/LeaveSessionMessage/LeaveSessionMessage.h"
#include "Messages/GamestartMessage/GamestartMessage.h"


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
	
	pybind11::class_<OnitamaMessage, std::shared_ptr<OnitamaMessage>>(m, "OnitamaMessage");

	pybind11::class_<GreetingMessage, std::shared_ptr<GreetingMessage>>(m, "GreetingMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &GreetingMessage::ParseContent)
		.def("ToString", &GreetingMessage::ToString)
		.def("GetPlayerName", &GreetingMessage::GetPlayerName)
		.def("SetPlayerName", &GreetingMessage::SetPlayerName);


	pybind11::class_<SessionListMessage, 
		std::shared_ptr<SessionListMessage>>(m, "SessionListMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &SessionListMessage::ParseContent)
		.def("ToString", &SessionListMessage::ToString)
		.def("GetSessionNames", &SessionListMessage::GetSessionNames);


	pybind11::class_<SessionInformationMessage, 
		std::shared_ptr<SessionInformationMessage>>(m, "SessionInformationMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &SessionInformationMessage::ParseContent)
		.def("ToString", &SessionInformationMessage::ToString)
		.def("GetOppoName", &SessionInformationMessage::GetOppoName)
		.def("IsHost", &SessionInformationMessage::IsHost);


	pybind11::class_<JoinSessionMessage, 
		std::shared_ptr<JoinSessionMessage>>(m, "JoinSessionMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &JoinSessionMessage::ParseContent)
		.def("ToString", &JoinSessionMessage::ToString)
		.def("SetSessionName", &JoinSessionMessage::SetSessionName);

	pybind11::class_<GamestartRequestMessage, 
		std::shared_ptr<GamestartRequestMessage>>(m, "GamestartRequestMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &GamestartRequestMessage::ParseContent)
		.def("ToString", &GamestartRequestMessage::ToString);

	pybind11::class_<LeaveSessionMessage, 
		std::shared_ptr<LeaveSessionMessage>>(m, "LeaveSessionMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &LeaveSessionMessage::ParseContent)
		.def("ToString", &LeaveSessionMessage::ToString);


	pybind11::class_<GamestartMessage,
		std::shared_ptr<GamestartMessage>>(m, "GamestartMessage")
		.def(pybind11::init<>())
		.def("ParseContent", &GamestartMessage::ParseContent)
		.def("ToString", &GamestartMessage::ToString)
		.def("GetCard1", &GamestartMessage::GetCard1)
		.def("GetCard2", &GamestartMessage::GetCard2)
		.def("GetOppoCard1", &GamestartMessage::GetOppoCard1)
		.def("GetOppoCard2", &GamestartMessage::GetOppoCard2)
		.def("GetCenterCard", &GamestartMessage::GetCenterCard)
		.def("GetStartingPlayer", &GamestartMessage::GetStartingPlayer)
		.def("GetOppoName", &GamestartMessage::GetOppoName);


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
	
