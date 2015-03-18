/**
* @file newtonInterp.cpp
* @author Joseph Sutton
* @description Newton's Interpolation w/ D.D. table
* @input # of Data points, and data points [x,y] for n data points.
*/

#ifndef CPP_NEWTON_INTERP_CPP
#define CPP_NEWTON_INTERP_CPP

#include <iostream>
#include "newtonInterp.h"

// return debug flag
const bool interp::newtonInterp::getDebugFlag() const {
	return this->debug;
}

// return isInterpolated flag
bool interp::newtonInterp::isInterpolated() {
	return this->interpolated;
}

// return output stream
const std::ostream* interp::newtonInterp::getOutputStream() const {
	return this->out;
}

// set debug flag 
void interp::newtonInterp::setDebugFlag(bool flag) {
	this->debug = flag;
}

// set output stream
void interp::newtonInterp::setOutputStream(std::ostream* _out) {
	this->out = _out;
}

// set num data pts
void interp::newtonInterp::setNumDataPts(int n) {
	this->numPts = n;
}

// set data pts
void interp::newtonInterp::setDataPts(double** pts) {
	this->dataPts = pts;
}

// get num data pts
const int interp::newtonInterp::getNumDataPts() const {
	return this->numPts;
}

// get dd table
double** interp::newtonInterp::getDDTable() const {
	return ddTable;
}

// get dd table
double** interp::newtonInterp::getDataPts() const {
	return dataPts;
}

// get coefficients
double* interp::newtonInterp::getCoeffs() const {
	return coefficients;
}

// interpolation method (weee)
void interp::newtonInterp::interpolate() {
	std::ostream& os = *out;

	// vector refs
	double**	data	= this->dataPts;	// data points ([x,y]{n})
	const int	n		= this->numPts;		// number of data points (for looping, since we've allocated arrays dynamically)
	double**	table	= new double*[n];	// divided difference table

	// init dd table memory alloc
	for (int i = 0; i < n; i++) {
		table[i] = new double[n];

		// init f(x[0])
		table[0][i] = data[i][1];

	}

	// divided difference table
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j++) {

			double fn	= table[(i - 1)][(j - 1)];	// fn(x)
			double fnp	= table[(i - 1)][j];		// fn+1(x)
			double xn	= data[(j - i)][0];			// x(n)
			double xnp	= data[j][0];				// x(n+1)

			table[i][j] = ((fnp - fn) / (xnp - xn));

		}
	}

	this->ddTable = table;
}

#endif