// pybind11_wrapper.cpp
#include <iostream>
#include <iomanip>
#include <pybind11/pybind11.h>
#include "EngineApi.h"
#include "OnitamaEngine.h"
PYBIND11_MODULE(MyLib1, m)
{

	m.doc() = "OnitamaEngine DLL";
	//m.def("cpp_function", &cppmult, "A function that multiplies two numbers");

	pybind11::class_<OnitamaEngine>(m, "OnitamaEngine")
		.def(pybind11::init<>())
		.def("ValidateMove", &OnitamaEngine::ValidateMove);
	//	.def("EricMagTofu_RiesenFan", &Point2D::ToXYXYXYList);

}