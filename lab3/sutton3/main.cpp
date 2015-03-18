/**
* @file main.cpp
* @author Joseph Sutton
* @description Newton's Interpolation w/ D.D. table
* @input # of Data points, and data points [x,y] for n data points.
*/

#include <iostream>
#include <fstream>
//#include <memory>
#include "newtonInterp.h"

// Configuration for output
bool			USE_FILE_OUTPUT = false;
std::string		FILE_NAME		= "newtonInterp.txt";

int main() {
	int numDataPts = 0;

	// input number of data points for interpolation
	std::cout << "Number of data points: ";
	std::cin >> numDataPts;
	std::cout << "\n";

	double** dataPoints = new double*[numDataPts];

	// input the actual data points for 
	// n number of data points stated
	for(int i = 0; i < numDataPts; i++) {
		dataPoints[i] = new double[2];

		// x[i]
		std::cout << "Enter X" << i << ": ";
		std::cin >> dataPoints[i][0];

		// y[i] (or f(x[i]))
		std::cout << "Enter Y" << i << ": ";
		std::cin >> dataPoints[i][1];

		std::cout << "\n";

	}

	// object declaration
	interp::newtonInterp newtonInterpObj;
	newtonInterpObj.setNumDataPts(numDataPts);
	newtonInterpObj.setDataPts(dataPoints);
	newtonInterpObj.setDebugFlag(true);

	// determine output for debugging/data
	if (USE_FILE_OUTPUT) {
		std::ofstream* of = new std::ofstream(FILE_NAME, std::ofstream::app);
		newtonInterpObj.setOutputStream(of);
	} else {
		std::ostream* out = &std::cout;
		newtonInterpObj.setOutputStream(out);
	}

	// interpolate!
	newtonInterpObj.interpolate();

	std::cout << newtonInterpObj;

	return 0;
}