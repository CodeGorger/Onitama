// pybind11_wrapper.cpp
#include <iostream>
#include <iomanip>
#include <pybind11/pybind11.h>
#include "PyBindEngineApi.h"
#include "../OnitamaEngine/OnitamaEngine.h"
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
		.def("GetCenterCard", &OnitamaEngine::GetCenterCard)
		.def("SetCurrentCardsRed", &OnitamaEngine::SetCurrentCardsRed)
		.def("SetCurrentCardsBlue", &OnitamaEngine::SetCurrentCardsBlue)
		.def("SetCurrentCardCenter", &OnitamaEngine::SetCurrentCardCenter);

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


	pybind11::class_<Point2D>(m, "Point2D")
		.def(pybind11::init<int, int>())
		.def("ParseFromChessString", 
			&Point2D::ParseFromChessString)
		.def("ToXyString", &Point2D::ToXyString)
		.def("ToChessString", &Point2D::ToChessString)
		.def("GetRotated", &Point2D::GetRotated)
		.def("Equals", &Point2D::operator==)
		.def("Add", &Point2D::operator+)
		.def("GetY", &Point2D::GetY)
		.def("GetY", &Point2D::GetY);

	pybind11::class_<MoveInformation>(m, "MoveInformation")
		.def(pybind11::init<>())
		.def(pybind11::init<std::string>())
		.def(pybind11::init<std::string, Point2D, Point2D>())
		.def("ParseMove", &MoveInformation::ParseMove)
		.def("GetFigureStartPosition", 
			&MoveInformation::GetFigureStartPosition)
		.def("GetFigureEndPosition", 
			&MoveInformation::GetFigureEndPosition)
		.def("GetCardName", &MoveInformation::GetCardName);


}