/**
* @file main.cpp
* @author Joseph Sutton
* @description Evaluating matrices with linear systems via Naive/Partial Pivoting Gaussian Elimination, and Upper Triangular form
* @input File name; file consists of multiple matrices separated by 2 \n's in which values are tab '\t' delimited
* @output Matrix representation of original augmented matrices, post-naive gauss. elimination and upper triangular form, 
* and Gaussian Elimination via Partial Pivoting w/ Upper Triangular form.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// prototypes
void originalMatrix(double**, int);
double** upTriangMatrix(double**, int);
void solveMatrix(double**, int, bool);
double** upTriPartialPivot(double**, int);

// consts
const double eps = 1.e-15;

int main() {
	string filename = "";

	cout << "Enter filename: ";
	cin >> filename;

	ifstream matrixFile(filename);

	if(!matrixFile.is_open()) {
		cout << "Failed to open data file.\n";
		return 0;
	}

	while(!matrixFile.eof()) {	

		string line;
		stringstream iss;

		int n;
		getline(matrixFile, line); // prime

		// get n
		iss << line;
		iss >> n;
		
		// clear sstream
		iss.clear();

		// malloc 2-d array matrix 
		double** matrix = new double*[n];

		for(int i = 0; getline(matrixFile, line); i++) {
			if(!(i < n)) {
				break;
			}

			iss << line;

			matrix[i] = new double[n + 1];

			for(int j = 0; getline(iss, line, '\t'); j++) {
				if(!(j <= n)) {
					break;
				}

				// convert string to double
				double dVal = stod(line);

				matrix[i][j] = dVal;
			}

			iss.clear();

		}

		// original augmented matrix
		originalMatrix(matrix, n);
		cout << "\n";

		// upper triangular matrix via naive gauss. elimination
		double** _matrix = upTriangMatrix(matrix, n);
		cout << "\n";

		// solution
		solveMatrix(_matrix, n, false);
		cout << "\n";

		// clear memory/matrix for use again
		free(_matrix);

		// upper triangle matrix via gauss. elim w/ partial pivot
		_matrix = upTriPartialPivot(matrix, n);
		cout << "\n";

		// solution from upper triangle matrix via gauss. elim w/ partial pivot
		solveMatrix(_matrix, n, true);
		cout << "\n--------------------------------------------\n"; // separation

		// clear memory
		free(_matrix);

	}

	int x; cin >> x;

	return 0;
}

// upper triangle matrix via gauss. elim w/ partial pivoting
double** upTriPartialPivot(double** matrix, int n) {

	double** newMatrix = new double*[n];

	// copy matrix
	for(int i = 0; i < n; i++) {

		newMatrix[i] = new double[n + 1];

		for(int j = 0; j <= n; j++) {
			newMatrix[i][j] = matrix[i][j];
		}
	}

	// partial pivot
	for(int i = 0; i < n; i++) {
		// init max and row
		double max = newMatrix[i][i];
		int r = i;
		
		// find largest in row, r = rownumber if found.
		for(int j = i + 1; j < n; j++) {
			if(max < newMatrix[j][i]) {
				max = newMatrix[j][i];
				r = j;
			}
		}

		// swap
		for(int j = 0; j <= n; j++) {
			double temp = newMatrix[r][j];
			newMatrix[r][j] = newMatrix[i][j];
			newMatrix[i][j] = temp;
		}

		// triangular matrix calc
		for(int j = i + 1; j < n; j++) {
			double m = newMatrix[j][i] / newMatrix[i][i];

			for(int k = 0; k <= n; k++) {
				newMatrix[j][k] -= m * newMatrix[i][k];
			}
		}
	}

	cout << "Triangular Matrix via Gaussian Elimination w/ Partial Pivoting:\n";

	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= n; j++) {

			if(j == n) {
				cout << setw(5) << " | ";
			}

			cout << setw(5) << left << setprecision(2) << newMatrix[i][j] << " ";

		}

		cout << "\n";

	}

	return newMatrix;

}

// solve matrix
void solveMatrix(double** matrix, int n, bool check = false) {

	// decl x 
	double* x = new double[n];

	// populate x[]
	for(int i = 0; i < n; i++) {
		x[i] = matrix[i][n - 1];
	}

	cout << "Solution:\n";

	for(int i = n - 1; i >= 0; i--) {
		double sum = 0;
		
		for(int j = i + 1; j <= n - 1; j++) {
			double mVal = matrix[i][j];
			double xj = x[j];

			sum = sum + mVal * xj;
		}

		double matrix_ii = matrix[i][i];
		double bi = matrix[i][n];

		if(check) {
			if((int)matrix_ii == 0) {
				x[i] = 0;
			} else {
				x[i] = (matrix[i][n] - sum) / matrix_ii;
			}
		} else {
			x[i] = (matrix[i][n] - sum) / matrix_ii;
		}

		// print 
		cout << "x[" << i << "] = " << setprecision(2) << left << x[i] << "\n";
	}

}

// print augmented matrix
void originalMatrix(double** matrix, int n) {

	cout << "Original Matrix:\n";

	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= n; j++) {

			if(j == n) {
				cout << setw(5) << " | ";
			}

			cout << setw(5) << left << setprecision(2) << matrix[i][j] << " ";

		}

		cout << "\n";

	}

}

// triangle matrix via naive gaussian elimination
double** upTriangMatrix(double** matrix, int n) {

	double** newMatrix = new double*[n];

	// copy matrix
	for(int i = 0; i < n; i++) {

		newMatrix[i] = new double[n + 1];

		for(int j = 0; j <= n; j++) {
			newMatrix[i][j] = matrix[i][j];
		}
	}

	// elimination
	for(int k = 0; k < n - 1; k++) {
		for(int i = k; i < n - 1; i++) {
			double m = ( newMatrix[i + 1][k] / newMatrix[k][k] );

			for(int j = 0; j <= n; j++) {
				newMatrix[i + 1][j] -= m * newMatrix[k][j];
			}
		}
	}

	cout << "Upper Triangle Matrix (Naive Gaussian Elimination):\n";

	// print matrix
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= n; j++) {

			if(j == n) {
				cout << setw(5) << " | ";
			}

			cout << setw(5) << left << setprecision(2) << newMatrix[i][j] << " ";

		}

		cout << "\n";

	}

	return newMatrix;

}
