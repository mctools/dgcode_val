#include "Core/Python.hh"
#include <pybind11/embed.h> //for scoped_interpreter
#include "Units/Units.hh"
#include <iostream>
#include <sstream>
#include <cstdlib>

int main()
{
  py::scoped_interpreter guard{};

  auto py_Path = pyextra::pyimport("pathlib").attr("Path");
  auto py_unitshh = py_Path( std::getenv( "SBLD_INCLUDE_DIR" ) ).attr("joinpath")( "Units", "Units.hh" );
  auto py_hashlib = pyextra::pyimport("hashlib");
  std::string cppheader_md5 = py_hashlib.attr("md5")( py_unitshh.attr("read_bytes")() ).attr("hexdigest")().cast<std::string>();

  py::object py_builtins = py::module_::import("builtins");
  py::object py_float_fromhex = py_builtins.attr("float").attr("fromhex");
  py::object py_repr = py_builtins.attr("repr");

  auto formatvalue = [&py_float_fromhex,&py_repr]( double x )
  {
    //Transfer value in hexfloat format to python side, so we can use
    //repr(floatval).
    std::ostringstream ss;
    ss << std::hexfloat << x;
    auto pyval = py_float_fromhex( py::str( ss.str() ) );
    return py_repr(pyval).cast<std::string>();
  };

#define EXPORTVAR(thenamespace,x) os << "    " << sbld_stringify(x) << " = "<< formatvalue( thenamespace :: x ) <<"\n"
  auto& os = std::cout;
  os << "\"\"\"\n";
  os << "\n";
  os << "Python module providing the same constants and unit conversion values as in the\n";
  os << "corresponding Units.hh C++ header. Please refer to that header file for\n";
  os << "documentation of all values.\n";
  os << "\n";
  os << "\"\"\"\n";
  os << "\n";
  os << "# This file was autogenerated from a C++ header file with an md5sum\n";
  os << "# checksum: "<<cppheader_md5<<"\n";
  os << "\n";
  os << "__all__ = ['units','constants']\n";
  os << "\n";
  os << "class _Units:\n\n";
  EXPORTVAR( Units, deg );
  EXPORTVAR( Units, angstrom );
  EXPORTVAR( Units, nm );
  EXPORTVAR( Units, um );
  EXPORTVAR( Units, mm );
  EXPORTVAR( Units, cm );
  EXPORTVAR( Units, meter );
  EXPORTVAR( Units, m );
  EXPORTVAR( Units, cm2 );
  EXPORTVAR( Units, cm3 );
  EXPORTVAR( Units, m2 );
  EXPORTVAR( Units, m3 );
  EXPORTVAR( Units, barn );
  EXPORTVAR( Units, second );
  EXPORTVAR( Units, ms );
  EXPORTVAR( Units, millisecond );
  EXPORTVAR( Units, ns );
  EXPORTVAR( Units, nanosecond );
  EXPORTVAR( Units, meV );
  EXPORTVAR( Units, eV );
  EXPORTVAR( Units, keV );
  EXPORTVAR( Units, MeV );
  EXPORTVAR( Units, GeV );
  EXPORTVAR( Units, TeV );
  EXPORTVAR( Units, joule );
  EXPORTVAR( Units, tesla );
  EXPORTVAR( Units, newton );
  EXPORTVAR( Units, pascal );
  EXPORTVAR( Units, bar );
  EXPORTVAR( Units, atmosphere );
  EXPORTVAR( Units, atm );
  EXPORTVAR( Units, coulomb );
  EXPORTVAR( Units, kilogram );
  EXPORTVAR( Units, gram );
  EXPORTVAR( Units, g );
  EXPORTVAR( Units, kelvin );
  EXPORTVAR( Units, mole );
  os << "\n    def __setattr__(self,name,value):\n";
  os << "        raise AttributeError('Units are read-only ')\n";
  os << "    def __delattr__(self,name,value):\n";
  os << "        raise AttributeError('Units are read-only ')\n";
  os << "\n";
  os << "class _Constants:\n\n";
  EXPORTVAR( Constants, pi );
  EXPORTVAR( Constants, c_light );
  EXPORTVAR( Constants, c_squared );
  EXPORTVAR( Constants, atomic_unit_of_charge );
  EXPORTVAR( Constants, avogadro );
  EXPORTVAR( Constants, h_Planck );
  EXPORTVAR( Constants, k_Boltzmann );
  EXPORTVAR( Constants, neutron_mass_c2 );
  EXPORTVAR( Constants, proton_mass_c2 );
  os << "\n    def __setattr__(self,name,value):\n";
  os << "        raise AttributeError('Constants are read-only ')\n";
  os << "    def __delattr__(self,name,value):\n";
  os << "        raise AttributeError('Constants are read-only ')\n";
  os << "\n";
  os << "units = _Units()\n";
  os << "constants = _Constants()\n";
}
