#include "roots.hpp"
#include <cmath>
#include <iostream>

// Bisection Root Finder
bool bisection(std::function<double(double)> f, double a, double b, double *root) {
    double tolerance = 1e-6; // Function must return correct root within a tolerance of 1e-6
    double max_iterations = 1e6; // A limit so the code doesn't run forever
    double c;

    if (f(a) * f(b) >= 0) { // Ensures that the starting points a and b have different signs. (One is negative/Positive)
        return false;
    }
    
    for (int i = 0; i < max_iterations; i++) { // For loop that starts the counter at i = 0 and continues until 1e6 (add one each time)
        c = (a + b) / 2; // Used to calculate the midpoint

        if (std::abs(f(c)) < tolerance || (b - a) / 2 < tolerance) {
            *root = c; // This will put the answer in the box
            return true; // We have found the root
        }

        if ((f(a) > 0) == (f(c) > 0)) {
            a = c; // Root is in the right half
        }
        else {
            b = c; // Root is in the left half
        }
    
    }

    return false;
}

// Regula Falsi Root Finder
bool regula_falsi(std::function<double(double)> f, double a, double b, double *root) {
    double tolerance = 1e-6; // Function must return correct root within a tolerance of 1e-6
    double max_iterations = 1e6; // A limit so the code doesn't run forever
    double c;

    if (f(a) * f(b) >= 0) { // Ensures that the starting points a and b have different signs. (One is negative/Positive)
        return false;
    }

    for (int i = 0; i < max_iterations; i++) { // Create a pointer until max iterations are reached
        c = a - (f(a) * (b - a) / (f(b) - f(a))); // Flase Position formula

        if (std::abs(f(c)) < tolerance) { // This part tests the current function to see if it is close enough to zero
            *root = c; // Once it works, put it into memory location pointed by root
            return true; // Found the root so exit
        }

        if ((f(a) > 0) == (f(c) > 0)) { // If both are the same sign then make a=c or else make b=c
            a = c;
        }
        else {
            b = c;
        }

    }
    return false;
}

// Newton Raphson Root Finder 
bool newton_raphson(std::function<double(double)> f, std::function<double(double)> g,
                    double a, double b, double c, double *root) { // f(x) is the standard function and g(x) is the derivative of it
    double tolerance = 1e-6;
    int max_iterations = 1000; // Newton-Raphson is much faster than the other methods so needs less iterations
    double x = c; // Start with an initial guess c with varible x

    for (int i = 0; i < max_iterations; i++) {
        double fx = f(x);
        double dfx = g(x); // This is the derivative

        if (std::abs(dfx) < 1e-10) { // If derviatve is super small, just return false because cant divide by 0
            return false;
        }

        double new_x = x - (fx /dfx); // Formula to calc where next guess should be

        if (std::abs(new_x - x) < tolerance) { // If the difference of the two positions is near zero, then it must mean a root is found
            *root = new_x;
            return true;
        }
        x = new_x; // Continue the for loop but now make x = x2 (Starts at new position)

    }
    return false;
}

// Secant Root Finder
bool secant(std::function<double(double)> f, double a, double b, double c, double *root) {
    double tolerance = 1e-6;
    int max_iterations = 1000;

    double x0 = a; // First initial guess
    double x1 = b; // Second initial guess

    for (int i = 0; i < max_iterations; i++) {
        double fx0 = f(x0);
        double fx1 = f(x1);

        if (std::abs(fx1 - fx0) < 1e-12) { // Prevent divison by zero/undefined (checks if y-values are near zero)
            return false;
        }

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0); // Formula for secant line

        if (std::abs(x2 - x1) < tolerance) {
            *root = x2;
            return true;
        }

        x0 = x1;
        x1 = x2; // Continue these iterations until the difference is near zero
    }
    return false;
}
