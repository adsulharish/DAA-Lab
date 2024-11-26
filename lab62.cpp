#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to calculate the minimum number of multiplications
int matrixChainOrder(const vector<int>& dims, vector<vector<int>>& m, vector<vector<int>>& s) {
    int n = dims.size() - 1;  // Number of matrices
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;  // No cost for a single matrix
    }

    for (int l = 2; l <= n; l++) {  // l is the chain length
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n];
}

// Function to print the optimal order of multiplication
void printOptimalOrder(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "M" << i;  // Print matrix index (1-based)
    } else {
        cout << "(";
        printOptimalOrder(s, i, s[i][j]);  // Left sub-chain
        printOptimalOrder(s, s[i][j] + 1, j);  // Right sub-chain
        cout << ")";
    }
}

// Main function to test different cases
int main() {
    // Test cases for different scenarios
    vector<vector<int>> testCases = {
        {10, 20, 30},
        {10, 20, 30, 40, 50},
        {5, 10, 20, 30, 40, 50},
        {10, 20},  // Invalid (only one matrix)
        {10, 20, 30, 15},  // Incompatible multiplication
        {10, 0, 30, 40},  // Zero dimension
        {},  // Empty chain
        {100, 200, 300, 400, 500},
        {10, 20, 30, 40, 50, 60, 70, 80},
        {10, 20, 25, 30}  // Incompatible multiplication
    };

    for (int t = 0; t < testCases.size(); t++) {
        cout << "Running Test Case " << t + 1 << "..." << endl;

        vector<int> dims = testCases[t];
        if (dims.size() < 3) {
            cout << "Error: Matrix chain must contain at least two matrices." << endl;
            continue;
        }

        // Check for zero or negative dimensions
        bool invalidDimensions = false;
        for (int i = 0; i < dims.size(); i++) {
            if (dims[i] <= 0) {
                invalidDimensions = true;
                break;
            }
        }
        if (invalidDimensions) {
            cout << "Error: Matrix dimensions must be positive integers." << endl;
            continue;
        }

        // Create matrix m (cost table) and s (split table)
        int n = dims.size() - 1;
        vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
        vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

        // Call the matrix chain order function
        int minMult = matrixChainOrder(dims, m, s);

        // Display the result
        cout << "Minimum number of multiplications: " << minMult << endl;
        cout << "Optimal order of multiplication: ";
        printOptimalOrder(s, 1, n);
        cout << endl << endl;
    }

    return 0;
}
