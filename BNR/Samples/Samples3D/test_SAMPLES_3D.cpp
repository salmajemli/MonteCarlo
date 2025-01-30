#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip> 
#include <random>
#include <cmath>
#include <numeric> 
#include <stdexcept>



double Norm_Vector(const std::vector<double> a, const std::vector<double> b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument(" Norm_Vector Vectors must be of the same size");
        }

        double result = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            result += a[i] * b[i];
        }
        return std::sqrt(result);
    };



int main(int argc, char const* argv[])
{
   
   
   std::vector<double> sample(3,0.0);
   std::random_device rd;
   std::default_random_engine generator(rd());
   std::vector<std::vector<double>> Echantillon;
   
    std::ofstream file;
    file.open("Test_Echantillon.txt");


    for (int i =0; i < 10000; i++)
    {
        std::normal_distribution<double> normal_distribution(0.0, 1.0);
        for ( int i = 0 ; i<3 ; i++){
            sample[i] = normal_distribution(generator);
        }
        double Norm_sample = Norm_Vector(sample, sample) ;
        for ( int i = 0 ; i<3 ; i++){
            sample[i] = sample[i] / Norm_sample;
        }
        Echantillon.push_back(sample);
        file << sample[0] << "\t" << sample[1] <<  "\t" << sample[2] <<std::endl;

    }
    file.close();

    return 0;

}
