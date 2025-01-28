#include "SetOfParticles.hpp"


SetOfParticles::SetOfParticles(const AbstractDomain* Domain, const struct_simulationParams& simulationParams, double& u, const std::vector<double>& x, double& t) :
   _Domain(Domain),
   _simulationParams(simulationParams),
   _nbParticles(simulationParams.Nmc),
   _u(u),
   _x(x),
   _t(t)
{
};

SetOfParticles::~SetOfParticles()
{
};


void SetOfParticles::simulateMotion()
{
   for (int i = 0; i < this->_simulationParams.Nmc; i++)
   {
      Particle particle(this->_Domain, this->_simulationParams, this->_x);
      particle.simulateMotion(_u);
   }
};
