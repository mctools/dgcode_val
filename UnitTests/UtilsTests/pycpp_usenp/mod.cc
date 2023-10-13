#include "Core/Python.hh"
#include "Utils/NumpyUtils.hh"

namespace UtilsTests {
  py::object gensquares() {
    std::size_t n = 100000;
#ifdef DGCODE_USEPYBIND11
    auto o = py::array_t<double>(n);
    double * buf = o.mutable_data();
#else
    double * buf;
    py::object o = NumpyUtils::create_numpyarray(n,buf);
#endif
    for (std::size_t i = 0;i<n;++i)
      buf[i] = i*i;
    return o;
  }
}


PYTHON_MODULE
{
  PYDEF("gensquares",UtilsTests::gensquares);
}
