#include "LeptonWeighter/NFluxInterface.h"

namespace LW {

double atmosNeutrinoFlux::EvaluateFlux(const Event& e) const{
  if(!nugen_compatible)
    return(flux->getFlux((nuflux::ParticleType)e.primary_type, e.energy, cos(e.zenith)));
  else
    return 2.*(flux->getFlux((nuflux::ParticleType)e.primary_type, e.energy, cos(e.zenith)));
}

} // close LW namespace
