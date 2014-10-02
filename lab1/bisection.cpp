/**
* @file bisection.cpp
* @duedate 09-25-2014
* @author Joseph Sutton
* @class CSCI-3180-001
* @description Lab 1 Assignment - Bisection Method approximation w/ Horner's algorithm for polynomial evaluation.
* @input error bounds [upper,lower], interval [a,b], polynomial degree, max # of iterations, and corresponding degree coefficients
*/

#ifndef CPP_BISECTION_CPP
#define CPP_BISECTION_CPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "bisection.h"

// return interval a
double bisection::getIntervalA() {
	return this->intervalA;
}

// return interval b
double bisection::getIntervalB() {
	return this->intervalB;
}

// return upper bound error
double bisection::getUpperBoundError() {
	return this->upperBound;
}

// return lower bound error
double bisection::getLowerBoundError() {
	return this->lowerBound;
}

// set debug flag within class (logging/output/debugging purposes)
void bisection::setDebug(bool debug) {
	this->debug = debug;
}

// set [a,] interval
void bisection::setIntervalA(double intervalA) {
	this->intervalA = intervalA;
}

// set [,b] interval
void bisection::setIntervalB(double intervalB) {
	this->intervalB = intervalB;
}

// set upper bound error
void bisection::setUpperBoundError(double upperBound) {
	this->upperBound = upperBound;
}

// set lower bound error
void bisection::setLowerBoundError(double lowerBound) {
	this->lowerBound = lowerBound;
}

// set maximum number of iterations
void bisection::setMaxIterations(int maxIterations) {
	this->maxIterations = maxIterations;
}

// execute method
void bisection::execute(std::ostream& out) {
	if(this->degree == 0) {
		std::cout << "f(x) not continuous, halting evaluation.";
		return;
	}

	this->outputReadablePolynomial(out);

	double a = this->intervalA;
	double b = this->intervalB;
	double c;

	out << std::left << std::setw(10)	<< std::setfill(' ') << "Max Error";
	out << std::left << std::setw(8)	<< std::setfill(' ') << "a";
	out << std::left << std::setw(8)	<< std::setfill(' ') << "b";
	out << std::left << std::setw(10)	<< std::setfill(' ') << "c";
	out << std::left << std::setw(8)	<< std::setfill(' ') << "f(a)";
	out << std::left << std::setw(8)	<< std::setfill(' ') << "f(b)";
	out << std::left << std::setw(8)	<< std::setfill(' ') << "f(c)";
	out << "\n";

	for(int i = 0; i < this->maxIterations; i++) {
		// c = (a+b)/2
		c = (a + b) / 2;

		double evalA = this->evaluate(a);
		double evalB = this->evaluate(b);
		double evalC = this->evaluate(c);

		// calculate error
		double maxError = std::max(
			abs(c - a),
			abs(c - b)
		);

		if (maxError > this->upperBound || maxError < this->lowerBound) {
			out << "STOPPING: Error bounds exceeded.";
			return;
		}

		// output
		out << std::fixed;
		out << std::left << std::setw(10)	<< std::setfill(' ') << std::setprecision(4) << maxError;
		out << std::left << std::setw(8)	<< std::setfill(' ') << std::setprecision(4) << a;
		out << std::left << std::setw(8)	<< std::setfill(' ') << std::setprecision(4) << b;
		out << std::left << std::setw(10)	<< std::setfill(' ') << std::setprecision(4) << c;
		out << std::left << std::setw(8)	<< std::setfill(' ') << std::setprecision(4) << evalA;
		out << std::left << std::setw(8)	<< std::setfill(' ') << std::setprecision(4) << evalB;
		out << std::left << std::setw(8)	<< std::setfill(' ') << std::setprecision(4) << evalC;
		out << "\n";

		// f(c) == 0 ?
		if (evalC == 0) {
			std::cout << "Root found: [" << a << "," << b << "] at iteration #" << i << "\n";
			break;
		}

		// f(c)f(a) < 0 ?
		if((evalC * evalA) < 0) {
			b = c;
		} else {
			a = c;
		}
	}

	out << "\n\n";
}

// evaluate method (horner's algorithm)
double bisection::evaluate(double x) {
	double result	= 0;

	for(std::vector<double>::iterator it = numCoefficients.begin(); it != numCoefficients.end(); ++it) {
		result = x * result + *it;
	}

	return result;
}

// output a readable polynomial (i.e. x^3 + -2x + -5)
void bisection::outputReadablePolynomial(std::ostream& out) {
	int _degree = this->degree;
	out << "Evaluating: ";

	for (std::vector<double>::iterator it = numCoefficients.begin(); it != numCoefficients.end(); ++it) {
		if (*it != 0) {
			if (_degree > 0) {
				out << *it << "x^" << _degree << " + ";
			} else {
				out << *it;
			}
		}

		_degree--;
	}

	out << "\n";
}

#endif