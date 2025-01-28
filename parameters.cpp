#include "parameters.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

template<typename T>
T parse_value(const std::string& line) {
    std::istringstream iss(line);
    T value;
    iss >> value;
    return value;
}

void Read_params(struct_simulationParams& simulationParams) {
    std::ifstream file(simulationParams.fileName);
    if (!file.is_open()) {
        std::cout << "Cannot open file : " << simulationParams.fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (std::getline(iss, value)) {
                // Supprimer les espaces éventuels
                key.erase(remove_if(key.begin(), key.end(), isspace), key.end());
                value.erase(remove_if(value.begin(), value.end(), isspace), value.end());

                if (key == "Dim") simulationParams.Dim = parse_value<int>(value);
                else if (key == "Nmc") simulationParams.Nmc = parse_value<int>(value);
                else if (key == "Tf") simulationParams.Tf = parse_value<double>(value);
                else if (key == "dt") simulationParams.dt = parse_value<double>(value);
                else if (key == "xmin") simulationParams.xmin = parse_value<double>(value);
                else if (key == "xmax") simulationParams.xmax = parse_value<double>(value);
                else if (key == "ymin") simulationParams.ymin = parse_value<double>(value);
                else if (key == "ymax") simulationParams.ymax = parse_value<double>(value);
                else if (key == "zmin") simulationParams.zmin = parse_value<double>(value);
                else if (key == "zmax") simulationParams.zmax = parse_value<double>(value);
                

                if (key == "v1" || key == "v2" || key == "v3") {
                    if (simulationParams.velocity.size() < 3) simulationParams.velocity.resize(3, 0.0);

                    if (key == "v1") simulationParams.velocity[0] = parse_value<double>(value);
                    else if (key == "v2") simulationParams.velocity[1] = parse_value<double>(value);
                    else if (key == "v3") simulationParams.velocity[2] = parse_value<double>(value);
                }
                else if (key == "Nx") simulationParams.Nx = parse_value<int>(value);
                else if (key == "Ny") simulationParams.Ny = parse_value<int>(value);
                else if (key == "Nz") simulationParams.Nz = parse_value<int>(value);
                else if (key == "sigma_S") simulationParams.sigma_S = parse_value<double>(value);
                else if (key == "sigma_T") simulationParams.sigma_T = parse_value<double>(value);
            }
        }
    }
    file.close();

}

