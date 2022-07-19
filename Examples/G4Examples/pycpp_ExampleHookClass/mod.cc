#include "Core/Python.hh"
#include "G4Examples/ExampleHookClass.hh"

PYTHON_MODULE
{
  py::class_<ExampleHookClass,boost::noncopyable,py::bases<Utils::ParametersBase> >("ExampleHookClass",py::init<>())
    .def("prepreInitHook",&ExampleHookClass::prepreInitHook)
    .def("preInitHook",&ExampleHookClass::preInitHook)
    .def("postInitHook",&ExampleHookClass::postInitHook)
    ;
}
