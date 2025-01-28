#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <random>
#include "SetOfParticles.hpp"
#include <chrono>



int main(int argc, char const* argv[])
{

   // Début de la mesure du temps
   auto start_time = std::chrono::high_resolution_clock::now();

  // Structure pour stocker les paramètres de simulation
   struct struct_simulationParams simulationParams;
   simulationParams.fileName = "param.txt";
   Read_params(simulationParams);

   // Définir le domaine selon le type
   AbstractDomain* Domaine = nullptr;
   Domaine = new BoundaryDomain(simulationParams);


   // Ouverture du fichier pour sauvegarder les résultats au temps initial
   std::ofstream file;

   double Mesh_size_x = (simulationParams.xmax - simulationParams.xmin) / (simulationParams.Nx) ;
   double Mesh_size_y = (simulationParams.ymax - simulationParams.ymin) / (simulationParams.Ny) ;
   double Mesh_size_z = (simulationParams.zmax - simulationParams.zmin) / (simulationParams.Nz) ;


   file.open("Resultats/solution_t_" + std::to_string(0) + ".txt");
   double u ; 





   for (int i = 0; i < simulationParams.Nx; i++)
   {
      for (int j = 0; j < simulationParams.Ny; j++)
      {
         for (int k = 0; k < simulationParams.Nz; k++)
         {
            double position_x = simulationParams.xmin + i  * Mesh_size_x;
            double position_y = simulationParams.ymin + j * Mesh_size_y;
            double position_z = simulationParams.zmin + k * Mesh_size_z;

            // Application de la condition initiale définie dans le domaine
            u = Domaine->initialCondition({ position_x, position_y, position_z }, simulationParams.velocity);            

            file << position_x << "\t" << position_y << "\t" << position_z << "\t" << simulationParams.time << "\t" << u << std::endl;
         }
      }
   }
   simulationParams.time += simulationParams.dt;
   file.close();

   // Nombre total d'étapes temporelles
   double Nf = int(simulationParams.Tf / simulationParams.dt) + 1;

   // Boucle principale : simulation pour chaque pas de temps
   for (int n = 1; n < Nf; n++)
   {
      file.open("Resultats/solution_t_" + std::to_string(n) + ".txt");

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
                              
               // Simulation du mouvement des particules
               SetOfParticles packOfParticles(Domaine, simulationParams, u, { position_x, position_y, position_z }, simulationParams.time);
               packOfParticles.simulateMotion();
               u = packOfParticles.get_u();
               file << position_x << "\t" << position_y << "\t" << position_z << "\t" << simulationParams.time << "\t" << u << std::endl;
            }
         }
      }
      // Mise à jour du temps de simulation
      simulationParams.time += simulationParams.dt;
      
      file.close();
   }


   delete Domaine;

   // Fin de la mesure du temps
   auto end_time = std::chrono::high_resolution_clock::now();

    // Calcul de la durée d'exécution
   auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
   std::cout << "Temps d'exécution total : " << duration.count() << " millisecondes." << std::endl;

   return 0;
}