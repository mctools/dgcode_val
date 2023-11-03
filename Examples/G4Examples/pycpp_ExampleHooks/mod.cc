#include "Core/Python.hh"
#include "G4Examples/ExampleHooks.hh"

PYTHON_MODULE3
{
  mod.def("prepreInitHook",&ExampleHooks::prepreInitHook);
  mod.def("preInitHook",&ExampleHooks::preInitHook);
  mod.def("postInitHook",&ExampleHooks::postInitHook);
}
