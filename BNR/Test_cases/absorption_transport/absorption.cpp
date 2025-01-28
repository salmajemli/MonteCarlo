#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include "../../../SetOfParticles.hpp"

using namespace std;

int main(int argc, char const* argv[])
{
   struct struct_simulationParams simulationParams;
   simulationParams.fileName = "param_absorption.txt";
   Read_params(simulationParams);

   AbstractDomain* Domaine = nullptr;
   Domaine = new BoundaryDomain(simulationParams);

   

   double Mesh_size_x = (simulationParams.xmax - simulationParams.xmin) / (simulationParams.Nx) ;
   double Mesh_size_y = (simulationParams.ymax - simulationParams.ymin) / (simulationParams.Ny) ;
   double Mesh_size_z = (simulationParams.zmax - simulationParams.zmin) / (simulationParams.Nz) ;



   double u , u_exacte; 
    double dt=simulationParams.dt;
   double v1=simulationParams.velocity[0],v2=simulationParams.velocity[1], v3=simulationParams.velocity[2];
   double v = sqrt(v1*v1+v2*v2+v3*v3);


   for (int i = 0; i < simulationParams.Nx; i++)
   {
      for (int j = 0; j < simulationParams.Ny; j++)
      {
         for (int k = 0; k < simulationParams.Nz; k++)
         {
            double position_x = simulationParams.xmin + i  * Mesh_size_x;
            double position_y = simulationParams.ymin + j * Mesh_size_y;
            double position_z = simulationParams.zmin + k * Mesh_size_z;

            u = Domaine->initialCondition({ position_x, position_y, position_z }, simulationParams.velocity);
            

            SetOfParticles packOfParticles(Domaine, simulationParams, u, { position_x, position_y, position_z }, simulationParams.time);

            packOfParticles.simulateMotion();

            u = packOfParticles.get_u();
        
         }
      }
   }
   simulationParams.time += simulationParams.dt;



   double Nf = int(simulationParams.Tf / simulationParams.dt) + 1;

   for (int n = 1; n < Nf; n++)
   {


      double error_sum = 0.0; 
      double max_error = 0.0;
      for (int i = 0; i < simulationParams.Nx; i++)
      {
         for (int j = 0; j < simulationParams.Ny; j++)
         {
            for (int k = 0; k < simulationParams.Nz; k++)
            {
               double position_x = simulationParams.xmin + i * Mesh_size_x;
               double position_y = simulationParams.ymin + j * Mesh_size_y;
               double position_z = simulationParams.zmin + k * Mesh_size_z;
               u = 0.0;
                              
               SetOfParticles packOfParticles(Domaine, simulationParams, u, { position_x, position_y, position_z }, simulationParams.time);
               packOfParticles.simulateMotion();
               u = packOfParticles.get_u();

                double t=n*simulationParams.dt;
                u_exacte = Domaine->initialCondition({position_x-v1*t,position_y-v2*t,position_z-v3*t},simulationParams.velocity)*exp(-v*simulationParams.sigma_T*t);
                
                // Calcul de l'erreur l2
                double local_error = std::abs(u - u_exacte);
                error_sum += local_error * local_error; 
            }
         }
      }
      simulationParams.time += simulationParams.dt;

      double L2_error = std::sqrt(error_sum / (simulationParams.Nx * simulationParams.Ny * simulationParams.Nz)); 
      std::cout << " Absorption case, L2 Error = " << L2_error << std::endl;

   }




   delete Domaine;

   return 0;
}