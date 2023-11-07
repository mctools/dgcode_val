#include "Core/String.hh"
#include "Units/Units.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#ifdef pascal
#  undef pascal //CLHEP system of units sets this nasty define
#endif
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <iomanip>



void verify( const char * varname, double x_clhep, double x_our, double prec = 1e-15 )
{
  double reldiff = fabs( x_clhep - x_our ) / (0.5 * ( fabs(x_clhep) + fabs(x_our) ) );
  if ( reldiff < prec )
    return;
  std::ostringstream ss;
  ss << std::setprecision(19)<< '"' << varname <<"\" value is not consistent between"
    " SystemOfUnits ("<<x_clhep<<") and our Units.hh ("<<x_our<<")";
  throw std::runtime_error( ss.str() );
}


int main()
{
#define VERIFYUNIT( varname ) verify( sbld_stringify(varname), CLHEP:: varname, NewUnits:: varname );
  VERIFYUNIT( deg );
  VERIFYUNIT( angstrom );
  VERIFYUNIT( nm );
  VERIFYUNIT( um );
  VERIFYUNIT( mm );
  VERIFYUNIT( cm );
  VERIFYUNIT( meter );
  VERIFYUNIT( m );
  VERIFYUNIT( cm2 );
  VERIFYUNIT( cm3 );
  VERIFYUNIT( m2 );
  VERIFYUNIT( m3 );
  VERIFYUNIT( second );
  VERIFYUNIT( ms );
  VERIFYUNIT( millisecond );
  VERIFYUNIT( ns );
  VERIFYUNIT( nanosecond );
  verify( "meV", CLHEP::eV * 0.001, NewUnits::meV );
  VERIFYUNIT( eV );
  VERIFYUNIT( keV );
  VERIFYUNIT( MeV );
  VERIFYUNIT( GeV );
  VERIFYUNIT( TeV );
  VERIFYUNIT( joule );
  VERIFYUNIT( tesla );
  VERIFYUNIT( newton );
  verify( "pascal", CLHEP::hep_pascal, NewUnits::pascal );
  VERIFYUNIT( bar );
  VERIFYUNIT( atmosphere );
  verify( "atm", CLHEP::atmosphere, NewUnits::atm );
  VERIFYUNIT( coulomb );
  VERIFYUNIT( kilogram );
  VERIFYUNIT( gram );
  VERIFYUNIT( g );
  VERIFYUNIT( kelvin );
  VERIFYUNIT( mole );

#define VERIFYCONSTANT( varname ) verify( sbld_stringify(varname), CLHEP:: varname, NewConstants:: varname );
  VERIFYCONSTANT( pi );
  VERIFYCONSTANT( c_light );
  VERIFYCONSTANT( c_squared );
  verify( "atomic_unit_of_charge", CLHEP::e_SI, NewConstants::atomic_unit_of_charge );
  verify( "avogadro", CLHEP::Avogadro, NewConstants::avogadro );
  VERIFYCONSTANT( h_Planck );
  verify( "k_Boltzmann", CLHEP::k_Boltzmann, NewConstants::k_Boltzmann, 1e-7 );//<--- NB: REDUCED PRECISION
  verify( "neutron_mass_c2", CLHEP::neutron_mass_c2, NewConstants::neutron_mass_c2, 1e-7 );//<--- NB: REDUCED PRECISION
}
