/**
* @file main.cpp
* @author Joseph Sutton
* @description Trapezoid Rule, Richardson's Extrapolation, and Simpson's Rule
* @input Upper and lower limit of integral; maximum number of sub-intervals.
*/
#include <iostream>
#include <iomanip>

// prototypes
double evalSimpson(double (*)(double), double, double, int);
double evalTrapezoid(double (*)(double), double, double, int);
double evalRichardson(double, double, int);
double simpsonError(double);
double trapezoidError(double, double, double);
double extrapError(double, int);
double fn(double);
double fp(double);

int main() {
	// basic decls
	int	maxSubIntervals;
	double	upperLimit,
		lowerLimit;

	// lower limit
	std::cout << "Enter lower limit: ";
	std::cin >> lowerLimit;

	// upper limit
	std::cout << "Enter upper limit: ";
	std::cin >> upperLimit;

	// check if a <= b
	if(lowerLimit >= upperLimit) {
		std::cout << "Upper limit cannot be equal to or less than the lower limit.\n";
		return 0;
	}

	// max sub-intervals
	std::cout << "Enter maximum number of sub-intervals: ";
	std::cin >> maxSubIntervals;

	for(int i = 0; i < maxSubIntervals; i++) {

		double h = (upperLimit - lowerLimit) / 2;

		double Ti	= evalTrapezoid(fn, lowerLimit, upperLimit, maxSubIntervals);
		double Ri	= evalRichardson(lowerLimit, upperLimit, maxSubIntervals);
		double Si	= evalSimpson(fn, lowerLimit, upperLimit, maxSubIntervals);
		double ETi	= abs(fp(h) - Ti);
		double ERi	= abs(fp(h) - Ri);
		double ESi	= abs(fp(h) - Si);

		if(i == 0) {
			std::cout << std::left << std::setw(45) << std::setfill(' ') << std::setprecision(15) << Ti << " ";
			std::cout << std::left << std::setw(45) << std::setfill(' ') << std::setprecision(15) << ETi;
		} else {
			std::cout << std::left << std::setw(15) << std::setfill(' ') << std::setprecision(15) << Ti << " ";
			std::cout << std::left << std::setw(15) << std::setfill(' ') << std::setprecision(15) << Ri << " ";
			std::cout << std::left << std::setw(15) << std::setfill(' ') << std::setprecision(15) << Si << " ";
			std::cout << std::left << std::setw(15) << std::setfill(' ') << std::setprecision(15) << ETi << " ";
			std::cout << std::left << std::setw(15) << std::setfill(' ') << std::setprecision(15) << ERi << " ";
			std::cout << std::left << std::setw(15) << std::setfill(' ') << std::setprecision(15) << ESi;
		}

		std::cout << "\n";

	}

	int x; std::cin >> x;

	return 0;
}

/**
 * The function.
 */
double fn(double x) {
	return x * cos(x);
}

/**
 * The derivative.
 */
double fp(double x) {
	return cos(x) - x * sin(x);
}

/**
 * Evaluate a function with Simpson's Rule.
 */
double evalSimpson(double (*f)(double), double a, double b, int n) {

	double ret = 0.0, h, x;

	h = (b - a) / n;

	for(int i = 0; i < n; i++) {

		x = i * h + a;
		ret += (h * 0.3333) * (fn(x) + 4 * f(x + h/2) + f(x + h)) / 6;

	}

	return ret;

}

/**
 * Evaluate a function with Trapezoid Rule.
 */
double evalTrapezoid(double (*f)(double), double a, double b, int n) {

	double ret = 0.0, h;

	h = (double)(b - a) / n;

	// h / 2 * [f(a) + f(b)]
	for(int i = 1; i <= n; i++) {

		ret += (h * 0.5) * (f(a + i * h) + f(a + i * h + h));

	}

	return ret * h;

}

/**
 * Richardson's extrapolation.
 */
double evalRichardson(double a, double b, int n) {

	double	ret = 0.0, 
		h = (double)(b - a) / n;

	double** calc = new double*[n];

	// grab/generate h's
	for(int i = 0; i < n; i++) {
		// allocate mem for dyn array
		calc[i] = new double[n];

		if(i == 0) {
			calc[0][i] = h;
		} else {
			h = h / 2;
			calc[0][i] = h;
		}

	}
	
	// extrapolate!
	for(int i = 1; i < n; i++) {
		for(int j = 0; j < (n - 1); j++) {

			calc[i][j] = calc[i - 1][j + 1] + (calc[i - 1][j + 1] - calc[i - 1][j])/pow(2.0, i);

		}
	}

	// return last extrapolant (sp)
	return calc[n - 1][0];

}

double trapezoidError(double h, double a, double b) {

	return (-1) * ((b - a) / 12) * pow(h, 2);

}
