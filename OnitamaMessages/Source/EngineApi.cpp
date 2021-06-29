// pybind11_wrapper.cpp
#include "MessageParser.h"
#include <iostream>
#include <iomanip>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


PYBIND11_MODULE(OnitamaEngine, m)
{
	m.doc() = "OnitamaEngine DLL";
	//m.def("cpp_function", &cppmult, "A function that multiplies two numbers");

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
		.export_values();
}
	
