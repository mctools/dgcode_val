#include "Core/Python.hh"
#include "G4Examples/ExampleHooks.hh"

PYTHON_MODULE
{
  py::def("prepreInitHook",&ExampleHooks::prepreInitHook);
  py::def("preInitHook",&ExampleHooks::preInitHook);
  py::def("postInitHook",&ExampleHooks::postInitHook);
}
