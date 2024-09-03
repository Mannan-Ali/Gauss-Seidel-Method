#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//Function to return if the follwing matrix is daigonally dominant or not

bool checkDiagDom(const vector<vector<double>>& arr, int dim) {
    int value = 0;
    for (int i = 0; i < dim; i++) {
        double sum = 0.0;
        for (int j = 0; j < dim; j++) {
            sum += (i != j) * abs(arr[i][j]);
        }
        sum -= abs(arr[i][i]);
        value = (sum > 0) + value * (sum <= 0);
    }
    return !value;
}


vector<vector<double>> permuteMat(const vector<vector<double>>& arr) {
    vector<vector<double>> mat = arr;
    int dim = mat.size();
    
    do {
        if (checkDiagDom(mat, dim)) {
            cout << "Rearranged Matrix (diagonal Dominance):" << endl;
            for (int i = 0; i < dim; i++) {
                for (int j = 0; j <= dim; j++) {
                    cout << mat[i][j] << " ";
                }
                cout << endl;
            }
            return mat;
        }
    } while (next_permutation(mat.begin(), mat.end()));
    
    cout << "The matrix has no diagonal dominance." << endl;
    return vector<vector<double>>();
}

vector<double> gaussSeidel(const vector<vector<double>>& mat, const vector<double>& initialGuess) {
    if (mat.empty()) {
        return vector<double>();
    }
    
    int n = mat.size();
    vector<double> x = initialGuess;
    
    for (int iter = 0; iter < 15; iter++) {  // Perform a fixed number of iterations
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += mat[i][j] * x[j];
                }
            }
            x[i] = (mat[i][n] - sum) / mat[i][i];
        }
    }
    
    return x;
}

int main() {
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;
    
    vector<vector<double>> matrix(n, vector<double>(n + 1));
    
    cout << "Enter the coefficients and constants for each equation:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << "Enter A[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrix[i][j];
        }
    }
    
    cout << "Enter the initial guesses for the variables:" << endl;
    vector<double> initialGuess(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter initial guess for x[" << i + 1 << "]: ";
        cin >> initialGuess[i];
    }
    
    vector<vector<double>> A = permuteMat(matrix);
    vector<double> solution = gaussSeidel(A, initialGuess);
    
    if (!solution.empty()) {
        cout << "Solution after 15 iterations:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i + 1 << "] = " << solution[i] << endl;
        }
    }
    
    return 0;
}
