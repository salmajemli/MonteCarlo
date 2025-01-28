#ifndef PARAMETRES_HPP
#define PARAMETRES_HPP

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

#include <string>

struct struct_simulationParams {
    int Dim , Nmc; 
    int Nx , Ny , Nz;
    double time , Tf, dt; 
    double sigma_S , sigma_T ;
    std::vector<double> velocity;
    double xmin , ymin , zmin , xmax , ymax , zmax  ;
    std::string fileName ;

};

void Read_params(struct_simulationParams& simulationParams_1);

#endif
