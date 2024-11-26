#include <iostream>
#include <vector>
using namespace std;




int findSpi(const vector<int>& grades, const vector<int>& credits) {
    if (grades.size() != credits.size() || grades.empty()) {
        cout << "Error: Grades and credits arrays must have the same non-zero length." << endl;
        return -1; // Error value
    }

    int sumProduct = 0;
    int sumCredits = 0;

    for (size_t i = 0; i < grades.size(); ++i) {
        sumProduct += grades[i] * credits[i];
        sumCredits += credits[i];
    }
    if (sumCredits == 0) {
        cout << "Error: Sum of credits is zero, cannot divide by zero." << endl;
        return -1; // Error value
    }

    return sumProduct / sumCredits;
}

int findCpi(const vector<int>& spi, int numSems) {
    if (spi.empty() || numSems == 0) {
        cout << "Error: Invalid input" << endl;
        return -1; // Error value
    }

    int sumSpi = 0;

    for (size_t i = 0; i < spi.size(); ++i) {
        sumSpi += spi[i];
    }

    return sumSpi / numSems;
}

void testFindSpi() {
    vector<int> grades1 = {10, 5, 7, 8};
    vector<int> credits1 = {3, 2, 5, 1};
    cout << "Test Case 1 (SPI): Expected ~7.55, Result = " << findSpi(grades1, credits1) << endl;

    vector<int> grades2 = {10, 8, 9};
    vector<int> credits2 = {0, 0, 0};
    cout << "Test Case 2 (SPI): Expected Error, Result = " << findSpi(grades2, credits2) << endl;

    vector<int> grades3 = {0, 10, 5};
    vector<int> credits3 = {2, 4, 3};
    cout << "Test Case 3 (SPI): Expected ~6.11, Result = " << findSpi(grades3, credits3) << endl;

    vector<int> grades4 = {6, 6, 6};
    vector<int> credits4 = {2, 2, 2};
    cout << "Test Case 4 (SPI): Expected 6.0, Result = " << findSpi(grades4, credits4) << endl;

    vector<int> grades5 = {7, 8};
    vector<int> credits5 = {3, 2, 4};
    cout << "Test Case 5 (SPI): Expected Error, Result = " << findSpi(grades5, credits5) << endl;
}

void testFindCpi() {
    vector<int> spi1 = {8, 7, 9, 8};
    int numSems1 = 4;
    cout << "Test Case 1 (CPI): Expected 8.0, Result = " << findCpi(spi1, numSems1) << endl;

    vector<int> spi2 = {8};
    int numSems2 = 1;
    cout << "Test Case 2 (CPI): Expected 8.0, Result = " << findCpi(spi2, numSems2) << endl;

    vector<int> spi3 = {7, 7, 7, 7, 7};
    int numSems3 = 5;
    cout << "Test Case 3 (CPI): Expected 7.0, Result = " << findCpi(spi3, numSems3) << endl;

    vector<int> spi4 = {};
    int numSems4 = 0;
    cout << "Test Case 4 (CPI): Expected Error, Result = " << findCpi(spi4, numSems4) << endl;

    vector<int> spi5 = {8, 7, 9};
    int numSems5 = 0;
    cout << "Test Case 5 (CPI): Expected Error, Result = " << findCpi(spi5, numSems5) << endl;
}

int main() {
    cout<<"Test Cases for findSpi(): "<<endl; 
    testFindSpi();
    cout<<endl<<endl<<"Test Cases for findCpi(): "<<endl;
    testFindCpi();
    return 0;
}
