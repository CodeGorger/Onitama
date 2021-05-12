// pybind11_wrapper.cpp
#include <iostream>
#include <iomanip>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


PYBIND11_MODULE(OnitamaEngine, m)
{
	m.doc() = "OnitamaEngine DLL";
	//m.def("cpp_function", &cppmult, "A function that multiplies two numbers");

	//TODO(Simon): Add doc for python
	pybind11::class_<OnitamaEngine>(m, "OnitamaEngine")
		.def(pybind11::init<>())
		.def("ValidateMove", &OnitamaEngine::ValidateMove)
		.def("GetCurrentBoardState", &OnitamaEngine::GetCurrentBoardState)
		.def("PrintBoard", &OnitamaEngine::PrintBoard)
		.def("PrintBoardAndAxes", &OnitamaEngine::PrintBoardAndAxes)
		.def("GetCurrentCardsRed", &OnitamaEngine::GetCurrentCardsRed)
		.def("GetCurrentCardsBlue", &OnitamaEngine::GetCurrentCardsBlue)
		.def("GetCenterCard", &OnitamaEngine::GetCenterCard);
		//.def("GetAllPossibleMoves", &OnitamaEngine::GetAllPossibleMoves);

	pybind11::class_<Card>(m, "Card")
		.def(pybind11::init<>())
		.def(pybind11::init<std::string, bool>())
		.def("GetJumpOptions", &Card::GetJumpOptions)
		.def("GetName", &Card::GetName)
		.def("GetGridStringBlue", &Card::GetGridStringBlue)
		.def("GetGridBlue", &Card::GetGridBlue)
		.def("GetGridStringRed", &Card::GetGridStringRed)
		.def("GetGridRed", &Card::GetGridRed);

}