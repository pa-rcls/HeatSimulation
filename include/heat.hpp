#ifndef HEAT_HPP
#define HEAT_HPP

#include <vector>

class HeatMatrix {
public:
    HeatMatrix(int rows, int cols, double alpha, double dt, double dx, double dy);  // Constructor to initialize the matrix and thermal parameters
    void printMatrix() const; // Method to print the matrix
    void setHeatPoint(int x, int y, double heat); // Method to set the initial heat at a specific point
    void updateHeatMatrix();  // Method to simulate the full heat equation and update the matrix

private:
    std::vector<std::vector<double>> matrix;  // 2D matrix represented as a vector of vectors
    double alpha;  // Thermal diffusivity coefficient
    double dt;     // Time step
    double dx, dy; // Spatial step sizes in x and y directions
};

#endif // HEAT_HPP
