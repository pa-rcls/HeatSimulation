#include "heat.hpp"
#include "confReader.hpp"
#include "outputWriter.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

    std::string simu_case;
    // Check if at least one argument is passed (besides the program name)
    if (argc > 1) {
        // argv[1] contains the first argument, convert it to a std::string
        simu_case = argv[1];
        
        // Print the first argument
        std::cout << "Case selected : " << simu_case << std::endl;
    } else {
        std::cout << "Please select a simulation case in examples/" << std::endl;
        return 0;
    }

    // Create an instance of ConfReader to parse the INI file
    ConfReader reader(simu_case + "config.ini");

    //Read values from config file 
    int rows = std::stoi(reader.get("simulation", "rows"));
    int cols = std::stoi(reader.get("simulation", "cols"));
    double alpha = std::stod(reader.get("simulation", "alpha"));
    double dt = std::stod(reader.get("simulation", "dt"));
    double dx = std::stod(reader.get("simulation", "dx"));
    double dy = std::stod(reader.get("simulation", "dy"));

    int x = std::stoi(reader.get("initial_heat_point", "x"));
    int y = std::stoi(reader.get("initial_heat_point", "y"));
    double temperature = std::stod(reader.get("initial_heat_point", "temperature"));

    // Display values retrieved from the INI file
    std::cout << "-----------------Simulation parameters :-----------------" << std::endl;
    std::cout << "Rows : " << reader.get("simulation", "rows") << "\n";
    std::cout << "Cols : " << reader.get("simulation", "cols") << "\n";
    std::cout << "Alpha : " << reader.get("simulation", "alpha") << "\n";
    std::cout << "dt : " << reader.get("simulation", "dt") << "\n";
    std::cout << "dx : " << reader.get("simulation", "dx") << "\n";
    std::cout << "dy : " << reader.get("simulation", "dy") << "\n";
    std::cout << "initial_heat_point x : " << reader.get("initial_heat_point", "x") << "\n";
    std::cout << "initial_heat_point y : " << reader.get("initial_heat_point", "y") << "\n";
    std::cout << "temperature : " << reader.get("initial_heat_point", "temperature") << "\n";
    std::cout << "---------------------------------------------------------" << std::endl;


    // Create a 5x5 matrix with thermal diffusivity (alpha), time step (dt), and spatial steps (dx, dy)
    HeatMatrix heatMatrix(rows, cols, alpha, dt, dx, dy);

    // Set an initial heat point at the center of the matrix
    heatMatrix.setHeatPoint(x, y, temperature);  // Set a high temperature at the center point

    // Print the initial matrix state
    std::cout << "Initial matrix:" << std::endl;
    heatMatrix.printMatrix();
    std::cout << "-----------------" << std::endl;

    // Perform multiple iterations to update the heat matrix over time
    for (int i = 0; i < 10; i++) {
        heatMatrix.updateHeatMatrix();  // Update matrix based on the heat equation
        std::cout << "Matrix after iteration " << i+1 << ":" << std::endl;
        heatMatrix.printMatrix();  // Print the matrix after each iteration
        std::cout << "-----------------" << std::endl;
    }

    return 0;
}