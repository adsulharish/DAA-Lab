#include <iostream>
#include <vector>
#include <string>
#include <cmath> // Include cmath for pow

using namespace std;

// Function for brute force multiplication
int bruteForceMultiply(int a, int b) {
    int result = 0;
    int absA = abs(a);
    int absB = abs(b);

    for (int i = 0; i < absB; i++) {
        result += absA; // Add 'absA' absB times
    }

    // Handle negative results
    return (a < 0) ^ (b < 0) ? -result : result;
}

// Karatsuba algorithm for multiplication
long long karatsubaMultiply(long long x, long long y) {
    // Base case for recursion
    if (x < 10 && y < 10) {
        return x * y;
    }

    // Handle negatives in Karatsuba multiplication
    bool isNegative = (x < 0) ^ (y < 0);
    x = abs(x);
    y = abs(y);

    // Find the size of the numbers
    int n1 = to_string(x).size();
    int n2 = to_string(y).size();
    int n = max(n1, n2);
    int half = n / 2;

    // Split the digit sequences in the middle
    long long power = static_cast<long long>(pow(10, half));
    long long a = x / power; // High part of x
    long long b = x % power; // Low part of x
    long long c = y / power; // High part of y
    long long d = y % power; // Low part of y

    // 3 recursive calls
    long long ac = karatsubaMultiply(a, c);
    long long bd = karatsubaMultiply(b, d);
    long long abcd = karatsubaMultiply(a + b, c + d);

    // The result of the Karatsuba multiplication
    long long result = ac * static_cast<long long>(pow(10, 2 * half)) 
                       + (abcd - ac - bd) * power 
                       + bd;

    return isNegative ? -result : result;
}

int main() {
    // Test cases: 5 positive and 5 negative integers
    vector<pair<int, int>> testCases = {
        {123456789, 987654321},   // Positive
        {999999999, 888888888},   // Positive
        {12345678, 87654321},     // Positive
        {98765432, 12345678},     // Positive
        {543210987, 654321098},    // Positive
        {-123456789, -987654321}, // Negative
        {999999999, -888888888},  // Mixed
        {-12345678, 87654321},    // Mixed
        {98765432, -12345678},    // Mixed
        {-543210987, 654321098}   // Mixed
    };

    // Print results
    cout << "Multiplication Results:\n";
    cout << "----------------------------------------------\n";

    // Testing both algorithms
    for (const auto& testCase : testCases) {
        int a = testCase.first;
        int b = testCase.second;

        // Calculate results
        int bruteResult = bruteForceMultiply(a, b);
        long long karatsubaResult = karatsubaMultiply(a, b);

        // Print results with clear indication of algorithm used
        cout << a << " * " << b << ":\n";
        cout << "Brute Force Result: " << bruteResult << endl;
        cout << "Karatsuba Result:   " << karatsubaResult << endl;
        cout << "----------------------------------------------\n";
    }

    return 0;
}
 