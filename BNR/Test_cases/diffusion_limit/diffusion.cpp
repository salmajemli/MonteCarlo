#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip> // Pour std::setprecision
#include <random>
#include <sstream>
#include "../../../SetOfParticles.hpp"


int main(int argc, char const* argv[])
{
   struct struct_simulationParams simulationParams;
   simulationParams.fileName = "param_diffusion.txt";
   Read_params(simulationParams);

 
   AbstractDomain* Domaine = nullptr;
   Domaine = new BoundaryDomain(simulationParams);

   std::ofstream file;
   double Mesh_size_x = (simulationParams.xmax - simulationParams.xmin) / (simulationParams.Nx) ;
   double Mesh_size_y = (simulationParams.ymax - simulationParams.ymin) / (simulationParams.Ny) ;
   double Mesh_size_z = (simulationParams.zmax - simulationParams.zmin) / (simulationParams.Nz) ;

   double u ; 
    double dt=simulationParams.dt;
   double v1=simulationParams.velocity[0],v2=simulationParams.velocity[1], v3=simulationParams.velocity[2];


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
         }
      }
   }
   simulationParams.time += simulationParams.dt;
   file.close();


   int Nf = int(simulationParams.Tf / simulationParams.dt) + 1;

   double error_sum = 0.0; 
   double max_error = 0.0; 

   std::string file_path = "Reference/sol_ref_t10.txt";
   std::ifstream ref_file(file_path);
   if (!ref_file.is_open()) {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier à l'emplacement " << file_path << std::endl;
      return 1;
   }

   std::vector<double> u_exacte;
   std::string line;


   while (std::getline(ref_file, line)) {
      
      std::istringstream iss(line);
      double col1, col2, col3;

      if (iss >> col1 >> col2 >> col3) {
         u_exacte.push_back(col3);
      } else {
         std::cerr << "Erreur : Ligne mal formatée ignorée : " << line << std::endl;
      }
   }

    file.close();

   for (int n = 0; n < Nf; n++)
   {
      int s=0;
      double error_sum = 0.0; 
      double max_error = 0.0;
      for (int j = 0; j < simulationParams.Ny; j++)
      {
         for (int i = 0; i < simulationParams.Nx; i++)
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
                if(n==1)
                {
                    double local_error = std::abs(u - u_exacte[s]);
                    error_sum += local_error * local_error; 
                    max_error = std::max(max_error, local_error);
                }
                
               s=s+1;
               file << position_x << "\t" << position_y << "\t" << position_z << "\t" << simulationParams.time << "\t" << u << std::endl;
            }
         }
      }
      simulationParams.time += simulationParams.dt;
      if (n==1)
      {
         double L2_error = std::sqrt(error_sum / (simulationParams.Nx * simulationParams.Ny * simulationParams.Nz)); 
        std::cout << " diffusion limit case, L2 Error = " << L2_error << std::endl;
      }
      
      
      file.close();
   }





   delete Domaine;

   return 0;
}