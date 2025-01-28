#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

#include "parameters.hpp"



class AbstractDomain
{

public:
   AbstractDomain(const struct_simulationParams& simulationParams);
   virtual ~AbstractDomain();


   const struct_simulationParams _simulationParams;

   double initialCondition(const std::vector<double>&, const std::vector<double>&) const;
   virtual void applyBoundaryConditions(std::vector<double>&, double&, std::vector<double>&) const = 0;
   
   double Norm_Vector(const std::vector<double> a, const std::vector<double> b) const ;
   std::vector<double> dotProductScal(const double a, const std::vector<double> b) const ;
   std::vector<double> SumVec(const std::vector<double> a, const std::vector<double> b) const ;


   double integrateAlpha(double x, double v, std::vector<double> vp) const;
   double sampleTau(const std::vector<double>&, const double&, const std::vector<double>&) const;
   std::vector<double> Vprime(const std::vector<double>&, const double&, const double&, const std::vector<double>&) const;

   std::vector<std::vector<double>> get_DomainLimits() const;
};



class BoundaryDomain : public AbstractDomain
{
public:
   BoundaryDomain(const struct_simulationParams& simulationParams) : AbstractDomain(simulationParams) {};
   virtual ~BoundaryDomain();
   virtual void applyBoundaryConditions(std::vector<double>&, double&, std::vector<double>&) const;
};



class Particle
{
private:
   const struct_simulationParams _simulationParams;
   const AbstractDomain* _Domain;
   std::vector<double> _xp , _vp;
   double _sp, _wp, _t;
   

public:
   Particle(const AbstractDomain*, const struct_simulationParams& simulationParams, const std::vector<double>& x);
   ~Particle();

   bool OutDomain() const;
   virtual void simulateMotion(double&);
};