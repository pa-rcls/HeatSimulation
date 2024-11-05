#include "heat.hpp"
#include <iostream>
#include <iomanip>

// Constructor: Initialize matrix with zeros and set the thermal parameters
HeatMatrix::HeatMatrix(int rows, int cols, double alpha, double dt, double dx, double dy)
    : matrix(rows, std::vector<double>(cols, 0.0)), alpha(alpha), dt(dt), dx(dx), dy(dy) {}

// Method to print the matrix with two decimal precision
void HeatMatrix::printMatrix() const {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << std::fixed << std::setprecision(2) << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Method to set the heat at a specific point in the matrix
void HeatMatrix::setHeatPoint(int x, int y, double heat) {
    if (x >= 0 && x < (int)matrix.size() && y >= 0 && y < (int)matrix[0].size()) {
        matrix[x][y] = heat;
    } else {
        std::cerr << "Error: index (" << x << "," << y << ") out of bounds" << std::endl;
    }
}

// Update the heat matrix using the full heat equation
void HeatMatrix::updateHeatMatrix() {
    // Create a temporary copy of the matrix to store new values
    std::vector<std::vector<double>> newMatrix = matrix;

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Traverse the matrix, skipping the boundary points
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            // Second derivative in x-direction (difference between neighbors along the x-axis)
            double T_xx = (matrix[i+1][j] - 2 * matrix[i][j] + matrix[i-1][j]) / (dx * dx);
            // Second derivative in y-direction (difference between neighbors along the y-axis)
            double T_yy = (matrix[i][j+1] - 2 * matrix[i][j] + matrix[i][j-1]) / (dy * dy);
            // Update the temperature at point (i, j) using the full heat equation
            newMatrix[i][j] = matrix[i][j] + alpha * dt * (T_xx + T_yy);
        }
    }

    // Replace the old matrix with the new updated matrix
    matrix = newMatrix;
}



