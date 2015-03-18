/**
* @file newtonInterp.h
* @author Joseph Sutton
* @description Newton's Interpolation w/ D.D. table
* @input # of Data points, and data points [x,y] for n data points.
*/

#ifndef H_NEWTON_INTERP_H
#define H_NEWTON_INTERP_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// interpolation namespace
namespace interp {

	// todo
	class lagrange {};

	// newton interpolation class
	class newtonInterp {
	private:
		// bool flags
		bool debug;
		bool interpolated;

		// important properties
		double**			dataPts;		// data points
		int					numPts;			// number of data points
		std::ostream*		out;			// managable output
		double*				coefficients;	// storing coefficients post-divided difference table calcs
		double**			ddTable;		// divided difference table
	public:
		// getters
		const std::ostream* getOutputStream() const;
		const bool getDebugFlag() const;
		const int getNumDataPts() const;
		double** getDDTable() const;
		double** getDataPts() const;
		double* getCoeffs() const;

		// setters
		void setOutputStream(std::ostream*);
		void setDebugFlag(bool);
		void setDataPts(double**);
		void setNumDataPts(int);

		// methods
		void interpolate();
		bool isInterpolated();
		double evalX(double);

		// overloaded operators

			// ostream overload (<<)
			friend std::ostream& operator<<(std::ostream& os, const newtonInterp& obj) {
				int w = 9; // width

				os << std::left << std::setw(w) << std::setfill(' ') << "i";
				os << std::left << std::setw(w) << std::setfill(' ') << "x[n]";
				os << std::left << std::setw(w) << std::setfill(' ') << "f(x[n])";

				for (int i = 0; i < obj.getNumDataPts(); i++) {
					os << std::left << std::setw(w) << std::setfill(' ') << i;
				}

				os << "\n";

				double** table	= obj.getDDTable();
				double** data	= obj.getDataPts();

				// display divided difference table
				for (int i = 0; i < obj.getNumDataPts(); i++) {

					os << std::left << std::setw(w) << std::setfill(' ') << i;
					os << std::left << std::setw(w) << std::setfill(' ') << data[i][0];
					os << std::left << std::setw(w) << std::setfill(' ') << data[i][1];

					if (i > 0) {
						for (int j = i; j < obj.getNumDataPts(); j++) {

							os << std::left << std::setw(w) << std::setfill(' ') << std::setprecision(3) << table[i][j];

						}
					}

					os << "\n";
				}

				os << "\n";

				double* coefficients = new double[(obj.getNumDataPts() - 1)];
				coefficients[0] = data[0][1];
				int x = 1;

				// get coefficients for newton polynomial
				for (int i = 1; i < obj.getNumDataPts(); i++) {
					for (int j = i; j < obj.getNumDataPts(); j++) {
						coefficients[x] = table[i][j];
						x++;
						break;
					}
				}

				os << "f(x) = ";

				double t = 0;

				// print polynomial
				for (int i = 0; i < x; i++) {
					if (i > 0) {
						os << " + " << coefficients[i];
						for (int j = 0; j < i; j++) {
							t = (1 - data[j][0]) * t + coefficients[i];
							os << "(x - " << std::setprecision(4) << data[j][0] << ")";
						}
					}
					else {
						os << coefficients[i];
						t = coefficients[i];
					}
				}

				os << "\n\n";

				// evaluate polynomial for all x
				for (int y = 0; y < x; y++) {
					double val;
					double x	= data[y][0];

					for (int i = 0; i < x; i++) {
						if (i > 0) {
							for (int j = 0; j < i; j++) {
								val += coefficients[i] * (x - data[j][0]);
							}
						}
						else {
							val = coefficients[i];
						}
					}

					os << "f(" << x << ") = " << std::setprecision(3) << val << "\n";
				}
				

				return os;
			};

	};

};

#endif