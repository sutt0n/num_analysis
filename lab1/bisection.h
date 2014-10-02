/**
* @file bisection.h
* @duedate 09-25-2014
* @author Joseph Sutton
* @class CSCI-3180-001
* @description Lab 1 Assignment - Bisection Method approximation w/ Horner's algorithm for polynomial evaluation.
* @input error bounds [upper,lower], interval [a,b], polynomial degree, max # of iterations, and corresponding degree coefficients
*/

#ifndef H_BISECTION_H
#define H_BISECTION_H

#include <vector>

class bisection {
private:
	// basics
	int degree,
		maxIterations;

	// store coefficients
	std::vector<double> numCoefficients;

	// stopping conditions
	double	intervalA,
			intervalB,
			upperBound,
			lowerBound;

	// debugging flag
	bool debug = false;

	// methods
	double evaluate(double);
public:
	// constructor(s)
	bisection(int degree, std::vector<double> numCoefficients) {
		this->degree = degree;
		this->numCoefficients = numCoefficients;
	};

	bisection(int degree, std::vector<double> numCoefficients, bool debug) {
		this->degree = degree;
		this->numCoefficients = numCoefficients;
		this->debug = debug;
	}

	// getters
	double getIntervalA();
	double getIntervalB();
	double getUpperBoundError();
	double getLowerBoundError();

	// setters
	void setDebug(bool);
	void setIntervalA(double);
	void setIntervalB(double);
	void setUpperBoundError(double);
	void setLowerBoundError(double);
	void setMaxIterations(int);
	//void setFunction(int, double);

	// member methods
	void execute(std::ostream&);
	void outputReadablePolynomial(std::ostream&);

};

#endif