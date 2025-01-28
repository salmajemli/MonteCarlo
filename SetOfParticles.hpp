#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "Simulation.hpp"
#include "parameters.hpp"




class SetOfParticles
{
private:
   const AbstractDomain* _Domain;
   const struct_simulationParams _simulationParams;
   const int _nbParticles;
   double _u;
   double _t;
   std::vector<double> _x;

public:
   SetOfParticles(const AbstractDomain*, const struct_simulationParams& simulationParams, double& u, const std::vector<double>& x, double& t);
   ~SetOfParticles();

   void simulateMotion(); 
   const double& get_u() const { return this->_u; };
};