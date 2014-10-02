/** 
 * @file main.cpp
 * @author Joseph Sutton
 * @description Bisection Method approximation w/ Horner's algorithm for polynomial evaluation.
 * @input error bounds [upper,lower], interval [a,b], polynomial degree, max # of iterations, and corresponding degree coefficients
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "bisection.h"

int main() {
	double	upperBound,	// [stop] upper bound error
			lowerBound,	// [stop] lower bound error
			intervalA,	// a < 0
			intervalB;	// b > 0

	int maxIterations,	// [stop] max number of iterations
		degree;			// polynomial degree

	// input
	std::cout << "Polynomial degree: ";
	std::cin >> degree;

	// add one for constant (i.e. degree of one => 2x + 1)
	std::vector<double> numCoefficients;

	// handle output for further input (coefficients)
	for(int i = degree; i >= 0; i--) {
		if(i > 1) {
			std::cout << "x^" << i << " coefficient: ";
		} else {
			std::cout << ((i == 1) ? "x coefficient: " : "last coefficient: ");
		}

		double tmp;
		std::cin >> tmp;

		numCoefficients.push_back(tmp);
	}

	// obtain max iterations
	std::cout << "Max number of iterations: ";
	std::cin >> maxIterations;
	
	std::cout << "\n";

	// error bounds
	std::cout << "Upper error bound: ";
	std::cin >> upperBound;

	std::cout << "Lower error bound: ";
	std::cin >> lowerBound;

	std::cout << "\n";

	// intervals
	std::cout << "Interval A: ";
	std::cin >> intervalA;

	std::cout << "Interval B: ";
	std::cin >> intervalB;

	// start bisection handling
	bisection bsObj = bisection(degree, numCoefficients);

	// set data
	bsObj.setUpperBoundError(upperBound);
	bsObj.setLowerBoundError(lowerBound);
	bsObj.setIntervalA(intervalA);
	bsObj.setIntervalB(intervalB);
	bsObj.setMaxIterations(maxIterations);

	// open a file for output
	std::ofstream output("bisection_output.txt", std::ofstream::app);

	if (!output.is_open()) {
		std::cout << "Could not open file 'bisection_output.txt'. Exiting.";
		return 0;
	}

	// run bisection
	bsObj.execute(output);

	// close file
	output.close();

	return 0;
}
