#include "Core/Python.hh"
#include "G4Examples/ExampleHookClass.hh"

PYTHON_MODULE
{
#ifdef DGCODE_USEPYBIND11
  py::class_<ExampleHookClass,Utils::ParametersBase>(m,"ExampleHookClass")
    .def( py::init<>() )
#else
  py::class_<ExampleHookClass,boost::noncopyable,py::bases<Utils::ParametersBase> >("ExampleHookClass",py::init<>())
#endif
    .def("prepreInitHook",&ExampleHookClass::prepreInitHook)
    .def("preInitHook",&ExampleHookClass::preInitHook)
    .def("postInitHook",&ExampleHookClass::postInitHook)
    ;
}
